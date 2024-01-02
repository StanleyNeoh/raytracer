#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

class lambertian: public material {
    public:
        lambertian(const color& a): albedo(a) {}

        bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const override {
            (void) r_in;
            vec3 scatter_direction = rec.unit_normal + vec3::random_unit();
            if (scatter_direction.near_zero()) scatter_direction = rec.unit_normal;
            scattered = ray(rec.p, scatter_direction.unit());
            return true;
        };

        bool transform(color& scattered_color) const override {
            scattered_color = albedo * scattered_color;
            return true;
        }

    private:
        color albedo;
};

#endif