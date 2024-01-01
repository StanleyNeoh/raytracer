#ifndef MATERIAL_H
#define MATERIAL_H

#include "../base/vec3.hpp"
#include "../base/ray.hpp"

class hit_record;

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const = 0;

        virtual bool transform(color& scattered_color) const = 0;
};
#endif
