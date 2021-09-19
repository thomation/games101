//
// Created by Göksu Güvendiren on 2019-05-14.
//

#pragma once

#include <vector>
#include "Vector.hpp"
#include "Object.hpp"
#include "Light.hpp"
#include "AreaLight.hpp"
#include "BVH.hpp"
#include "Ray.hpp"


class Scene
{
public:
    // setting up options
    int width = 1280;
    int height = 960;
    double fov = 90;
    Vector3f backgroundColor = Vector3f(0.0);
    int maxDepth = 5;

    Scene(int w, int h) : width(w), height(h)
    {}

    void Add(Object *object) { objects.push_back(object); }
    void Add(std::unique_ptr<Light> light) { lights.push_back(std::move(light)); }

    const std::vector<Object*>& get_objects() const { return objects; }
    const std::vector<std::unique_ptr<Light> >&  get_lights() const { return lights; }
    Intersection intersect(const Ray& ray) const;
    BVHAccel *bvh;
    void buildBVH();
    Vector3f castRay(const Ray &ray, int depth) const;
    Vector3f computeReflectionAndFefraction(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const;
    Vector3f computeReflection(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const;
    Vector3f computeDiffuseAndGlossy(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m, const Vector2f& st, Object * hitObject) const;
    Vector3f computeSubsurfaceScattering(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m, const Vector2f& st, Object * hitObject, bool & suc) const;
    bool trace(const Ray &ray, const std::vector<Object*> &objects, float &tNear, uint32_t &index, Object **hitObject);
     // creating the scene (adding objects and lights)
    std::vector<Object* > objects;
    std::vector<std::unique_ptr<Light> > lights;
    std::vector<float> cdfs;

    // Compute reflection direction
    Vector3f reflect(const Vector3f &I, const Vector3f &N) const
    {
        return I - 2 * dotProduct(I, N) * N;
    }

};