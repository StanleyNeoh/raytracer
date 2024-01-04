#ifndef SPHERE_H
#define SPHERE_H

#include "../base/interval.hpp"
#include "../material/material.hpp"
#include "hittable.hpp"

class sphere: public hittable {
    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;

    public:
        sphere(point3 _center, double _radius, shared_ptr<material> _mat);
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif
