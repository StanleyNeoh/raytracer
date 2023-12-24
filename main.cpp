#include "color.hpp"
#include "vec3.hpp"

#include <iostream>

using std::cout, std::clog;

int main() {

    // Image 
    int img_w = 256;
    int img_h = 256;

    // Render
    cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

    for (int j = 0; j < img_h; j++) {
        clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;

        for (int i = 0; i < img_w; i++) {
            auto pixel_color = color(double(i)/(img_w -1), double(j)/(img_h-1), 0);
            write_color(cout, pixel_color);
        }
        clog << "\rDone\n";
    }
}