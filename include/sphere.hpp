#pragma once

#include "hittable.hpp"

class sphere : public hittable{
private:
point3 center;
double radius;
std::shared_ptr<material> mat;

public:

sphere(const point3& center, const double radius, std::shared_ptr<material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat){}

bool hit(const ray&r , interval rayt, hitrecord&  rec) const override{
    vec3 oc = center - r.origin();
    auto a = r.direction().lengthsqaured();
    auto h = dot(r.direction(), oc);
    auto c = oc.lengthsqaured() - radius * radius;
    auto discrimenant = h*h - a*c;
    
    if(discrimenant < 0.0){
        return false;
    }


    auto sqrtdiscrimenant = std::sqrt(discrimenant);
    auto root  = (h-sqrtdiscrimenant) / a;

    //outside the range find the other root
    if(!rayt.surrounds(root)){
        root= (h+sqrtdiscrimenant)/a;
        if(!rayt.surrounds(root)){
            return false;
        }
    }

    rec.t = root;
    rec.p  =  r.at(rec.t);
    vec3 outwarNormal = (rec.p-center) / a;
    rec.setFrontFace(r, outwarNormal);
    rec.mat = mat;
    
    return true;

}


};