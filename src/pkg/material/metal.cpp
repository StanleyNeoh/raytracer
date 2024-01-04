#include "metal.hpp"
#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

metal::metal(const color& a, double fuzz): albedo(a), fuzz(std::min(1.0, fuzz)) {}

bool metal::scatter(
    const ray& r_in,
    const hit_record& rec,
    ray& scattered
) const {
    vec3 unit_direction = r_in.unit_direction().reflect(rec.unit_normal); 
    if (fuzz > 0.0) {
        unit_direction = (unit_direction + fuzz * vec3::random_unit()).unit();
    }
    scattered = ray(rec.p, unit_direction);
    return true;
}

bool metal::transform(color& scattered_color) const {
    scattered_color = albedo * scattered_color;
    return true;
}
