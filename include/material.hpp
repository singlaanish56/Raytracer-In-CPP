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

public:
metal(const color& albedo ): albedo(albedo){}
bool scatter(const ray& r, const hitrecord& rec, color& attenuation, ray& scattered) const override{
    vec3 reflected = reflect(r.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;

    return true;
}
};