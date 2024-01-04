#include "lambertian.hpp"
#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

lambertian::lambertian(const color& a): albedo(a) {}

bool lambertian::scatter(
    const ray& r_in,
    const hit_record& rec,
    ray& scattered
) const {
    (void) r_in;
    vec3 scatter_direction = rec.unit_normal + vec3::random_unit();
    if (scatter_direction.near_zero()) scatter_direction = rec.unit_normal;
    scattered = ray(rec.p, scatter_direction.unit());
    return true;
}

bool lambertian::transform(color& scattered_color) const {
    scattered_color = albedo * scattered_color;
    return true;
}
