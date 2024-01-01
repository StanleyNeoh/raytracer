#ifndef UTILS_H
#define UTILS_H

#include <limits>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double deg_to_rad(double deg) {
    return deg * pi / 180.0;
}

#endif