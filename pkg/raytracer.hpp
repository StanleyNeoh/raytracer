#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <cmath>
#include <memory>

// Usings
using std::shared_ptr, std::make_shared, std::sqrt;
using std::cout, std::clog, std::max;

// Common Headers
#include "base/utils.hpp"
#include "base/ray.hpp"
#include "base/vec3.hpp"
#include "base/color.hpp"
#include "base/interval.hpp"

#include "hittable/hittable.hpp"
#include "hittable/hittable_list.hpp"
#include "hittable/sphere.hpp"

#endif