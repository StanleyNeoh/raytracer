#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

class lambertian: public material {
    public:
        lambertian(const color& a);

        bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const override;

        bool transform(color& scattered_color) const override;

    private:
        color albedo;
};

#endif