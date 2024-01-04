#include "hittable.hpp"

#include "../base/interval.hpp"
#include "../base/ray.hpp"
#include "../base/vec3.hpp"
#include <memory>

void hit_record::set_face_normal(const ray& r, const vec3& front_unit_normal) {
    front_face = vec3::dot(r.unit_direction(), front_unit_normal) < 0;
    unit_normal = front_face ? front_unit_normal : -front_unit_normal;
}
