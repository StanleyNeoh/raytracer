#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr, std::make_shared, std::sqrt;
using std::cout, std::clog, std::max;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double deg_to_rad(double deg) {
    return deg * pi / 180.0;
}

// Common Headers
#include "ray.hpp"
#include "vec3.hpp"

#endif