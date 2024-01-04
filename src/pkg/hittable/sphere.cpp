#include "sphere.hpp"

#include "../base/interval.hpp"
#include "../material/material.hpp"
#include "hittable.hpp"
#include <memory>

using std::shared_ptr;

sphere::sphere(point3 _center, double _radius, shared_ptr<material> _mat): center(_center), radius(_radius), mat(_mat) {}

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    double a = r.unit_direction().length_squared();
    double half_b = vec3::dot(oc, r.unit_direction());
    double c = oc.length_squared() - radius * radius;
    double D = half_b * half_b - a * c;
    if (D < 0) return false;
    double sqrt_D = sqrt(D);

    double root = (-half_b - sqrt_D) / a;
    if (!ray_t.surrounds(root)) {
        root = (-half_b + sqrt_D) / a; 
        if (!ray_t.surrounds(root)) return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;
    return true;
}
