#pragma once

#include "vec3.hpp"
#include "interval.hpp"
using color=vec3;

inline double linearToGamma(double linerComponent){
    if(linerComponent > 0){
        return std::sqrt(linerComponent);
    }

    return 0;
}

void write_color(std::ostream& out, const color& pixels){
    auto r  =pixels.x();
    auto g  =pixels.y();
    auto b  =pixels.z();

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    static const interval intensity(0.000,0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte <<' '<<gbyte<<' '<<bbyte<<'\n';
}