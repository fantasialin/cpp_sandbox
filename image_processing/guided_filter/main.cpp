#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <numeric>

#include "image_lite.h"

using namespace std;
using namespace image_lite_lib;

// Guided filter parameters
// RADIUS  : local window half-size (window = (2r+1)^2 pixels)
// EPSILON : regularisation; larger = smoother, less edge-aware
constexpr int   RADIUS  = 3;
constexpr float EPSILON = 0.15f * 0.15f; // (0.01)^2 on a [0,1] intensity scale

// ---------------------------------------------------------------------------
// Box filter helpers
// ---------------------------------------------------------------------------

// Compute the box-filter (mean) of src over a (2r+1)x(2r+1) window.
// Uses two separable 1D passes via prefix sums → O(W*H) regardless of radius.
static void box_filter(const vector<float> &src,
                       vector<float>       &dst,
                       int width, int height, int r)
{
    int N = width * height;
    dst.resize(N);
    vector<float> tmp(N);

    // Horizontal pass with prefix sums
    for (int y = 0; y < height; ++y) {
        const float *row = src.data() + y * width;
        float       *out = tmp.data() + y * width;

        // Build prefix sum for this row
        vector<float> psum(width + 1, 0.0f);
        for (int x = 0; x < width; ++x)
            psum[x + 1] = psum[x] + row[x];

        for (int x = 0; x < width; ++x) {
            int lo = max(x - r,         0);
            int hi = min(x + r + 1, width);
            out[x] = (psum[hi] - psum[lo]) / (float)(hi - lo);
        }
    }

    // Vertical pass with prefix sums
    for (int x = 0; x < width; ++x) {
        // Build prefix sum for this column (from tmp)
        vector<float> psum(height + 1, 0.0f);
        for (int y = 0; y < height; ++y)
            psum[y + 1] = psum[y] + tmp[y * width + x];

        for (int y = 0; y < height; ++y) {
            int lo = max(y - r,          0);
            int hi = min(y + r + 1, height);
            dst[y * width + x] = (psum[hi] - psum[lo]) / (float)(hi - lo);
        }
    }
}

// Element-wise multiply two same-size vectors into dst.
static void vec_mul(const vector<float> &a,
                    const vector<float> &b,
                    vector<float>       &dst)
{
    int n = (int)a.size();
    dst.resize(n);
    for (int i = 0; i < n; ++i)
        dst[i] = a[i] * b[i];
}

// ---------------------------------------------------------------------------
// Guided filter  (He et al., 2013)
//
// Algorithm per channel:
//   mean_I  = box(guide)
//   mean_p  = box(input)
//   corr_Ip = box(guide * input)
//   corr_II = box(guide * guide)
//   cov_Ip  = corr_Ip - mean_I * mean_p
//   var_I   = corr_II - mean_I * mean_I
//   a       = cov_Ip / (var_I + eps)
//   b       = mean_p - a * mean_I
//   mean_a  = box(a)
//   mean_b  = box(b)
//   output  = mean_a * guide + mean_b
//
// When guide == input this is the self-guided (edge-preserving smoothing) mode.
// ---------------------------------------------------------------------------
bool guided_filter(ImageLte<float> &guide,
                   ImageLte<float> &input,
                   ImageLte<float> &out,
                   int radius, float eps)
{
    int width   = input.get_width();
    int height  = input.get_height();
    int channel = input.get_channel();

    if (guide.get_width()   != width  ||
        guide.get_height()  != height ||
        guide.get_channel() != channel) {
        cout << "guide and input must have the same dimensions\n";
        return false;
    }

    out = ImageLte<float>(width, height, channel);
    int N = width * height;

    vector<float> I(N), p(N);
    vector<float> mean_I, mean_p, corr_Ip, corr_II;
    vector<float> Ip(N), II(N);
    vector<float> cov_Ip(N), var_I(N), a(N), b(N);
    vector<float> mean_a, mean_b, ch_out(N);

    for (int c = 0; c < channel; ++c) {
        guide.get_channel_data(I, c);
        input.get_channel_data(p, c);

        // Step 1: local means
        box_filter(I, mean_I, width, height, radius);
        box_filter(p, mean_p, width, height, radius);

        // Step 2: correlations
        vec_mul(I, p, Ip);
        box_filter(Ip, corr_Ip, width, height, radius);

        vec_mul(I, I, II);
        box_filter(II, corr_II, width, height, radius);

        // Step 3: local linear coefficients
        for (int i = 0; i < N; ++i) {
            cov_Ip[i] = corr_Ip[i] - mean_I[i] * mean_p[i];
            var_I[i]  = corr_II[i] - mean_I[i] * mean_I[i];
            a[i]      = cov_Ip[i] / (var_I[i] + eps);
            b[i]      = mean_p[i] - a[i] * mean_I[i];
        }

        // Step 4: smooth coefficients then apply
        box_filter(a, mean_a, width, height, radius);
        box_filter(b, mean_b, width, height, radius);

        for (int i = 0; i < N; ++i)
            ch_out[i] = mean_a[i] * I[i] + mean_b[i];

        out.set_channel_data(ch_out, c);
    }

    return true;
}

// Self-guided mode: guide == input (edge-preserving smoothing).
bool test_function(ImageLte<float> &in, ImageLte<float> &out) {
    int width   = in.get_width();
    int height  = in.get_height();
    int channel = in.get_channel();
    cout << "image size : " << width << " x " << height << " channel : " << channel << "\n";
    cout << "radius : " << RADIUS << "  epsilon : " << EPSILON << "\n";

    return guided_filter(in, in, out, RADIUS, EPSILON);
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
