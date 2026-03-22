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

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
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

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TODO Implement Path Tracing Algorithm here
    // 1 shade(p, wo)
    // 2 sampleLight(inter , pdf_light)
    // 3 Get x, ws, NN, emit from inter
    // 4 Shoot a ray from p to x
    // 5 If the ray is not blocked in the middle
    // 6 L_dir = emit * eval(wo, ws, N) * dot(ws, N) * dot(ws,
    // NN) / |x-p|^2 / pdf_light
    // 7
    // 8 L_indir = 0.0
    // 9 Test Russian Roulette with probability RussianRoulette
    // 10 wi = sample(wo, N)
    // 11 Trace a ray r(p, wi)
    // 12 If ray r hit a non -emitting object at q
    // 13 L_indir = shade(q, wi) * eval(wo, wi, N) * dot(wi, N)
    // / pdf(wo, wi, N) / RussianRoulette
    // 14
    // 15 Return L_dir + L_indir


}