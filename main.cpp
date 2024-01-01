#include "pkg/raytracer.hpp"

int main() {
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0.5, 3), 1));
    world.add(make_shared<sphere>(point3(2, 2, 5), 0.25));
    world.add(make_shared<sphere>(point3(0, -100.5, 1), 100));

    camera cam(point3(1, 0, 0), vec3(0, 0, 1));
    cam.render_ppm(std::cout, world);
}
