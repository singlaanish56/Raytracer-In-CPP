#pragma once

#include "vec3.hpp"

class ray{
public:
    ray(){}
    ray(const point3& orig,const vec3& dir) : orig(orig), dir(dir){}
    const point3& origin() const { return orig;}
    const vec3& direction() const { return dir;}


    point3 at(double t) const{
        return orig + t*dir;
    }

private:
    point3 orig;
    vec3 dir;
};