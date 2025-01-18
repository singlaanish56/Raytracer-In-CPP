#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <limits>
#include <random>

const double infinity  = std::numeric_limits<double>::infinity();
const double pi =3.1415926535897932385;

inline double degreeToRadians(double deegrees){
    return deegrees * pi / 180.0;
}

inline double randomDouble(){
    static  std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max){
    return min +( max - min) * randomDouble();
}

#include "color.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"