#ifndef HITTABLE_H
#define HITTABLE_H

#include "../base/interval.hpp"
#include "../base/ray.hpp"
#include "../base/vec3.hpp"
#include <memory>

class material;

class hit_record {
    public:
        point3 p;
        vec3 unit_normal;   // `unit_normal` always against the ray (outward wrt surface).
        shared_ptr<material> mat;
        double t;
        bool front_face;    // whether ray hit the front face (outer face)

        // Sets the hit record normal vector
        void set_face_normal(const ray& r, const vec3& front_unit_normal) {
            front_face = vec3::dot(r.unit_direction(), front_unit_normal) < 0;
            unit_normal = front_face ? front_unit_normal : -front_unit_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(
            const ray& r, 
            interval ray_t,
            hit_record& rec) const = 0;
};

#endif
