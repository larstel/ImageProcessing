#include "ppmcreator.h"

PpmCreator::PpmCreator()
{
    std::string format = "P3";
    std::string comment = "# Lars Teloeken";
    int width = 800;
    int height = 800;
    int brightness = 255;
    std::string pixels = "";

    int counter =0;
    for(int i = 0; i < width; i++){
        if(counter<brightness){
            for(int j = 0; j < height; j++){
                pixels.append(std::to_string(i%brightness) + " 0 0 ");
            }
         }else if(counter>=brightness && counter<brightness*2){
            for(int j = 0; j < height; j++){
                pixels.append(std::to_string(brightness-1-(i%brightness)) + " 0 0 ");
            }
         } else {
            counter=0;
         }
            counter++;
         }
    std::ofstream outfile ("test.ppm");

    outfile << format << std::endl;
    outfile << comment << std::endl;
    outfile << width << " " << height << std::endl;
    outfile << brightness << std::endl;
    outfile << pixels << std::endl;

    outfile.close();
}
