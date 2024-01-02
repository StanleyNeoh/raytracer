#ifndef HITTABLE_H
#define HITTABLE_H

#include "../base/interval.hpp"
#include "../base/ray.hpp"
#include "../base/vec3.hpp"

class material;

class hit_record {
    public:
        point3 p;
        vec3 unit_normal;
        shared_ptr<material> mat;
        double t;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& out_unit_normal) {
            // Sets the hit record normal vector
            // `out_unit_normal` always against the ray (outward wrt surface).
            front_face = vec3::dot(r.unit_direction(), out_unit_normal) < 0;
            unit_normal = front_face ? out_unit_normal : -out_unit_normal;
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
