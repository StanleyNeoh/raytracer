#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

class isotropic: public material {
    public:
        isotropic(const color& a): albedo(a) {}

        bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const override {
            (void) r_in;
            vec3 scatter_direction = vec3::scatter_isotropic(rec.unit_normal);
            if (scatter_direction.near_zero()) scatter_direction = rec.unit_normal;
            scattered = ray(rec.p, scatter_direction);
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