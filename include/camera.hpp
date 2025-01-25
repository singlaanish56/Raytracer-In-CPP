#pragma once

#include "hittable.hpp"
#include "material.hpp"

class camera{
private:
    int imageHeight;
    point3 center;
    point3  pixel100loc;
    vec3 pixelDeltaU;
    vec3 pixelDeltaV;
    double pixelSampleScale;
    vec3 u, v ,w;
    vec3 defocusDiskU;
    vec3 defocusDiskV;

    void initialize(){

    //calculate the height, depending on the width
    imageHeight =int(imageWidth / aspectRatio);
    imageHeight = imageHeight <1 ? 1 : imageHeight;

    //antialiasing
    pixelSampleScale  = 1.0 / samplePerPixel;

    //camera
    center = lookFrom;

    auto theta = degreeToRadians(fieldOfView);
    auto h = std::tan(theta/2);
    
    w = unit_vector(lookFrom-lookAt);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    //viewport
    auto viewportHeight = 2 * h * focusDist;
    auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
    auto viewportU = viewportWidth * u;
    auto viewportV = viewportHeight * -v;
    pixelDeltaU =  viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight; 

    //the upper left location of the pixel on the viewport
    auto viewportUpperLeft = center - (focusDist * w) - viewportU/2 - viewportV/2;

    // shift the left mopst point to coincide with the center
    pixel100loc = viewportUpperLeft + 0.5 *( pixelDeltaU+pixelDeltaV);

    auto defocusRadius = focusDist * std::tan(degreeToRadians(deFocusAngle/2));
    defocusDiskU = u * defocusRadius;
    defocusDiskV = v * defocusDiskV;

    }

    ray getRay(int i,int j) const{
        // offsetting the ray by bit, changing where the ray hits in the pixel for around the pixel.
        
        auto offset = sampleSquare();
        auto pixelSample  = pixel100loc + ((i+ offset.x()) * pixelDeltaU) + ((j+offset.y())* pixelDeltaV);

        auto rayOrigin = (deFocusAngle<=0)?center: defocusDiskSample();
        auto rayDirection = pixelSample - rayOrigin;

        return ray(rayOrigin, rayDirection);
    }

    point3 defocusDiskSample() const {
        auto p = randomUnitDisk();
        return center + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
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
            ray scattered;
            color attenuation;
            if(rec.mat->scatter(r, rec, attenuation, scattered)){
                return attenuation * rayColor(scattered, depth-1, world);
            }

            return color(0,0,0);
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

    double fieldOfView = 90;
    point3 lookFrom =  point3(0,0,0);
    point3 lookAt = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);
    
    double deFocusAngle = 0;
    double focusDist = 10;

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