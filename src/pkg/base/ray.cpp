#include "ray.hpp"

#include "vec3.hpp"

ray::ray() {}

ray::ray(const point3& orig, const vec3& unit_dir): orig(orig), unit_dir(unit_dir) {}

point3 ray::origin() const { return orig; }

vec3 ray::unit_direction() const { return unit_dir; }

point3 ray::at(double t) const {
    return orig + t * unit_dir;
}