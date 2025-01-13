#pragma once

#include "hittable.hpp"
class camera{
private:
    int imageHeight;
    point3 center;
    point3  pixel100loc;
    vec3 pixelDeltaU;
    vec3 pixelDeltaV;

    void initialize(){

    //calculate the height, depending on the width
    imageHeight =int(imageWidth / aspectRatio);
    imageHeight = imageHeight <1 ? 1 : imageHeight;

    //camera
    auto focalLength = 1.0;
    center = point3(0,0,0);

    //viewport
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth/imageHeight));
    auto viewportU = vec3(viewportWidth ,0 ,0);
    auto viewportV = vec3(0, -viewportHeight, 0);
    pixelDeltaU =  viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight; 

    //the upper left location of the pixel on the viewport
    auto viewportUpperLeft = center - vec3(0,0,focalLength) - viewportU/2 - viewportV/2;

    // shift the left mopst point to coincide with the center
    pixel100loc = viewportUpperLeft + 0.5 *( pixelDeltaU+pixelDeltaV);
    }

    color rayColor(const ray& r, const hittable& world){
        hitrecord rec;

        if (world.hit(r,interval(0, infinity), rec)){
            return 0.5  * (rec.normal + color(1,1,1));
        }

        vec3 unit_direction  = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a) * color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);
    }

public :
    double aspectRatio = 1.0;
    int imageWidth = 100;
    
    void render(const hittable& world){
        initialize();

        std::cout<<"P3\n"<< imageWidth <<' '<<imageHeight<<"\n255\n";
        
        for(int j=0;j<imageHeight;j++){
            std::clog<<"\rScanline remaining: " <<(imageHeight-j) << ' '<<std::flush;
            for(int i=0;i<imageWidth;i++){
                auto pixelCenter = pixel100loc + (i* pixelDeltaU) + (j * pixelDeltaV);
                auto rayDirection =  pixelCenter - center;

                ray r ( center, rayDirection);
                color pixelColor = rayColor(r, world);

                write_color(std::cout, pixelColor); 
            }
        }

        std::clog<<"\rDone.                           \n";      
    }

};