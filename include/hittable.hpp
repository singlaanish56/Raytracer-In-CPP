#pragma once

#include "regularIncludes.hpp"

class material;

// just tell the point of hit and the normal at the piont
class hitrecord{
public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
    double t;
    bool frontface;

    void setFrontFace(const ray& r, const vec3& outwardNormal){

        frontface = dot(r.direction(), outwardNormal) <0;
        normal = frontface ? outwardNormal : -outwardNormal;
    }
};


// this class just acts as a abstraction to any object that can be hit
class hittable{
    public:
    virtual ~hittable()  = default;

    // the tmin tmax just helps identify the range in which or whether the ray was hit.
    virtual bool hit(const ray&r , interval rayt, hitrecord&  rec) const =0;
};