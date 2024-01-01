#ifndef CAMERA_H
#define CAMERA_H

#include "../base/vec3.hpp"
#include "../hittable/hittable.hpp"

#include <iostream>

class camera {
    public:
        int img_w = 400;
        double aspect_ratio  = 16.0 / 9.0;

        camera(point3 _center, vec3 _direction): center(_center), direction(_direction) {}

        camera(): center(point3(0,0,0)), direction(vec3(0,0,1)) {
            std::clog << direction << "== \n";
        }

        void render_ppm(ostream& out, const hittable& world) {
            setup();
            out << "P3\n" << num_pixel_u << ' ' << num_pixel_v << "\n255\n";
            for (int j = 0; j < num_pixel_u; j++) {
                std::clog << "\rScanlines remaining: " << (num_pixel_v - j) << ' ' << std::flush;

                for (int i = 0; i < img_w; i++) {
                    vec3 pixel_center = pixel00_loc + (i * pixel_du) + (j * pixel_dv);
                    vec3 ray_dir = pixel_center - center;
                    ray r(center, ray_dir);

                    color pixel_color = ray_color(r, world);
                    write_color(out, pixel_color);
                }
            }
            std::clog << "\rDone                     \n";
        }

        void reposition(point3 _center, vec3 _direction) {
            direction = _direction;
            center = _center;
            to_setup = true;
        }
        
    private:
        bool to_setup = true;
        point3 center;
        vec3 direction; // length is focal length
        point3 pixel00_loc;
        vec3 pixel_du;
        vec3 pixel_dv;
        int num_pixel_u;
        int num_pixel_v;

        void setup() {
            if (!to_setup) return;
            to_setup = false;
            num_pixel_v = std::max(1, static_cast<int>(img_w / aspect_ratio));
            num_pixel_u = img_w;

            double vp_width_v = 2.0;
            double vp_width_u = vp_width_v * (static_cast<double>(num_pixel_u) / num_pixel_v);
            vec3 vp_v = vec3(0, -vp_width_v, 0);
            vec3 vp_u = vector_with_length(cross(direction, vp_v), vp_width_u);

            pixel_dv = vp_v / num_pixel_v;
            pixel_du = vp_u / num_pixel_u;
            pixel00_loc = center + direction 
                - 0.5 * (vp_v + vp_u)
                + 0.5 * (pixel_du + pixel_dv);
        }

        color ray_color(const ray& r, const hittable& world) {
            hit_record rec;
            if (world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color(1,1,1));
            }

            vec3 unit_dir = unit_vector(r.direction());
            auto a = 0.5 * (unit_dir.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }

        void write_color(ostream& out, color pixel_color) const {
            // Write the translated [0, 255] value of each color component.
            out << static_cast<int>(255.999 * pixel_color.x()) << ' '
                << static_cast<int>(255.999 * pixel_color.y()) << ' '
                << static_cast<int>(255.999 * pixel_color.z()) << '\n';
        }
};

#endif