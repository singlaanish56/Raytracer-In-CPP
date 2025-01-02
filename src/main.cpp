
#include<iostream>



int main(){

    int image_wdith = 256;
    int image_height = 256;
    std::cout<<"P3\n"<< image_wdith <<' '<<image_height<<"\n255\n";
    
    for(int j=0;j<image_height;j++){
        for(int i=0;i<image_wdith;i++){
            auto b = double(i) / (image_wdith-1);
            auto g = double(j) / (image_height-1);
            auto r = double(j) / (image_wdith-1);;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout<<ir<<' '<<ig<<' '<<ib<<'\n';
        }
    }

    return 0;
}