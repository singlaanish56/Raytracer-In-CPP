
#include "regularIncludes.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"


int main(){

    // World
    hittableList world;
    auto materialGround =  std::make_shared<lambertian>(color(0.5,0.5,0.5));
    world.add(std::make_shared<sphere>(point3(0,-1000,0),1000, materialGround));

    for(int a = -11;a<11;a++){
        for(int b=-11;b<11;b++){

            auto chooseMaterial = randomDouble();
            point3 center(a+ 0.9*randomDouble(), 0.2, b + 0.9* randomDouble());

            if((center - point3(4,0.2, 0)).length()> 0.9){
                std::shared_ptr<material> sphereMaterial;

                if(chooseMaterial < 0.8){
                    auto albedo = color::random() * color::random();
                    sphereMaterial = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }else if(chooseMaterial < 0.95){
                    auto albedo = color::random(0.5,1);
                    auto fuzz = randomDouble(0,0.5);
                    sphereMaterial = std::make_shared<metal> (albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }else{
                    sphereMaterial = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }


    auto dielectricMaterial  = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3(0,1,0),1.0, dielectricMaterial));

    auto normalMaterial  = std::make_shared<lambertian>(color(0.4,0.2,0.1));
    world.add(std::make_shared<sphere>(point3(-4,1,0),1.0, normalMaterial));

    auto metalMaterial  = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(point3(4,1,0),1.0, metalMaterial));


    camera cam;

    cam.aspectRatio = 16.0/9.0;
    cam.imageWidth = 600;
    cam.samplePerPixel = 300;
    cam.maxDepth = 30;

    cam.fieldOfView = 20;
    cam.lookFrom = point3(13,2,3);
    cam.lookAt = point3(0,0,0);
    cam.vup = vec3(0,1,0);

    cam.deFocusAngle = 0.6;
    cam.focusDist = 10.0;

    cam.render(world);
}