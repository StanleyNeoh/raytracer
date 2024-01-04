#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include "hittable.hpp"
#include "../base/ray.hpp"

using std::shared_ptr, std::vector;

class hittable_list: public hittable {
    public:
        vector<shared_ptr<hittable>> objects;

        hittable_list();
        hittable_list(shared_ptr<hittable> object);
        void clear();
        void add(shared_ptr<hittable> object);
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif
