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

constexpr float SIGMA = 1.2f;

// Build a normalized 1D Gaussian kernel.
// Kernel radius covers 3σ (>99.7% of the distribution).
static vector<float> build_gaussian_kernel_1d(float sigma) {
    int half = (int)ceilf(3.0f * sigma);
    int size = 2 * half + 1;
    vector<float> k(size);
    float sum = 0.0f;
    for (int i = 0; i < size; ++i) {
        float x = (float)(i - half);
        k[i] = expf(-(x * x) / (2.0f * sigma * sigma));
        sum += k[i];
    }
    float inv_sum = 1.0f / sum;
    for (auto &v : k) v *= inv_sum;
    return k;
}

// Apply Gaussian blur via separable 1D convolution (horizontal then vertical).
// Complexity: O(W * H * 2K) instead of O(W * H * K^2) for the 2D approach.
bool test_function(ImageLte<float> &in, ImageLte<float> &out) {
    int width   = in.get_width();
    int height  = in.get_height();
    int channel = in.get_channel();
    cout << "image size : " << width << " x " << height << " channel : " << channel << "\n";

    vector<float> kernel = build_gaussian_kernel_1d(SIGMA);
    int kernel_size = (int)kernel.size();
    int half = kernel_size / 2;
    cout << "kernel size : " << kernel_size << "\n";

    out = ImageLte<float>(width, height, channel);
    int rect_size = width * height;

    vector<float> ch_in, tmp(rect_size), ch_out(rect_size);

    for (int c = 0; c < channel; ++c) {
        in.get_channel_data(ch_in, c);

        // Horizontal pass: ch_in → tmp
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float sum = 0.0f;
                for (int k = 0; k < kernel_size; ++k) {
                    int sx = x + (k - half);
                    if (sx < 0) sx = 0;
                    else if (sx >= width) sx = width - 1;
                    sum += ch_in[y * width + sx] * kernel[k];
                }
                tmp[y * width + x] = sum;
            }
        }

        // Vertical pass: tmp → ch_out
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float sum = 0.0f;
                for (int k = 0; k < kernel_size; ++k) {
                    int sy = y + (k - half);
                    if (sy < 0) sy = 0;
                    else if (sy >= height) sy = height - 1;
                    sum += tmp[sy * width + x] * kernel[k];
                }
                ch_out[y * width + x] = sum;
            }
        }

        out.set_channel_data(ch_out, c);
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
    if (test_function(image_src, image_dst)) {
        cout << "processing success\n";
        std::chrono::milliseconds timestamp_ = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        std::string timestamp = to_string(timestamp_.count());
        std::string out_file = std::string("output_") + timestamp + std::string(".png");
        image_dst.saveImage(out_file);
    }
    else {
        cout << "processing failed\n";
        return -1;
    }

    return 1;
}
