#ifndef METAL_H
#define METAL_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

class metal: public material {
    public:
        metal(const color& a): albedo(a) {};
        bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const override {
            vec3 reflected = vec3::reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }
        bool transform(color& scattered_color) const override {
            scattered_color = albedo * scattered_color;
            return true;
        }

    private:
        color albedo;
};

#endif