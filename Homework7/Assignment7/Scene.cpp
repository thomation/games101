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
			Vector3f lightPos = lightSample.coords;
			Vector3f ws = normalize(lightPos - shadePoint);
			Ray ray = Ray(shadePoint + ws, ws);
			Intersection lightIntersction = Scene::intersect(ray);
			if (lightIntersction.happened && lightIntersction.obj->hasEmit() && (lightIntersction.coords - lightPos).norm()< EPSILON)
			{
				auto emit = lightSample.emit / 255.0f;
				auto d2 = (lightPos - shadePoint).norm();
				auto f_r = m->eval(wo, ws, N);
				auto cp = std::max(0.0f, dotProduct(ws, N));
				Vector3f NN = lightIntersction.normal;
				lightIntersction.obj->getSurfaceProperties(lightPos, ws, index, uv, NN, st);
				auto cl = std::max(0.0f, dotProduct(-ws, NN));
				L_dir = emit * f_r * cp * cl /( d2 * lightPdf + EPSILON);
			}
		}
		hitColor = L_dir;
	}
	return hitColor;
}