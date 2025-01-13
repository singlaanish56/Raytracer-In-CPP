#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <limits>


const double infinity  = std::numeric_limits<double>::infinity();
const double pi =3.1415926535897932385;

inline double degreeToRadians(double deegrees){
    return deegrees * pi / 180.0;
}

#include "color.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"