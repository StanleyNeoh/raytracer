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
            vec3 unit_direction = vec3::random_unit();
            if (vec3::dot(unit_direction, rec.unit_normal) < 0) unit_direction = -unit_direction;
            scattered = ray(rec.p, unit_direction);
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