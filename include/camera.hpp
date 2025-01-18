#pragma once

#include "hittable.hpp"
class camera{
private:
    int imageHeight;
    point3 center;
    point3  pixel100loc;
    vec3 pixelDeltaU;
    vec3 pixelDeltaV;
    double pixelSampleScale;

    void initialize(){

    //calculate the height, depending on the width
    imageHeight =int(imageWidth / aspectRatio);
    imageHeight = imageHeight <1 ? 1 : imageHeight;

    //antialiasing
    pixelSampleScale  = 1.0 / samplePerPixel;

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

    ray getRay(int i,int j) const{
        // offsetting the ray by bit, changing where the ray hits in the pixel for around the pixel.
        
        auto offset = sampleSquare();
        auto pixelSample  = pixel100loc + ((i+ offset.x()) * pixelDeltaU) + ((j+offset.y())* pixelDeltaV);

        auto rayOrigin = center;
        auto rayDirection = pixelSample - rayOrigin;

        return ray(rayOrigin, rayDirection);
    }

    vec3 sampleSquare() const {
        //get a random point between [-.5, -.5] [+.5,+.5] unit sqaure.
        return vec3(randomDouble() -0.5 ,  randomDouble() - 0.5, 0);
    }

    color rayColor(const ray& r, int depth, const hittable& world){
        if(depth<=0)
            return color(0,0,0);
        
        hitrecord rec;

        // the non zero min in the interval is to  deal with a closer to just below the surface, which
        //could change the surface color again.
        if (world.hit(r,interval(0.001, infinity), rec)){
            vec3 direction = randomOnHemisphere(rec.normal);
            return 0.7 * rayColor(ray(rec.p, direction),depth-1, world);
        }

        vec3 unit_direction  = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a) * color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);
    }

public :
    double aspectRatio = 1.0;
    int imageWidth = 100;
    int samplePerPixel = 10;
    int maxDepth=10;// max number of recursive calls for the rayColor functions
    void render(const hittable& world){
        initialize();

        std::cout<<"P3\n"<< imageWidth <<' '<<imageHeight<<"\n255\n";
        
        for(int j=0;j<imageHeight;j++){
            std::clog<<"\rScanline remaining: " <<(imageHeight-j) << ' '<<std::flush;
            for(int i=0;i<imageWidth;i++){
               color pixelColor(0,0,0);
                for(int sample = 0 ; sample<samplePerPixel;sample++){
                    ray r = getRay(i,j);
                    pixelColor += rayColor(r, maxDepth, world);
                }


                write_color(std::cout, pixelSampleScale  * pixelColor); 
            }
        }

        std::clog<<"\rDone.                           \n";      
    }

};