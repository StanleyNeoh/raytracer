#include "vec3.hpp"

vec3::vec3(): e{0, 0, 0}  {}
vec3::vec3(double e0, double e1, double e2): e{e0,e1,e2} {}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3 vec3::operator-() const {
    return vec3(-e[0], -e[1], -e[2]);
}

double vec3::operator[](int i) const {
    return e[i];
}

double& vec3::operator[](int i) {
    return e[i];
}

vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3& vec3::operator/=(double t) {
    return *this *= 1/t;
}

double vec3::length_squared() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

double vec3::length() const {
    return sqrt(length_squared());
}

bool vec3::near_zero() const {
    double s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[1]) < s);
}

vec3 vec3::unit() const {
    return *this / this->length();
}

vec3 vec3::with_length(double l) const {
    return l * this->unit();
}

vec3 vec3::reflect(const vec3& unit_normal) const {
    return *this - 2*dot(*this, unit_normal)*unit_normal;
}

vec3 vec3::refract(const vec3& unit_normal, double rel_refractive_index) {
    double R_cos = dot(*this, unit_normal);
    vec3 r_out_par = rel_refractive_index * (*this -  R_cos * unit_normal);
    vec3 r_out_perp = -unit_normal * sqrt(this->length_squared() - r_out_par.length_squared());
    return r_out_par + r_out_perp;
}

double vec3::dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

vec3 vec3::cross(const vec3 &u, const vec3 &v) {
    return vec3(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

vec3 vec3::random() {
    return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 vec3::random_unit() {
    double a = random_double() * pi;
    double b = random_double() * 2 * pi;
    double r = sin(a);
    return vec3(r * cos(b), r * sin(b), cos(a));
}


vec3 vec3::random_unit(vec3 unit_u, vec3 unit_v) {
    double theta = random_double() * 2 * pi;
    return cos(theta) * unit_u + sin(theta) * unit_v;
}
