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
            scattered = ray(rec.p, r_in.unit_direction().scatter_lambertian(rec.unit_normal));
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