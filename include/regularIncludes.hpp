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
   return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max){
    return min +( max - min) * randomDouble();
}

#include "color.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"