#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

#include "image_lite.h"

using namespace std;
using namespace image_lite_lib;

// Bilateral filter parameters
constexpr float SIGMA_SPACE  = 3.0f; // spatial Gaussian (controls neighborhood radius)
constexpr float SIGMA_RANGE  = 0.15f; // range Gaussian  (controls edge sensitivity)

// Bilateral filter: edge-preserving smoothing.
//
// For each pixel p, the output is a weighted average of nearby pixels q where
// the weight combines:
//   - spatial weight:  Gaussian(distance(p,q), sigma_space)
//   - range  weight:   Gaussian(|intensity(p) - intensity(q)|, sigma_range)
//
// Pixels across an edge have very different intensities, so their range weight
// approaches zero and the edge is preserved.  Unlike Gaussian blur, this filter
// is non-linear and cannot be separated into two 1D passes.
bool test_function(ImageLte<float> &in, ImageLte<float> &out) {
    int width   = in.get_width();
    int height  = in.get_height();
    int channel = in.get_channel();
    cout << "image size : " << width << " x " << height << " channel : " << channel << "\n";
    cout << "sigma_space : " << SIGMA_SPACE << "  sigma_range : " << SIGMA_RANGE << "\n";

    // Precompute the spatial Gaussian lookup over the window radius.
    int half = (int)ceilf(3.0f * SIGMA_SPACE);
    int win  = 2 * half + 1;
    cout << "window size : " << win << " x " << win << "\n";

    // spatial_lut[dy * win + dx] = exp(-0.5 * (dx^2+dy^2) / sigma_space^2)
    vector<float> spatial_lut(win * win);
    float inv_2ss = 1.0f / (2.0f * SIGMA_SPACE * SIGMA_SPACE);
    for (int dy = -half; dy <= half; ++dy) {
        for (int dx = -half; dx <= half; ++dx) {
            float dist2 = (float)(dx * dx + dy * dy);
            spatial_lut[(dy + half) * win + (dx + half)] = expf(-dist2 * inv_2ss);
        }
    }

    // Precompute range Gaussian lookup table indexed by squared intensity diff
    // scaled to [0, 255^2] mapped into LUT_SIZE bins.
    constexpr int LUT_SIZE = 1024;
    vector<float> range_lut(LUT_SIZE);
    float inv_2sr = 1.0f / (2.0f * SIGMA_RANGE * SIGMA_RANGE);
    for (int i = 0; i < LUT_SIZE; ++i) {
        float diff = (float)i / (float)(LUT_SIZE - 1); // normalized to [0,1]
        range_lut[i] = expf(-diff * diff * inv_2sr);
    }

    out = ImageLte<float>(width, height, channel);
    int rect_size = width * height;

    vector<float> ch_in(rect_size), ch_out(rect_size);

    for (int c = 0; c < channel; ++c) {
        in.get_channel_data(ch_in, c);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float center = ch_in[y * width + x];
                float weight_sum = 0.0f;
                float val_sum    = 0.0f;

                for (int dy = -half; dy <= half; ++dy) {
                    int sy = y + dy;
                    if (sy < 0) sy = 0;
                    else if (sy >= height) sy = height - 1;

                    for (int dx = -half; dx <= half; ++dx) {
                        int sx = x + dx;
                        if (sx < 0) sx = 0;
                        else if (sx >= width) sx = width - 1;

                        float neighbor = ch_in[sy * width + sx];
                        float diff = fabsf(neighbor - center);

                        // Map diff [0,1] → range LUT index
                        int lut_idx = (int)(diff * (float)(LUT_SIZE - 1));
                        if (lut_idx >= LUT_SIZE) lut_idx = LUT_SIZE - 1;

                        float w = spatial_lut[(dy + half) * win + (dx + half)]
                                * range_lut[lut_idx];

                        val_sum    += neighbor * w;
                        weight_sum += w;
                    }
                }

                ch_out[y * width + x] = val_sum / weight_sum;
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
