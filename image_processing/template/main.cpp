#include <vector>
#include <array>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>


#include "image_lite.h"

using namespace std;
using namespace image_lite_lib;

bool test_function(ImageLte<float> &in, ImageLte<float> &out){
    //do some processing
    out = in;
    return true;
}

#define TEST_IMAGE_PATH "../data/kingfisher.jpg"

int main() {
    //srand(time(NULL));
    ImageLte<float> image_src(std::string(TEST_IMAGE_PATH));
    ImageLte<float> image_dst;
    if(test_function(image_src, image_dst)){
        std::cout << "processing success\n";
        //output result
        std::chrono::milliseconds timestamp_ = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        std::string timestamp = to_string(timestamp_.count());
        std::string out_file = std::string("output_") + timestamp + std::string(".png");
        image_dst.saveImage(out_file);
    }
    else{
        std::cout << "processing failed\n";
        return -1;
    }

    return 1;
}

