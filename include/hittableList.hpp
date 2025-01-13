#pragma once

#include "hittable.hpp"
#include <vector>

class hittableList : public hittable{
public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittableList(){}
    hittableList(std::shared_ptr<hittable> object) { add(object);};

    void add(std::shared_ptr<hittable> object){
        objects.push_back(object);
    }

    bool hit(const ray&r , interval rayt, hitrecord&  rec) const override{

        hitrecord tempRec;
        bool hitAnything = false;
        auto closestSoFar  = rayt.max;


        for(const auto& object : objects){
            if(object->hit(r, interval(rayt.min, closestSoFar), tempRec)){
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }



        return hitAnything;
    }
    
};