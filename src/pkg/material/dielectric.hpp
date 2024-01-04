#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

class dielectric: public material {
    public:
        dielectric(double ri);
        dielectric(const color& attenuation, double ri);

        bool scatter(
            const ray& r_in,
            const hit_record& rec,
            ray& scattered
        ) const override;

        bool transform(color& scattered_color) const override;

    private:
        color attenuation;
        double ri;

        static double reflectance(double cosine, double rel_ri);
};

#endif
