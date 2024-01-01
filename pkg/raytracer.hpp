#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <cmath>
#include <memory>

// Usings
using std::shared_ptr, std::make_shared, std::sqrt;

// Common Headers
#include "base/utils.hpp"
#include "base/ray.hpp"
#include "base/vec3.hpp"
#include "base/interval.hpp"

#include "hittable/hittable.hpp"
#include "hittable/hittable_list.hpp"
#include "hittable/sphere.hpp"

#include "camera/camera.hpp"

#endif