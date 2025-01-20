
#include "regularIncludes.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"


int main(){

    // World
    hittableList world;
    auto materialGround = std::make_shared<lambertian>(color(0.8,0.8,0.0));
    auto materialCenter = std::make_shared<lambertian>(color(0.1,0.2,0.5));
    auto materialLeft = std::make_shared<metal>(color(0.8,0.8,0.8),0.3);
    auto materialRight = std::make_shared<metal>(color(0.8,0.6,0.2),1.0);

    world.add(std::make_shared<sphere>(point3(0.0,-100.5,-1.0), 100.0, materialGround));
    world.add(std::make_shared<sphere>(point3(0.0, 0.0,-1.2), 0.5, materialCenter));
    world.add(std::make_shared<sphere>(point3(-1.0,0.0,-1.0), 0.5, materialLeft));
    world.add(std::make_shared<sphere>(point3(1.0,0.0,-1.0), 0.5, materialRight));
    camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplePerPixel = 100;
    cam.maxDepth =  50;
    cam.render(world);
    return 0;
}