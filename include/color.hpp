#pragma once

#include "vec3.hpp"
using color=vec3;

void write_color(std::ostream& out, const color& pixels){
    auto r  =pixels.x();
    auto g  =pixels.y();
    auto b  =pixels.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte <<' '<<gbyte<<' '<<bbyte<<'\n';
}