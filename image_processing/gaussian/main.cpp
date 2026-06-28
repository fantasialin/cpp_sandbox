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

bool l1_normalize(vector<float> &data){
    std::cout << __FUNCTION__ << "\n";
    float sum = 0.0f;
    for(auto &item : data){
        sum += item;
    }
    if(sum <= 0.0f) return false;
    float inv_sum = 1.0f/sum;
    for(auto &item : data){
        item *= inv_sum;
    }
    return true;
}

#define sigma 1.2f

// This function takes an input image and applies a Gaussian blur to it, storing the result in the output image.
bool test_function(ImageLte<float> &in, ImageLte<float> &out){
    //do some processing
    int width = in.get_width();
    int height = in.get_height();
    int channel = in.get_channel();
    std::cout << "image size : " << width << " x " << height << " channel : " << channel << "\n";
    int kernel_size = (int) (sigma * 6.0f) + 1;//6 times sigma will cover 99.7% of the distribution
    if(kernel_size % 2 == 0) kernel_size += 1; //make it odd
    std::cout << "kernel size : " << kernel_size << "\n";
    std::vector<float> kernel;
    kernel.resize(kernel_size,0.0f);
    int half_kernel_size = kernel_size/2;

    for(int i = 0; i < kernel_size; ++i){
        int x = i - half_kernel_size;
        kernel[i] = expf(-(x*x)/(2.0f*sigma*sigma));
    }
    l1_normalize(kernel);

    out = ImageLte<float>(width, height, channel);
    // get input image data
    std::vector<float> input_data;
    for(int c = 0; c < channel; ++c){
        std::vector<float> channel_data_in;
        std::vector<float> channel_data_out;
        in.get_channel_data(channel_data_in, c);
        //convolve with kernel
        int rect_size = width * height;
        channel_data_out.resize(rect_size, 0.0f);
        for(int y = 0; y < height; ++y){
            for(int x = 0; x < width; ++x){
                float sum = 0.0f;
                for(int k = 0; k < kernel_size; ++k){
                    int offset = k - half_kernel_size;
                    int x_ = x + offset;
                    if(x_ < 0) x_ = 0;
                    if(x_ >= width) x_ = width - 1;
                    sum += channel_data_in[y*width+x_] * kernel[k];
                }
                channel_data_out[y*width+x] = sum;
            }
        }
        out.set_channel_data(channel_data_out, c);
    }

    return true;
}
#if defined(WIN32)
#define TEST_IMAGE_PATH "../data/kingfisher.jpg"
#else
#define TEST_IMAGE_PATH "data/kingfisher.jpg"
#endif

int main() {
    //srand(time(NULL));
    std::string test_image = std::string(TEST_IMAGE_PATH);
    ImageLte<float> image_src(test_image);
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

