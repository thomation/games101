//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of the Whitted-syle light transport algorithm (E [S*] (D|G) L)
//
// This function is the function that compute the color at the intersection point
// of a ray defined by a position and a direction. Note that thus function is recursive (it calls itself).
//
// If the material of the intersected object is either reflective or reflective and refractive,
// then we compute the reflection/refracton direction and cast two new rays into the scene
// by calling the castRay() function recursively. When the surface is transparent, we mix
// the reflection and refraction color using the result of the fresnel equations (it computes
// the amount of reflection and refractin depending on the surface normal, incident view direction
// and surface refractive index).
//
// If the surface is duffuse/glossy we use the Phong illumation model to compute the color
// at the intersection point.
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    if (depth > this->maxDepth) {
        return Vector3f(0.0,0.0,0.0);
    }
    Intersection intersection = Scene::intersect(ray);
    Material *m = intersection.m;
    Object *hitObject = intersection.obj;
    Vector3f hitColor = this->backgroundColor;
//    float tnear = kInfinity;
    Vector2f uv;
    uint32_t index = 0;
    if(intersection.happened) {
        //return Vector3f(0, 0, 0);
        //std::cout << "hit " << intersection.coords << std::endl;
        Vector3f hitPoint = intersection.coords;
        Vector3f N = intersection.normal; // normal
        Vector2f st; // st coordinates
        hitObject->getSurfaceProperties(hitPoint, ray.direction, index, uv, N, st);
//        Vector3f tmp = hitPoint;
        switch (m->getType()) {
            case REFLECTION_AND_REFRACTION:
            {
                hitPoint = computeReflectionAndFefraction(ray, depth, hitPoint, N, m);
                break;
            }
            case REFLECTION:
            {
                hitColor = computeReflection(ray, depth, hitPoint, N, m);
				break;
            }
           case DIFFUSE_AND_GLOSSY :
            {
			   hitColor = computeDiffuseAndGlossy(ray, depth, hitPoint, N, m, st, hitObject);
                break;
            }
           default : 
           {
               hitColor = computeSubsurfaceScattering(ray, depth, hitPoint, N, m, st, hitObject);
           }
        }
    }

    return hitColor;
}

    // Compute Fresnel equation
//
// \param I is the incident view direction
//
// \param N is the normal at the intersection point
//
// \param ior is the material refractive index
//
// \param[out] kr is the amount of light reflected
    static void fresnel(const Vector3f &I, const Vector3f &N, const float &ior, float &kr)
    {
        float cosi = clamp(-1, 1, dotProduct(I, N));
        float etai = 1, etat = ior;
        if (cosi > 0) {  std::swap(etai, etat); }
        // Compute sini using Snell's law
        float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
        // Total internal reflection
        if (sint >= 1) {
            kr = 1;
        }
        else {
            float cost = sqrtf(std::max(0.f, 1 - sint * sint));
            cosi = fabsf(cosi);
            float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            kr = (Rs * Rs + Rp * Rp) / 2;
        }
        // As a consequence of the conservation of energy, transmittance is given by:
        // kt = 1 - kr;
    }
Vector3f Scene::computeReflectionAndFefraction(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const
{
	Vector3f reflectionDirection = normalize(reflect(ray.direction, N));
	Vector3f refractionDirection = normalize(refract(ray.direction, N, m->ior));
	Vector3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
								 hitPoint - N * EPSILON :
								 hitPoint + N * EPSILON;
	Vector3f refractionRayOrig = (dotProduct(refractionDirection, N) < 0) ?
								 hitPoint - N * EPSILON :
								 hitPoint + N * EPSILON;
	Vector3f reflectionColor = castRay(Ray(reflectionRayOrig, reflectionDirection), depth + 1);
	Vector3f refractionColor = castRay(Ray(refractionRayOrig, refractionDirection), depth + 1);
	float kr;
	fresnel(ray.direction, N, m->ior, kr);
	return reflectionColor * kr + refractionColor * (1 - kr);
}
Vector3f Scene::computeReflection(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const
{
    float kr;
	fresnel(ray.direction, N, m->ior, kr);
	Vector3f reflectionDirection = reflect(ray.direction, N);
	Vector3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
								 hitPoint + N * EPSILON :
								 hitPoint - N * EPSILON;
	return  castRay(Ray(reflectionRayOrig, reflectionDirection),depth + 1) * kr;
}
Vector3f Scene::computeDiffuseAndGlossy(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m, const Vector2f& st, Object * hitObject) const
{
	// [comment]
	// We use the Phong illumation model int the default case. The phong model
	// is composed of a diffuse and a specular reflection component.
	// [/comment]
	Vector3f lightAmt = 0, specularColor = 0;
	Vector3f shadowPointOrig = (dotProduct(ray.direction, N) < 0) ?
							   hitPoint + N * EPSILON :
							   hitPoint - N * EPSILON;
	// [comment]
	// Loop over all lights in the scene and sum their contribution up
	// We also apply the lambert cosine law
	// [/comment]
	for (uint32_t i = 0; i < get_lights().size(); ++i)
	{
		auto area_ptr = dynamic_cast<AreaLight*>(this->get_lights()[i].get());
		if (area_ptr)
		{
			// Do nothing for this assignment
		}
		else
		{
			Vector3f lightDir = get_lights()[i]->position - hitPoint;
			// square of the distance between hitPoint and the light
			float lightDistance2 = dotProduct(lightDir, lightDir);
			lightDir = normalize(lightDir);
			float LdotN = std::max(0.f, dotProduct(lightDir, N));
			Object *shadowHitObject = nullptr;
			float tNearShadow = kInfinity;
			// is the point in shadow, and is the nearest occluding object closer to the object than the light itself?
			bool inShadow = bvh->Intersect(Ray(shadowPointOrig, lightDir)).happened;
			lightAmt += (1 - inShadow) * get_lights()[i]->intensity * LdotN;
			Vector3f reflectionDirection = reflect(-lightDir, N);
			specularColor += powf(std::max(0.f, -dotProduct(reflectionDirection, ray.direction)),
								  m->specularExponent) * get_lights()[i]->intensity;
		}
	}
	return lightAmt * (hitObject->evalDiffuseColor(st) * m->Kd + specularColor * m->Ks);
}
const int SAMPLE_NUM = 10;
// For Marble
const float Fdr = -1.44 / 1.3 / 1.3 + 0.71 / 1.3 + 0.668 + 0.0636 * 1.3;
const float A = (1 + Fdr) / (1 - Fdr);
const Vector3f SigmaS = Vector3f(2.19, 2.62, 3.0);
const Vector3f SigmaA = Vector3f(0.0021, 0.0041, 0.0071);
const Vector3f SigmaT = SigmaS + SigmaA;
const Vector3f Alpha = Vector3f(SigmaS.x / SigmaT.x, SigmaS.y / SigmaT.y, SigmaS.z / SigmaT.z);
const Vector3f SigmaTR = SigmaT * Vector3f(std::sqrt(3 * (1 - Alpha.x)), std::sqrt(3 * (1 - Alpha.y)), std::sqrt(3 * (1 - Alpha.z)));
const Vector3f Ld= SigmaTR.Inverse();
const Vector3f D = Ld / (3.5 + 100 * (A - 0.33) * (A - 0.33) * (A - 0.33) * (A - 0.33));

void Scene::samplePoint(const Vector3f & source, float R, const Vector3f& N, Intersection & target, float & pdf) const
{
	float theta = 2.0 * M_PI * get_random_float();
	float r =  R * get_random_float();
	Vector3f dir(std::cos(theta), std::sin(theta), 1.0);
	// TODO: compute world dir
	Vector3f pos = source + dir;
	Ray ray = Ray(pos, -N);
    target = Scene::intersect(ray);
	float area = r * r * M_PI;
	pdf = 1.0f / area;
}
static Vector3f Rd(const Vector3f& r)
{
	Vector3f e1 = -r * D.Inverse();
	Vector3f e3 = -r * D.Inverse() / 3.0;
	Vector3f m = D* r* M_PI * 8;
	return Vector3f(std::exp(e1.x) + std::exp(e3.x), std::exp(e1.y) + std::exp(e3.y), std::exp(e1.z) + std::exp(e3.z));
}
static Vector3f S(const Vector3f& po, const Vector3f& wo, const Vector3f& No, float ioro,
	const Vector3f& pi, const Vector3f& wi, const Vector3f& Ni, float iori)
{
    float fo;
	fresnel(wo, No, ioro, fo);
	float fi;
	fresnel(wi, Ni, iori, fi);
	float d = std::abs(po.x - pi.x) + std::abs(po.y - pi.y) + std::abs(po.z - pi.z);
	return Rd(d) * fo * fi / M_PI;
}
Vector3f Scene::computeSubsurfaceScattering(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m, const Vector2f& st, Object * hitObject) const
{
	Vector3f sumLightColor;
	Vector2f ist; // st coordinates
	uint32_t index = 0;
	Vector2f iuv;
	for (int j = 0; j < SAMPLE_NUM; j++)
	{
		Vector3f lightAmt = 0, specularColor = 0;
		Intersection inter;
		float pdf;
		samplePoint(hitPoint, 1, N, inter, pdf);
		if (!inter.happened)
			continue;
		for (uint32_t i = 0; i < get_lights().size(); ++i)
		{
			auto area_ptr = dynamic_cast<AreaLight*>(this->get_lights()[i].get());
			if (area_ptr)
				continue;
			Material* mi = inter.m;
			Object* inObject = inter.obj;
			const Vector3f& pi = inter.coords;

			Vector3f Ni = inter.normal; // normal
			Vector3f lightDir = get_lights()[i]->position - inter.coords;
			lightDir = normalize(lightDir);
			inObject->getSurfaceProperties(pi, lightDir, index, iuv, Ni, ist);
			sumLightColor += S(hitPoint, ray.direction, N, m->ior, inter.coords, lightDir, Ni, mi->ior) / pdf;
		}

	}
	return sumLightColor;

}