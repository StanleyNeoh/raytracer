#include "isotropic.hpp"

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

isotropic::isotropic(const color& a): albedo(a) {}

bool isotropic::scatter(
    const ray& r_in,
    const hit_record& rec,
    ray& scattered
) const {
    (void) r_in;
    vec3 unit_direction = vec3::random_unit();
    if (vec3::dot(unit_direction, rec.unit_normal) < 0) unit_direction = -unit_direction;
    scattered = ray(rec.p, unit_direction);
    return true;
}

bool isotropic::transform(color& scattered_color) const {
    scattered_color = albedo * scattered_color;
    return true;
}
