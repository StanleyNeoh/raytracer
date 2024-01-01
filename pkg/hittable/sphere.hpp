#ifndef SPHERE_H
#define SPHERE_H

#include "../base/interval.hpp"
#include "hittable.hpp"

class sphere: public hittable {
    private:
        point3 center;
        double radius;

    public:
        sphere(point3 _center, double _radius): center(_center), radius(_radius) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = r.origin() - center;
            double a = r.direction().length_squared();
            double half_b = dot(oc, r.direction());
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
            return true;
        }
};
#endif
