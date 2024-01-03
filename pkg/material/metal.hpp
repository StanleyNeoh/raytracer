#ifndef METAL_H
#define METAL_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

class metal: public material {
    public:
        metal(const color& a, double fuzz): albedo(a), fuzz(std::min(1.0, fuzz)) {};

        bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const override {
            vec3 unit_direction = r_in.unit_direction().reflect(rec.unit_normal); 
            if (fuzz > 0.0) {
                unit_direction = (unit_direction + fuzz * vec3::random_unit()).unit();
            }
            scattered = ray(rec.p, unit_direction);
            return true;
        }

        bool transform(color& scattered_color) const override {
            scattered_color = albedo * scattered_color;
            return true;
        }

    private:
        color albedo;
        double fuzz;
};

#endif