#ifndef VEC3_H
#define VEC3_H

#include "utils.hpp"
#include <cmath>
#include <iostream>

using std::sqrt, std::ostream;

class vec3;
inline ostream& operator<<(std::ostream &out, const vec3 &v);
inline vec3 operator+(const vec3 &u, const vec3 &v);
inline vec3 operator-(const vec3 &u, const vec3 &v);
inline vec3 operator*(const vec3 &u, const vec3 &v);
inline vec3 operator*(double t, const vec3 &v);
inline vec3 operator*(const vec3 &v, double t);
inline vec3 operator/(const vec3 &v, double t);

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

        bool near_zero() const {
            double s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[0]) < s) && (fabs(e[0]) < s);
        }

        vec3 unit() const {
            return *this / this->length();
        }

        vec3 with_length(double l) const {
            return l * this->unit();
        }

        vec3 reflect(const vec3& unit_normal) const {
            return *this - 2*dot(*this, unit_normal)*unit_normal;
        }

        static double dot(const vec3 &u, const vec3 &v) {
            return u.e[0] * v.e[0]
                + u.e[1] * v.e[1]
                + u.e[2] * v.e[2];
        }

        static vec3 cross(const vec3 &u, const vec3 &v) {
            return vec3(
                u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]
            );
        }
        
        // Creates a random unit vector 
        static vec3 random_unit() {
            double a = random_double() * pi;
            double b = random_double() * 2 * pi;
            double r = sin(a);
            return vec3(r * cos(b), r * sin(b), cos(a));
        }

        // Creates a random unit vector for isotropic scattering
        static vec3 scatter_isotropic(const vec3& unit_normal) {
            vec3 unit_vector = random_unit();
            if (dot(unit_vector, unit_normal) < 0) unit_vector = -unit_vector;
            return unit_vector;
        }

        // Creates a random unit vector for lambertian scattering
        static vec3 scatter_lambertian(const vec3& unit_normal) {
            vec3 scatter_direction = unit_normal + random_unit();
            if (scatter_direction.near_zero()) scatter_direction = unit_normal;
            return scatter_direction;
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

#endif

