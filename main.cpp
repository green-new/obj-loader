#include <iostream>
#include "loader.h"

int main() {
    mol::loader MainLoader;
    MainLoader.obj_load("teapot.obj");
    MainLoader.obj_load("torus.obj");
    MainLoader.obj_load("teddy.obj");

    std::vector<float> values = MainLoader.get_vertex_data("teddy.obj");

    for (auto a : values)
    {
        std::cout << " " << a;
    }

    std::cin.get();
    return 0;
}