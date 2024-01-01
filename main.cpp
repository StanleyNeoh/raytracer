#include "pkg/raytracer.hpp"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_dir = unit_vector(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Image 
    double aspect_ratio = 16.0 / 9.0;
    int img_w = 400;
    int img_h = max(1, static_cast<int>(img_w / aspect_ratio));

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, 3), 0.5));
    world.add(make_shared<sphere>(point3(2, 2, 5), 0.25));
    world.add(make_shared<sphere>(point3(0, -100.5, 1), 100));

    // Camera
    double focal_l = 1.0;
    double vp_h = 2.0;
    double vp_w = vp_h * (static_cast<double>(img_w) / img_h);
    point3 camera_center = point3(0, 0, 0);

    // Basis for viewport
    vec3 vp_normal = vec3(0, 0, focal_l);
    vec3 vp_u = vec3(vp_w, 0, 0);
    vec3 vp_v = vec3(0, -vp_h, 0);
    vec3 pixel_du = vp_u / img_w;
    vec3 pixel_dv = vp_v / img_h;

    vec3 vp_topleft = camera_center + vp_normal - vp_u/2 - vp_v/2;
    vec3 pixel00_loc = vp_topleft + 0.5 * (pixel_du + pixel_dv);

    // Render
    cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

    for (int j = 0; j < img_h; j++) {
        clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;

        for (int i = 0; i < img_w; i++) {
            vec3 pixel_center = pixel00_loc + (i * pixel_du) + (j * pixel_dv);
            vec3 ray_dir = pixel_center - camera_center;
            ray r(camera_center, ray_dir);

            color pixel_color = ray_color(r, world);
            write_color(cout, pixel_color);
        }
    }
    clog << "\rDone.                     \n";
}
