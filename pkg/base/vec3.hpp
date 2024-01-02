#ifndef VEC3_H
#define VEC3_H

#include "utils.hpp"
#include <cmath>
#include <iostream>

using std::sqrt, std::ostream;

class vec3;
class hit_record;
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
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[1]) < s);
        }

        vec3 unit() const {
            return *this / this->length();
        }

        vec3 with_length(double l) const {
            return l * this->unit();
        }

        // Preserves length
        vec3 reflect(const vec3& unit_normal) const {
            return *this - 2*dot(*this, unit_normal)*unit_normal;
        }

        // Preserves length
        // `unit_normal` taken to be against `*this`
        vec3 refract(const vec3& unit_normal, double rel_refractive_index) {
            double R_cos = dot(*this, unit_normal);
            vec3 r_out_par = rel_refractive_index * (*this -  R_cos * unit_normal);
            vec3 r_out_perp = -unit_normal * sqrt(this->length_squared() - r_out_par.length_squared());
            return r_out_par + r_out_perp;
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

