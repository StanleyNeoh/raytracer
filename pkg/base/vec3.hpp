#ifndef VEC3_H
#define VEC3_H

#include "utils.hpp"
#include <cmath>
#include <iostream>

using std::sqrt, std::ostream;

class vec3;
inline double dot(const vec3 &u, const vec3 &v);
inline vec3 cross(const vec3 &u, const vec3 &v);
inline vec3 unit_vector(vec3 v);
inline vec3 vector_with_length(vec3 v, double l);

class vec3 {
    public:
        double e[3];

        vec3(): e{0, 0, 0}  {}
        vec3(double e0, double e1, double e2): e{e0,e1,e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const {
            return vec3(-e[0], -e[1], -e[2]);
        }

        double operator[](int i) const {
            return e[i];
        }

        double& operator[](int i) {
            return e[i];
        }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() const {
            return sqrt(length_squared());
        }

        static vec3 random() {
            // Creates a random vector with length < 1
            double p = random_double();
            double a = random_double() * pi;
            double b = random_double() * 2 * pi;
            double r = p * sin(a);
            return vec3(r * cos(b), r * sin(b), p * cos(a));
        }

        static vec3 random_unit() {
            // Creates a random vector with length == 1
            double a = random_double() * pi;
            double b = random_double() * 2 * pi;
            double r = sin(a);
            return vec3(r * cos(b), r * sin(b), cos(a));
        }

        static vec3 random_unit_in_halfplane(const vec3& normal) {
            // Creates a random vector in the direction cwith length == 1
            vec3 unit_vector = random_unit();
            if (dot(unit_vector, normal) < 0) unit_vector = -unit_vector;
            return unit_vector;
        }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
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

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 vector_with_length(vec3 v, double l) {
    return l * unit_vector(v);
}

#endif

