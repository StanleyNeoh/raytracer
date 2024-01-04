#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
    private:
        point3 orig;
        vec3 unit_dir; // Always unit

    public:
        ray();
        ray(const point3& orig, const vec3& unit_dir);
        point3 origin() const;

        // Always unit
        vec3 unit_direction() const;
        point3 at(double t) const;
};

#endif
