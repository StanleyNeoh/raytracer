#include "camera.hpp"

#include "../base/utils.hpp"
#include "../base/vec3.hpp"
#include "../base/interval.hpp"
#include "../hittable/hittable.hpp"

#include <iostream>
#include <chrono>

using namespace std::chrono;


void camera::render_ppm(ostream& out, const hittable& world) {
    auto start_time = high_resolution_clock::now();
    setup();
    out << "P3\n" << img_w << ' ' << img_h << "\n255\n";
    for (int vi = 0; vi < img_h; vi++) {
        std::clog << "\rScanlines remaining: " << (img_h - vi) << ' ' << std::flush;
        for (int ui = 0; ui < img_w; ui++) {
            color pixel_color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(ui, vi);
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(out, pixel_color / samples_per_pixel);
        }
    }
    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start_time);
    std::clog << "\rDone in " << duration.count() / 1000.0 << "ms.           \n";
}

void camera::setup() {
    img_h = std::max(1, static_cast<int>(img_w / aspect_ratio));

    double vp_distance = focal_length > 0 ? focal_length : (lookat - lookfrom).length();
    double vp_h = 2 * vp_distance * tan(deg_to_rad(vfov) / 2);
    double vp_w = vp_h * (static_cast<double>(img_w) / img_h);

    w = (lookat - lookfrom).unit();
    u = vec3::cross(w, vup).unit();
    v = vec3::cross(w, u);

    vec3 w_vp = vp_distance * w;
    vec3 v_vp = vp_h * v;
    vec3 u_vp = vp_w * u;
    pixel_dv = v_vp / img_h;
    pixel_du = u_vp / img_w;

    pixel00_loc = lookfrom 
        + w_vp
        + 0.5 * (pixel_du + pixel_dv - u_vp - v_vp);
}


ray camera::get_ray(int ui, int vi) {
    double rui = random_double() - 0.5 + ui; 
    double rvi = random_double() - 0.5 + vi; 
    point3 to = pixel00_loc + (rui * pixel_du) + (rvi * pixel_dv);
    point3 from = lookfrom + aperture * vec3::random_unit(u, v);
    return ray(from, (to-from).unit());
}

color camera::ray_color(const ray& r, int depth, const hittable& world) {
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

void camera::write_color(ostream& out, color pixel_color) const {
    // Write the translated [0, 255] value of each color component.
    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(255.999 * intensity.clamp(sqrt(pixel_color.x()))) << ' '
        << static_cast<int>(255.999 * intensity.clamp(sqrt(pixel_color.y()))) << ' '
        << static_cast<int>(255.999 * intensity.clamp(sqrt(pixel_color.z()))) << '\n';
}
