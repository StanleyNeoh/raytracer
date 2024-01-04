#include "dielectric.hpp"
#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"
#include "material.hpp"

dielectric::dielectric(double ri): attenuation(color(1,1,1)), ri(ri) {}

dielectric::dielectric(const color& attenuation, double ri): attenuation(attenuation), ri(ri) {}

bool dielectric::scatter(
    const ray& r_in,
    const hit_record& rec,
    ray& scattered
) const {
    double rel_ri = rec.front_face ? (1.0 / ri): ri;
    double cos = vec3::dot(r_in.unit_direction(), -rec.unit_normal);
    if (fabs(cos) > 1.0) std::clog << "Oh No " << cos << "\n"; 
    double sin = sqrt(1.0 - cos * cos);
    bool isTIR = rel_ri * sin > 1.0;
    bool isReflected = reflectance(cos, rel_ri) > random_double();

    vec3 unit_direction;
    if (isTIR || isReflected) {
        unit_direction = r_in.unit_direction().reflect(rec.unit_normal);
    } else {
        unit_direction = r_in.unit_direction().refract(rec.unit_normal, rel_ri);
    }
    scattered = ray(rec.p, unit_direction);
    return true;
}

bool dielectric::transform(color& scattered_color) const {
    scattered_color = attenuation * scattered_color;
    return true;
}

double dielectric::reflectance(double cosine, double rel_ri) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - rel_ri) / (1 + rel_ri);
    r0 *= r0;
    return r0 + (1 - r0) * pow(1 - cosine, 5);
}
