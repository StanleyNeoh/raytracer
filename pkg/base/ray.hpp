#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
    private:
        point3 orig;
        vec3 unit_dir; // Always unit

    public:
        ray() {}
        ray(const point3& orig, const vec3& unit_dir): orig(orig), unit_dir(unit_dir) {}
        point3 origin() const { return orig; }
        vec3 unit_direction() const { return unit_dir; }

        point3 at(double t) const {
            return orig + t * unit_dir;
        }
};

#endif
