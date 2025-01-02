
#include<iostream>
#include"color.hpp"
#include"vec3.hpp"


int main(){

    int image_wdith = 256;
    int image_height = 256;
    std::cout<<"P3\n"<< image_wdith <<' '<<image_height<<"\n255\n";
    
    for(int j=0;j<image_height;j++){
        std::clog<<"\rScanline remaining: " <<(image_height-j) << ' '<<std::flush;
        for(int i=0;i<image_wdith;i++){
            auto r = double(i) / (image_wdith-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            auto pixels = color(r,g,b);
            write_color(std::cout, pixels); 
        }
    }

    std::clog<<"\rDone.                           \n";
    return 0;
}