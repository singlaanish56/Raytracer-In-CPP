
#include "regularIncludes.hpp"
#include "hittable.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"


color ray_color(const ray& r, const hittable& world)
{   
    hitrecord rec;

    if (world.hit(r,interval(0, infinity), rec)){
        return 0.5  * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction  = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a) * color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);
}

int main(){


    //Image
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

    //calculate the height, depending on the width
    int image_height =int(image_width / aspect_ratio);
    image_height = image_height <1 ? 1 : image_height;

    // World
    hittableList world;
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));


    //camera
    auto focal_length = 1.0;
    auto camera_center = point3(0,0,0);

    //viewport
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width/image_height));
    auto viewport_u = vec3(viewport_width ,0 ,0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    auto pixel_u_delta =  viewport_u / image_width;
    auto pixel_v_delta = viewport_v / image_height; 

    //the upper left location of the pixel on the viewport
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;

    auto pixel00_loc = viewport_upper_left + 0.5 *( pixel_u_delta+pixel_v_delta);

    

    std::cout<<"P3\n"<< image_width <<' '<<image_height<<"\n255\n";
    
    for(int j=0;j<image_height;j++){
        std::clog<<"\rScanline remaining: " <<(image_height-j) << ' '<<std::flush;
        for(int i=0;i<image_width;i++){
            auto pixel_center = pixel00_loc + (i* pixel_u_delta) + (j * pixel_v_delta);
            auto ray_direction =  pixel_center - camera_center;

            ray r ( camera_center, ray_direction);
            color pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color); 
        }
    }

    std::clog<<"\rDone.                           \n";
    return 0;
}