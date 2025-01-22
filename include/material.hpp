#pragma once

#include "hittable.hpp"

class material{
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r, const hitrecord& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};


class lambertian : public material{
private:
//fractional reflection from a surface, ==1 all of it has been reflected
color albedo;

public:
lambertian(const color& albedo) : albedo(albedo){}

bool scatter(const ray& r, const hitrecord& rec, color& attenuation, ray& scattered) const override{
    auto scatterDirection = rec.normal + randomUnitVector();
    if(scatterDirection.nearZero())
        scatterDirection = rec.normal;
    
    scattered = ray(rec.p, scatterDirection);

    attenuation = albedo;

    return true;
}

};

class metal : public material{
private:
color albedo;
double fuzz;

public:
metal(const color& albedo, double fuzz ): albedo(albedo), fuzz(fuzz<1 ? fuzz:1){}
bool scatter(const ray& r, const hitrecord& rec, color& attenuation, ray& scattered) const override{
    vec3 reflected = reflect(r.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz*randomUnitVector());

    scattered = ray(rec.p, reflected);
    attenuation = albedo;

    return dot(scattered.direction(), rec.normal) > 0;
}
};


class dielectric : public material{
private:
//ratio of material ri over the ri of the enclosing area
double refractiveIndex;

static double schlickReflectance(double cos, double refractionIndex){
auto r0 = (1-refractionIndex) / (1+refractionIndex);
r0=r0*r0;
return r0 + (1-r0)*std::pow((1-cos),5);
}

public:
dielectric(double refractiveIndex):refractiveIndex(refractiveIndex){}

bool scatter(const ray& r, const hitrecord& rec, color& attenuation, ray& scattered) const override{
    attenuation = color(1.0,1.0,1.0);
    double rindex = rec.frontface ? (1.9/refractiveIndex) : refractiveIndex;

    vec3 unitDirection = unit_vector(r.direction());
    double cosTheta = std::fmin(dot(-unitDirection, rec.normal), 1.0);
    double sinTheta  = std::sqrt(1.0-cosTheta*cosTheta);
    
    //total internal reflection, read about the paper in the refract func in  vec3
    bool cannotRefract = rindex * sinTheta > 1.0;
    vec3 direction;
    if(cannotRefract || schlickReflectance(cosTheta, rindex) > randomDouble()){
        direction = reflect(unitDirection, rec.normal);
    }else{
        direction = refract(unitDirection, rec.normal, rindex);
    }
    

    scattered = ray(rec.p, direction);

    return true;
}
};