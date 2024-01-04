#ifndef VEC3_H
#define VEC3_H

#include "utils.hpp"
#include <cmath>
#include <iostream>

using std::sqrt, std::ostream;

class vec3 {
    public:
        double e[3];

        vec3();
        vec3(double e0, double e1, double e2);

        double x() const;
        double y() const;
        double z() const;

        vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);
        vec3& operator+=(const vec3 &v);
        vec3& operator*=(double t);
        vec3& operator/=(double t);
        double length_squared() const;
        double length() const;
        bool near_zero() const;
        vec3 unit() const;
        vec3 with_length(double l) const;

        // Preserves length
        vec3 reflect(const vec3& unit_normal) const;

        // Preserves length
        // `unit_normal` taken to be against `*this`
        vec3 refract(const vec3& unit_normal, double rel_refractive_index);

        static double dot(const vec3 &u, const vec3 &v);
        static vec3 cross(const vec3 &u, const vec3 &v);

        // Creates a random vector in [0, 1)^3
        static vec3 random();

        // Creates a random vector in [min, max)^3
        static vec3 random(double min, double max);
        
        // Creates a random unit vector 
        static vec3 random_unit();
        
        // Create a random unit vector on a disk
        // `unit_u` and `unit_v` are orthonormal basis
        static vec3 random_unit(vec3 unit_u, vec3 unit_v);
};

using point3 = vec3;
using color = vec3;

//  Vector Utility Functions

inline ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(
        u.e[0] + v.e[0],
        u.e[1] + v.e[1],
        u.e[2] + v.e[2]
    );
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(
        u.e[0] - v.e[0],
        u.e[1] - v.e[1],
        u.e[2] - v.e[2]
    );
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(
        u.e[0] * v.e[0],
        u.e[1] * v.e[1],
        u.e[2] * v.e[2]
    );
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(
        t * v.e[0],
        t * v.e[1],
        t * v.e[2]
    );
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t) {
    return (1/t) * v;
}

#endif

