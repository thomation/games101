//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"
#include <cmath>

void Scene::buildBVH() {
	printf(" - Generating BVH...\n\n");
	this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray& ray) const
{
	return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection& pos, float& pdf) const
{
	float emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
		}
	}
	float p = get_random_float() * emit_area_sum;
	emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
			if (p <= emit_area_sum) {
				objects[k]->Sample(pos, pdf);
				break;
			}
		}
	}
}

bool Scene::trace(
	const Ray& ray,
	const std::vector<Object*>& objects,
	float& tNear, uint32_t& index, Object** hitObject)
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

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray& ray, int depth) const
{
	// TO DO Implement Path Tracing Algorithm here
	if (depth > this->maxDepth) {
		return Vector3f(0.0, 0.0, 0.0);
	}
	Intersection intersection = Scene::intersect(ray);
	Material* m = intersection.m;
	Object* hitObject = intersection.obj;
	Vector3f hitColor = Vector3f(0, 0, 0);
	//    float tnear = kInfinity;
	Vector2f uv;
	uint32_t index = 0;
	if (intersection.happened) {
		// Light
		//if (intersection.obj->hasEmit()) {
			//hitColor = m->getEmission()/ 255.0f;
			//return hitColor;
		//}
		const Vector3f& shadePoint = intersection.coords;
		Vector3f N = intersection.normal; // normal
		Vector2f st; // st coordinates
		hitObject->getSurfaceProperties(shadePoint, ray.direction, index, uv, N, st);
		const Vector3f wo = - ray.direction;
		Vector3f L_dir = Vector3f(0);
		{
			Intersection lightSample;
			float lightPdf;
			sampleLight(lightSample, lightPdf);
			Vector3f x = lightSample.coords;
			Vector3f ws = normalize(x - shadePoint);
			Ray rayToLight = Ray(shadePoint + ws, ws);
			Intersection lightInter = Scene::intersect(rayToLight);
			if (lightInter.happened && lightInter.obj->hasEmit() && (lightInter.coords - x).norm()< EPSILON)
			{
				auto emit = lightSample.emit;
				auto d = x - shadePoint;
				float d2 = dotProduct(d, d);
				auto f_r = m->eval(wo, ws, N);
				auto cp = std::max(0.0f, dotProduct(ws, N));
				Vector3f NN = lightInter.normal;
				lightInter.obj->getSurfaceProperties(x, ws, index, uv, NN, st);
				auto cl = std::max(0.0f, dotProduct(-ws, NN));
				L_dir = emit * f_r * cp * cl /( d2 * lightPdf + EPSILON);
			}
		}
		Vector3f L_indir = Vector3f(0);
		{
			float ksi = get_random_float();
			if (ksi > RussianRoulette)
				L_indir = 0.0;
			else {
				auto wi = normalize(m->sample(wo, N));
				Ray rayToQ = Ray(shadePoint + wi, wi);
				Intersection objInter = Scene::intersect(rayToQ);
				if (objInter.happened && !objInter.obj->hasEmit()) {
					auto pdf = m->pdf(wo, wi, N);
					auto f_r = m->eval(wo, wi, N);
					auto c = std::max(0.0f, dotProduct(wi, N));
					auto sq = castRay(rayToQ, depth);
					L_indir = sq * f_r * c / (pdf * RussianRoulette);
				}
			}
		}
		hitColor = L_dir + L_indir;
	}
	return hitColor;
}