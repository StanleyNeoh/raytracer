#ifndef CAMERA_H
#define CAMERA_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"

// We have 2 coordinate systems, viewport and world
// For our viewport coordinate system, we want to think of:
// - `u` is right (correspond to width), 
// - `v` is down (correspond to height),
// - `w` is forward
//
// Hence, our viewport coordinate system is right-handed. w ~ (u x v)
//
// For our world coordinate system, we will use the typical right-handed cartesian basis `i, j, k`.
class camera {
    public:
        // Parameters
        int img_w = 400;
        double aspect_ratio  = 16.0 / 9.0;
        double vfov = 90;
        double aperture = 0.0;
        double focal_length = -1.0; // if `focal_length < 0`, focal_length determined by what is looking at

        point3 lookfrom = point3(0, 0, 0);
        point3 lookat = point3(0, 1, 0); // length is focal length
        vec3 vup = vec3(0, 0, 1);
        
        // Hyperparameters
        int samples_per_pixel = 10;
        int max_depth = 10;

        void render_ppm(ostream& out, const hittable& world);
        
    private:
        int img_h;
        vec3 u, v, w;   // unit vector
        point3 pixel00_loc;
        vec3 pixel_du;
        vec3 pixel_dv;

        void setup();

        // Get a randomly sampled camera ray for the pixel at location ui, vi
        ray get_ray(int ui, int vi);

        color ray_color(const ray& r, int depth, const hittable& world);

        void write_color(ostream& out, color pixel_color) const;
};

#endif