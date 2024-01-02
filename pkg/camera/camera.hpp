#ifndef CAMERA_H
#define CAMERA_H

#include "../base/utils.hpp"
#include "../base/vec3.hpp"
#include "../base/interval.hpp"
#include "../hittable/hittable.hpp"

#include <iostream>
#include <chrono>

using namespace std::chrono;

class camera {
    public:
        int img_w = 400;
        double aspect_ratio  = 16.0 / 9.0;
        int samples_per_pixel = 10;
        int max_depth = 10;

        point3 center;
        vec3 direction; // length is focal length

        camera(point3 _center, vec3 _direction): center(_center), direction(_direction) {}

        void render_ppm(ostream& out, const hittable& world) {
            auto start_time = high_resolution_clock::now();
            setup();
            out << "P3\n" << num_pixel_u << ' ' << num_pixel_v << "\n255\n";
            for (int vi = 0; vi < num_pixel_v; vi++) {
                std::clog << "\rScanlines remaining: " << (num_pixel_v - vi) << ' ' << std::flush;
                for (int ui = 0; ui < num_pixel_u; ui++) {
                    color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(ui, vi);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(out, pixel_color);
                }
            }
            auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start_time);
            std::clog << "\rDone in " << duration.count() << "μs.      \n";
        }
        
    private:
        point3 pixel00_loc;
        vec3 pixel_du;
        vec3 pixel_dv;
        int num_pixel_u;
        int num_pixel_v;

        void setup() {
            num_pixel_v = std::max(1, static_cast<int>(img_w / aspect_ratio));
            num_pixel_u = img_w;

            double vp_width_v = 2.0;
            double vp_width_u = vp_width_v * (static_cast<double>(num_pixel_u) / num_pixel_v);
            vec3 vp_v = vec3(0, -vp_width_v, 0);
            vec3 vp_u = vec3::cross(direction, vp_v).with_length(vp_width_u);

            pixel_dv = vp_v / num_pixel_v;
            pixel_du = vp_u / num_pixel_u;
            pixel00_loc = center + direction 
                - 0.5 * (vp_v + vp_u)
                + 0.5 * (pixel_du + pixel_dv);
        }


        // Get a randomly sampled camera ray for the pixel at location ui, vi
        ray get_ray(int ui, int vi) {
            double rui = random_double() - 0.5 + ui; 
            double rvi = random_double() - 0.5 + vi; 
            point3 pixel_center = pixel00_loc + (rui * pixel_du) + (rvi * pixel_dv);
            vec3 ray_dir = pixel_center - center;
            return ray(center, ray_dir.unit());
        }

        color ray_color(const ray& r, int depth, const hittable& world) {
            hit_record rec;
            if (depth <= 0) return color(0,0,0);

            // Lower bound of interval set to 0.001 to prevent shadow acne.
            // This is when the new_r appears under the surface and gets and extra hit.
            if (world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color c(0, 0, 0);
                if (rec.mat->scatter(r, rec, scattered)) {
                    c = ray_color(scattered, depth-1, world);
                }
                rec.mat->transform(c);
                return c;
            }

            double a = 0.5 * (r.unit_direction().y() + 1.0);
            return std::move((1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0));
        }

        void write_color(ostream& out, color pixel_color) const {
            double r = pixel_color.x() / samples_per_pixel;
            double g = pixel_color.y() / samples_per_pixel;
            double b = pixel_color.z() / samples_per_pixel;

            // Apply gamma transform
            r = sqrt(r);
            g = sqrt(g);
            b = sqrt(b);

            // Write the translated [0, 255] value of each color component.
            static const interval intensity(0.000, 0.999);
            out << static_cast<int>(255.999 * intensity.clamp(r)) << ' '
                << static_cast<int>(255.999 * intensity.clamp(g)) << ' '
                << static_cast<int>(255.999 * intensity.clamp(b)) << '\n';
        }
};

#endif