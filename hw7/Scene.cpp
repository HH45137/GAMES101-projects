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
    auto result_color = Vector3f(0.0f);
    Intersection intersection = intersect(ray);

    if (!intersection.happened) {
        return result_color;
    }
    if (intersection.m->hasEmission()) {
        return intersection.m->getEmission();
    }

    // Direct Lighting
    Vector3f direct_light = {};
    {
        Intersection light_intersection = {};
        float pdf_light = 0.0f;
        sampleLight(light_intersection, pdf_light);

        Vector3f p = intersection.coords;
        Vector3f x = light_intersection.coords;
        Vector3f N = intersection.normal.normalized();
        Vector3f NN = light_intersection.normal.normalized();
        Vector3f emit = light_intersection.emit;
        // 从着色点指向光源的方向
        Vector3f ws = (x - p).normalized();
        // 出射方向（从表面指向相机）
        Vector3f wo = -ray.direction;

        // 可见性测试
        Ray p_to_light_ray(p, ws);
        Intersection shadow_inter = intersect(p_to_light_ray);
        float dist_to_light = (x - p).norm();
        bool visible = (shadow_inter.happened && std::abs(shadow_inter.distance - dist_to_light) < EPSILON);

        if (visible && pdf_light > 0.0f) {
            // BSDF 参数顺序：出射方向 wo，入射方向 ws
            Vector3f bsdf = intersection.m->eval(wo, ws, N);

            float cos_theta_p = std::max(0.0f, dotProduct(ws, N));
            float cos_theta_x = std::max(0.0f, dotProduct(-ws, NN));

            direct_light = emit * bsdf * cos_theta_p * cos_theta_x / (dist_to_light * dist_to_light) / pdf_light;
        }
    }

    result_color += direct_light;

    return result_color;
}