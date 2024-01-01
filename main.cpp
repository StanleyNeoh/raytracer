#include "pkg/raytracer.hpp"

int main() {
    // World
    hittable_list world;
    shared_ptr<material> red = make_shared<metal>(color(1, 0.5, 0.5), 0.1);
    shared_ptr<material> green = make_shared<metal>(color(0.5, 1, 0.5), 0.3);
    shared_ptr<material> blue = make_shared<metal>(color(0.5, 0.5, 1), 0.8);
    shared_ptr<material> white = make_shared<lambertian>(color(0.5, 0.5, 0.5));

    world.add(make_shared<sphere>(point3(0, 0.5, 2), 1, red));
    world.add(make_shared<sphere>(point3(1, 0, 1), 0.25, green));
    world.add(make_shared<sphere>(point3(-1, 0, 1), 0.25, blue));
    world.add(make_shared<sphere>(point3(0, -100.5, 1), 100, white));

    camera cam(point3(0, 0, 0), vec3(0, 0, 1));
    cam.render_ppm(std::cout, world);
}
