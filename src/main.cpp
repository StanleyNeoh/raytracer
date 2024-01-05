#include "pkg/raytracer.hpp"
#include "scene/scene.hpp"

#include <iostream>

int main() {
    int option;
    bool optionSet = false;
    while (!optionSet) {
        std::clog << "Which scene do you want to render?\n"
            << "    1: Textbook Scene\n"
            << "    2: Simple Scene\n"
            << "Input your option (1, 2): \n";
        std::cin >> option;
        std::clog << option;
        switch (option) {
            case 1:
            case 2:
                optionSet = true;
                break;
            default:
                std::clog << "Please select one of the available options (1, 2): \n\n"; 
        };
    }

    switch(option) {
        case 1:
            render_textbook_ppm();
            break;
        case 2:
            render_simple_ppm();
            break;
        default:
            std::clog << "Invalid option\n";
    }
    return 0;
}
