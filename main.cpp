#include "pkg/raytracer.hpp"

int main() {
    // World
    hittable_list world;
    shared_ptr<material> turq = make_shared<metal>(color(0.5, 1, 1), 0.0);
    shared_ptr<material> red = make_shared<metal>(color(1, 0.5, 0.5), 0.1);
    shared_ptr<material> green = make_shared<metal>(color(0.5, 1, 0.5), 0.3);
    shared_ptr<material> blue = make_shared<metal>(color(0.5, 0.5, 1), 0.5);
    shared_ptr<material> clear = make_shared<dielectric>(color(1, 1, 1), 1.3);

    shared_ptr<material> white = make_shared<isotropic>(color(1, 1, 1));
    shared_ptr<material> gray = make_shared<lambertian>(color(0.5, 0.5, 0.5));

    // Main sphere
    world.add(make_shared<sphere>(point3(0, 0, 1), 1, turq));

    // hollow sphere
    world.add(make_shared<sphere>(point3(1, 2, 1.35), 0.25, clear));
    world.add(make_shared<sphere>(point3(1, 2, 1.35), -0.2, clear));

    world.add(make_shared<sphere>(point3(2, 0, 0), 0.25, red));
    world.add(make_shared<sphere>(point3(1, 0, 0), 0.25, green));
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.25, blue));
    world.add(make_shared<sphere>(point3(0, 2, 0), 0.25, white));

    // ground
    world.add(make_shared<sphere>(point3(0, 0, -100.5), 100, gray));

    camera cam;
    cam.vfov = 90;
    cam.vup = vec3(0, 0, 1);
    cam.lookfrom = point3(2, 2, 2);
    cam.lookat = point3(0, 0, 1);
    cam.aperture = 0.05;

    cam.render_ppm(std::cout, world);
}
