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
	Intersection intersection = Scene::intersect(ray);
	Vector3f hitColor = Vector3f(0, 0, 0);
	//    float tnear = kInfinity;
	if (intersection.happened) {
		//Light
		if (intersection.obj->hasEmit()) {
			return Vector3f(1);
		}
		hitColor = Shade(intersection, -ray.direction, 0);
	}
	return hitColor;
}
Vector3f Scene::Shade(const Intersection& p, const Vector3f& wo, int depth) const
{
	Vector3f hitColor = Vector3f(0, 0, 0);
	const Vector3f& shadePoint = p.coords;
	Vector3f N = p.normal; // normal
	Vector2f st; // st coordinates
	Material* m = p.m;
	Object* hitObject = p.obj;
	uint32_t index = 0;
	Vector2f uv;
	hitObject->getSurfaceProperties(shadePoint, wo, index, uv, N, st);
	Vector3f L_dir = Vector3f(0);
	{
		Intersection lightSample;
		float lightPdf;
		sampleLight(lightSample, lightPdf);
		Vector3f x = lightSample.coords;
		Vector3f ws = normalize(x - shadePoint);
		Ray rayToLight = Ray(shadePoint + ws * 0.1, ws);
		Intersection lightInter = Scene::intersect(rayToLight);
		if (lightInter.happened && lightInter.obj->hasEmit() && (lightInter.coords - x).norm() < EPSILON)
		{
			auto emit = lightSample.emit;
			auto d = x - shadePoint;
			float d2 = dotProduct(d, d);
			auto f_r = m->eval(wo, ws, N);
			auto cp = std::max(0.0f, dotProduct(ws, N));
			Vector3f NN = lightInter.normal;
			lightInter.obj->getSurfaceProperties(x, ws, index, uv, NN, st);
			auto cl = std::max(0.0f, dotProduct(-ws, NN));
			L_dir = emit * f_r * cp * cl / (d2 * lightPdf);
		}
	}
	Vector3f L_indir = Vector3f(0);
	{
		float ksi = get_random_float();
		if(ksi <= RussianRoulette) {
			auto wi = normalize(m->sample(wo, N));
			Ray rayToQ = Ray(shadePoint + wi * 0.1, wi);
			Intersection q = Scene::intersect(rayToQ);
			if (q.happened && !q.obj->hasEmit()) {
				auto pdf = m->pdf(wo, wi, N);
				auto f_r = m->eval(wo, wi, N);
				auto c = std::max(0.0f, dotProduct(wi, N));
				auto sq = Shade(q, -wi, depth + 1);
				L_indir = sq *f_r* c / (pdf * RussianRoulette);
			}
		}
	}
	hitColor = L_dir + L_indir;
	return hitColor;
}
