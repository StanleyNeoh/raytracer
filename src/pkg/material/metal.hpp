#ifndef METAL_H
#define METAL_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

class metal: public material {
    public:
        metal(const color& a, double fuzz);

        bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const override;

        bool transform(color& scattered_color) const override;

    private:
        color albedo;
        double fuzz;
};

#endif