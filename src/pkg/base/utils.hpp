#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include <cstdlib>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double deg_to_rad(double deg) {
    return deg * pi / 180.0;
}

// Returns a random real from [0, 1)
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Returns a random real from [min, max)
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

#endif