#ifndef _IMAGE_LITE_H
#define _IMAGE_LITE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype> //std::tolower
#include <sys/stat.h>
#include <tuple>
#include <stack>
#include <math.h>
#include <chrono>
#include <functional>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif
using namespace std;
using namespace chrono;

#if 0
#define JOE_TIME_PROFILE_INIT()
#define JOE_TIME_PROFILE_START()
#define JOE_TIME_PROFILE_COUNT(message)
#else

#define JOE_TIME_PROFILE_INIT() \
  std::chrono::microseconds delta;\
  std::chrono::microseconds start_;\
  std::chrono::microseconds now_;

#define JOE_TIME_PROFILE_START() start_ = duration_cast<microseconds>(system_clock::now().time_since_epoch());

#define JOE_TIME_PROFILE_COUNT(message) \
  now_ = duration_cast<microseconds>(system_clock::now().time_since_epoch());\
  delta = (now_ - start_);\
  start_ = now_;\
  std::cout << message << " : " << (delta.count() / 1000.0f) << " ms\n";
#endif

namespace image_lite_lib{

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#define TWOPI 6.2831853

#ifndef M_PI
#define M_PI       3.14159265358979323846   // pi
#endif
/*  memory layout separate
+----------------------------------+
|                                  |
|       channel 0 (R)              |
|                                  |
+----------------------------------+
|                                  |
|       channel 1 (G)              |
|                                  |
+----------------------------------+
|                                  |
|       channel 2 (B)              |
|                                  |
+----------------------------------+
|                                  |
|       channel 3 (A)              |
|                                  |
+----------------------------------+
*/

#ifndef EPS
//#define EPS 1e-3 //.005 //.002
#define EPS .004
#endif

template<class TupType, size_t... I>
std::ostream& tuple_print(std::ostream& os,
                          const TupType& _tup, std::index_sequence<I...>)
{
    os << "(";
    (..., (os << (I == 0 ? "" : ", ") << std::get<I>(_tup)));
    os << ")";
    return os;
}

template<class... T>
std::ostream& operator<< (std::ostream& os, const std::tuple<T...>& _tup)
{
    return tuple_print(os, _tup, std::make_index_sequence<sizeof...(T)>());
}


using rect = std::tuple<int, int, int, int>;//(x1, y1), (x2, y2)
using point = std::tuple<int, int>;//x,y
using pointf = std::tuple<double, double>;//x,y
using color = std::tuple<int, int, int, int>;//RGBA

template <typename T>
class ImageLte{
  public:
    //default ctor
    ImageLte() { 
      width = 0;
      height = 0;
      channel = 0;
    }
    //default ctor
    //ctor
    ImageLte(unsigned int width_, unsigned int height_, unsigned int channel_) 
          : width(width_), height(height_), channel(channel_){
      auto size = width * height * channel;
      if(size <= 0 || channel > 4){
        std::cout << "wrong w or h or c w: " << width << "   h: " << height << "  c: " << channel << "\n";
        return;
      }
      data_.resize(size,0.0);
    }
    //ctor
    ImageLte(std::string &path_file_name):width(0), height(0), channel(0){
        loadImage(path_file_name);
        return;
    }
    //dtor
    ~ImageLte(){
      data_.clear();
    }
    //copy ctor
    ImageLte(const ImageLte<T>& rhs) : width(rhs.width), height(rhs.height), channel(rhs.channel){
      data_.clear();
      auto size = width * height * channel;
      if(size > 0){
        data_ = rhs.data_;//use assignment
      }
      else{
        std::cout << "wrong w or h or c     w: " << width << "   h: " << height << "  c: " << channel << "\n";
        return;
      }
    }
    //copy assignment
    ImageLte& operator=(const ImageLte<T>& rhs) {
        if(this != &rhs){
            data_.clear();
            width = rhs.width; 
            height = rhs.height; 
            channel = rhs.channel; 
            data_ = rhs.data_;//use assignment
        }
        return *this;
    }

    int get_channel(){return channel;}
    int get_width(){return width;}
    int get_height(){return height;}
    bool print();

    T get_pixel(int x, int y, int c, bool clamp=true);
    bool get_channel_data(vector<T>&ret, int c);
    bool set_channel_data(vector<T>&data, int c);
    color get_pixel_color(int x, int y);
    void set_pixel(int x, int y, int c, T v);
    T* get_buffer(){ return data_.data();}
    bool get_RGBA_data(vector<unsigned char>&ret);
    bool loadImage(std::string &path_file_name);
    bool saveImage(std::string &path_file_name);
    bool transpose();
    bool matrix_transpose();
    bool flip();
    bool reverse();
    bool rgb_to_grayscale(bool preserve=true);
    bool rgb_to_hsv();
    bool hsv_to_rgb();
    bool shift(int c, T value);
    bool scale_image(int c, T value);
    bool set_channel_value(int c, T value);
    bool replace_channel(int c, std::vector<T> data_in);
    bool clamp();
    bool same_image(ImageLte<T>& rhs);
    bool add_image(ImageLte<T>& rhs);
    
  private:
    bool within_eps(T a, T b);
    bool compareStrings(std::string& str1, std::string& str2);
    bool fileExists(const std::string& path);
    int interpolate(int a0, int a1, float delta);
    std::vector<T> data_;
    int width = 0;
    int height = 0;
    int channel = 0; //channel count e.g. RGB --> channel count =3, grey --> channel count =1
};


template <typename T>
inline bool ImageLte<T>::compareStrings(std::string &str1, std::string &str2)
{
    if (str1.length() != str2.length())
        return false;

    for (int i = 0; i < str1.length(); ++i) {
        if (std::tolower(str1[i]) != std::tolower(str2[i]))
            return false;
    }

    return true;
}

template <typename T>
inline bool ImageLte<T>::fileExists(const std::string &path)
{
    struct stat info;
    if (stat(path.c_str(), &info) == 0) {
        return true;
    }
    return false;
}

template <typename T>
inline int ImageLte<T>::interpolate(int a0, int a1, float delta)
{
    //int distance = a1 - a0;
    return a0 + ((a1 - a0) * delta);
}

template <typename T>
inline bool ImageLte<T>::within_eps(T a, T b)
{
    return a-EPS<b && b<a+EPS;
}

template <typename T>
inline bool ImageLte<T>::print()
{   
    std::cout << __FUNCTION__ << "\n";
    if(channel < 0 || channel != 1) return false;
    if(width > 10) return false;
    if(height > 10) return false;

    std::cout << "[ \n" << std::fixed << std::setprecision(3);
    for(int j = 0; j < height ; j++){//y
      for(int i = 0; i < width ; i++){//x
        auto pos = i + j * width;
        std::cout << "  " << data_[pos];
      }
      std::cout << "\n";
    }
    std::cout << "  ]\n";
    return true;
}

template <typename T>
inline T ImageLte<T>::get_pixel(int x, int y, int c, bool clamp)
{
    int y_ = y;
    int x_ = x;
    // out of range --> use clamp
    if(clamp){
      if(y < 0) y_ = 0;
      if(x < 0) x_ = 0;
      if(y >= height) y_ = height -1;
      if(x >= width) x_ = width -1;
    }
    else{
      if(y < 0) return 1.0;
      if(x < 0) return 1.0;
      if(y >= height) return 1.0;
      if(x >= width) return 1.0;
    }
    if(c > channel) return 0.0;

    int index = 0;
    index = (y_*width+x_)+(c*height*width);
    return data_[index];
}

template <typename T>
inline bool ImageLte<T>::get_channel_data(vector<T> &ret, int c)
{
    std::cout << __FUNCTION__ << " channel : " << c << "\n";
    auto rect_size = width * height;
    if(rect_size <= 0) return false;
    if(c < 0 || c >= channel) return false;
    std::vector<T> tmp_data;
    tmp_data.resize(rect_size,0.0);
    auto pos = c*rect_size;//offset
    for(int i=0; i<rect_size; i++){
      tmp_data[i] = data_[pos+i];
    }
    ret = tmp_data;

    return true;
}

template <typename T>
inline bool ImageLte<T>::set_channel_data(vector<T> &data, int c)
{
    std::cout << __FUNCTION__ << " channel : " << c << "\n";
    auto rect_size = width * height;
    if(rect_size <= 0) return false;
    if(data.size() != rect_size) return false;
    if(c < 0 || c >= channel) return false;
    auto pos = c*rect_size;//offset
    for(int i=0; i<rect_size; i++){
      data_[pos+i] = data[i];
    }

    return true;
}

template <typename T>
inline color ImageLte<T>::get_pixel_color(int x, int y)
{
    int y_ = y;
    int x_ = x;
    // out of range --> use clamp
    if(y < 0) y_ = 0;
    if(x < 0) x_ = 0;
    if(y >= height) y_ = height -1;
    if(x >= width) x_ = width -1;

    uint8_t R, G, B;
    auto rect_size = width * height;
    int index = 0;
    if(channel == 1){
      index = (y_*width+x_);//R
      R = (unsigned char) roundf((255*data_[index]));
      G = R; B = R;
      return color(R,G,B,0);
    }
    index = (y_*width+x_);//R
    R = (unsigned char) roundf((255*data_[index]));
    index = (y_*width+x_)+(rect_size);//G
    G = (unsigned char) roundf((255*data_[index]));
    index = (y_*width+x_)+(2*rect_size);//B
    B = (unsigned char) roundf((255*data_[index]));
    return color(R,G,B,0);
}

template <typename T>
inline void ImageLte<T>::set_pixel(int x, int y, int c, T v)
{
    int y_ = y;
    int x_ = x;
    // out of range --> use clamp
    if(y < 0) y_ = 0;
    if(x < 0) x_ = 0;
    if(y >= height) y_ = height -1;
    if(x >= width) x_ = width -1;

    int index = 0;
    auto rect_size = width * height;
    index = (y_*width+x_)+(c*rect_size);
    data_[index] = v;
    return;
}

template <typename T>
inline bool ImageLte<T>::get_RGBA_data(vector<unsigned char> &ret)
{
    std::cout << __FUNCTION__ << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0) return false;
    if(channel !=3 && channel !=4 ) return false;
    auto rect_ = width * height;
    auto target_channel = 4;
    ret.resize(rect_*target_channel);//RGBA, BGRA ?
    //RGB
    #if 0
    for(int k = 0; k < channel ; ++k){
        for(int i = 0; i < rect_; ++i){
            if constexpr (std::is_same_v<T, float>) { //if T == float
              ret[i*target_channel+k] = (unsigned char) roundf((255.0*data_[i + k*rect_])); 
            }
            else if constexpr (std::is_same_v<T, unsigned char>) { //if T == unsigned char
              ret[i*target_channel+k] = data_[i + k*rect_];
            }
        }
    }
    #else
    //BGR  //for GPU
    int target_k;
    for(int k = 0; k < channel ; ++k){
        if(k == 0) target_k = 2;
        if(k == 2) target_k = 0;
        if(k == 1) target_k = 1;
        for(int i = 0; i < rect_; ++i){
            if constexpr (std::is_same_v<T, float>) { //if T == float
              ret[i*target_channel+target_k] = (unsigned char) roundf((255.0*data_[i + k*rect_])); 
            }
            else if constexpr (std::is_same_v<T, unsigned char>) { //if T == unsigned char
              ret[i*target_channel+target_k] = data_[i + k*rect_];
            }
        }
    }
    #endif
    if(channel == 3){//no alpha channel
      //set alpha as opaque
      for(int i = 0; i < rect_; ++i){
        ret[i*target_channel+3] = 255; // opaque
      }
    }
    return true;
}

template <typename T>
inline bool ImageLte<T>::loadImage(std::string &path_file_name)
{
    std::cout << "loading image file name : " << path_file_name << "\n";
    bool ret = false;
    if(fileExists(path_file_name)){
      int w, h, c;
      int channels = 3; // ??
      unsigned char *ptrbuffer = stbi_load(path_file_name.c_str(), &w, &h, &c, channels);
      if (!ptrbuffer) {
          std::cout << __FUNCTION__ << "Cannot load image " << path_file_name <<  "STB Reason: " << stbi_failure_reason() << "\n";
          return false;
      }
      std::cout << __FUNCTION__ << " wxh " << w << "x" << h << " channel : " << c << "\n";
      if(c == 1){//need to reload image again. workaround load a gray scale image problem.
        free(ptrbuffer);
        ptrbuffer = nullptr;
        ptrbuffer = stbi_load(path_file_name.c_str(), &w, &h, &c, 0);
        if (!ptrbuffer) {
            std::cout << __FUNCTION__ << "Cannot load image " << path_file_name <<  "STB Reason: " << stbi_failure_reason() << "\n";
            return false;
        }
        std::cout << __FUNCTION__ << "reload gray image --> wxh " << w << "x" << h << " channel : " << c << "\n";
      }
      if(c == 4) c = 3; //we don't want 4 channel, only request 3 channels RGB
      channel = c;
      width = w; 
      height = h;
      auto size = width * height * channel;
      data_.resize(size);
      for(int k = 0; k < c; ++k){
          for(int j = 0; j < h; ++j){
              for(int i = 0; i < w; ++i){
                  int dst_index = i + w*j + w*h*k;
                  int src_index = k + c*i + c*w*j;  
                  if constexpr (std::is_same_v<T, float>) { //if T == float
                    data_[dst_index] = (T)(ptrbuffer[src_index]/255.0); 
                  }
                  else if constexpr (std::is_same_v<T, unsigned char>) { //if T == unsigned char
                    data_[dst_index] = (T)ptrbuffer[src_index];
                  }
              }
          }
      }
      ret = true;
      //free stb return buffer...
      free(ptrbuffer);
    }
    else{
      std::cout << __FUNCTION__ << " file not found : " << path_file_name << "\n";
    }
    std::cout << __FUNCTION__ << " ret : " << ret << " done!\n";
    return ret;
}

template <typename T>
inline bool ImageLte<T>::saveImage(std::string &path_file_name)
{
    std::cout << "save image to file name : " << path_file_name << "\n";
    if (data_.size() <= 0)
        return false;
    std::cout << "data size : " << data_.size() << " wxh : " << width << " x " << height << " channel : " << channel << "\n";
    //check extension
    std::string strPNG = std::string("png");
    std::string strJPG = std::string("jpg");
    std::size_t found = path_file_name.rfind(".");
    if (found != std::string::npos) {
        std::string output_name = path_file_name.substr(0, found+1);
        std::string ext_ = path_file_name.substr(found+1);
        //std::cout << ext_ << "\n";
        if(compareStrings(ext_, strPNG) || compareStrings(ext_, strJPG)){
          vector<unsigned char> img(data_.size());
          auto rect_ = width * height;
          for(int k = 0; k < channel ; ++k){
              for(int i = 0; i < rect_; ++i){
                  if constexpr (std::is_same_v<T, float>) { //if T == float
                    img[i*channel+k] = (unsigned char) roundf((255.0*data_[i + k*rect_])); 
                  }
                  else if constexpr (std::is_same_v<T, unsigned char>) { //if T == unsigned char
                    img[i*channel+k] = data_[i + k*rect_];
                  }
              }
          }
          int success = 0;
          if(compareStrings(ext_, strPNG)){
            std::string output_ = output_name + strPNG;
            success = stbi_write_png(output_.c_str(), width, height, channel, static_cast<const void*>(img.data()), width*channel);
            if(!success)  std::cout << "Failed to write image " << output_ << "\n";
          }
          else if(compareStrings(ext_, strJPG)){
            std::string output_ = output_name + strJPG;
            success = stbi_write_jpg(output_.c_str(), width, height, channel, static_cast<const void*>(img.data()), 100);
            if(!success)  std::cout << "Failed to write image " << output_ << "\n";
          }
          //img.clear();
        }

    }
    return true;
}
template <typename T>
inline bool ImageLte<T>::transpose()
{
    std::cout << __FUNCTION__ << "\n";
    std::cout << "data size : " << data_.size() << " wxh : " << width << " x " << height << " channel : " << channel << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0)
      return false;
    
    std::vector<T> tmp_data;
    tmp_data.resize(total_size,0.0);
    int rect_ = width * height;
    for(int c = 0; c < channel; c++){
      auto shift =  c * rect_;
      for(int i = 0; i < rect_; i++){
        auto target = (rect_ - i - 1) + shift;
        auto source = i + shift;
        tmp_data[target] = data_[source];
      }
    }
    data_.clear();
    data_ = tmp_data;
    return true;
}

template <typename T>
inline bool ImageLte<T>::matrix_transpose()
{
    std::cout << __FUNCTION__ << "\n";
    std::cout << "data size : " << data_.size() << " wxh : " << width << " x " << height << " channel : " << channel << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0)
      return false;
    
    std::vector<T> tmp_data;
    tmp_data.resize(total_size,0.0);
    int rect_ = width * height;
    for(int c = 0; c < channel; c++){
      auto shift =  c * rect_;
      for(int i = 0; i < rect_; i++){
        int y_0 = i/width;
        int y_offset = i%width;
        auto target = y_0 + y_offset*height + shift;
        auto source = i + shift;
        tmp_data[target] = data_[source];
      }
    }
    data_.clear();
    data_ = tmp_data;
    auto tmp = width;
    width = height;
    height = tmp;
    return true;
}

template <typename T>
inline bool ImageLte<T>::flip()
{
    std::cout << __FUNCTION__ << "\n";
    std::cout << "data size : " << data_.size() << " wxh : " << width << " x " << height << " channel : " << channel << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0)
      return false;
    
    std::vector<T> tmp_data;
    tmp_data.resize(total_size,0.0);
    int rect_ = width * height;
    for(int c = 0; c < channel; c++){
      auto shift =  c * rect_;
      for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
          auto target = i + ((height -1 -j)*width) + shift;
          auto source = i + j*width + shift;
          tmp_data[target] = data_[source];
        }
      }
    }
    data_.clear();
    data_ = tmp_data;
    return true;
}

template <typename T>
inline bool ImageLte<T>::reverse()
{
    std::cout << __FUNCTION__ << "\n";
    std::cout << "data size : " << data_.size() << " wxh : " << width << " x " << height << " channel : " << channel << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0)
      return false;
    
    std::vector<T> tmp_data;
    tmp_data.resize(total_size,0.0);
    int rect_ = width * height;
    for(int c = 0; c < channel; c++){
      auto shift =  c * rect_;
      for(int i = 0; i < rect_; i++){
        auto target = i + shift;
        unsigned char tmp = data_[target] * 255;
        tmp = tmp ^ 0xff;
        tmp_data[target] = tmp/255.;
      }
    }
    data_.clear();
    data_ = tmp_data;
    return true;
}

template <typename T>
inline bool ImageLte<T>::rgb_to_grayscale(bool preserve)
{
    std::cout << __FUNCTION__ << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0 || channel != 3)
      return false;
    
    std::vector<T> tmp_data;
    auto size = 0;
    if (preserve)
      size = total_size;// RGB channel
    else
      size = width * height; //only one channel
    auto rect_ = width * height;
    auto rect_x2 = rect_*2;
    tmp_data.resize(size,0.0);
    for(int index=0; index<rect_; index++){
      tmp_data[index] = 0.299*data_[index] + 0.587*data_[index+rect_] + 0.114*data_[index+rect_x2];//0.299R + 0.587G + 0.114B
      if(preserve){
        tmp_data[index+rect_] = tmp_data[index];
        tmp_data[index+rect_x2] = tmp_data[index];
      }
    }
    if(preserve){
      channel = 3;
    }
    else{
      channel = 1;
    }
    data_.clear();
    data_ = tmp_data;
    return true;
}

template <typename T>
inline bool ImageLte<T>::rgb_to_hsv()
{
    std::cout << __FUNCTION__ << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0 || channel != 3)
      return false;
    
    std::vector<T> tmp_data;
    auto rect_ = width * height;
    auto rect_x2 = 2 * rect_;
    tmp_data.resize(total_size,0.0);

    T min, max, delta;
    T R,G,B;
    T H,S,V;

    for(int index=0; index<rect_; index++){
        R = data_[index]; 
        G = data_[index+rect_]; 
        B = data_[index+rect_x2];
        max  = std::max({R,G,B});
        min = std::min({R,G,B});
        V = max;
        delta = max - min;
        
        if( max != 0.0 ) {
            //S
            S = (delta / max);       // s  --> G

            if(delta != 0.0){
                //H
                if( R == max ){
                    H = ( G - B ) / delta;        // between yellow & magenta
                }
                else if( G == max ){
                    H = 2.0 + ( B - R ) / delta;  // between cyan & yellow
                }
                else {
                    H = 4.0 + ( R - G ) / delta;  // between magenta & cyan
                }

                if( H < 0 ) H += 6.0;
                H = H/6.;
            }
            else{
                H = 0.0;
            }
        }
        else {
            S = 0.0;
            H = 0.0;
        }
        //HSV
        tmp_data[index] = H;
        tmp_data[index+rect_] = S;
        tmp_data[index+rect_x2] = V;
    }
    data_.clear();
    data_ = tmp_data;
    return true;
}

template <typename T>
inline bool ImageLte<T>::hsv_to_rgb()
{
    std::cout << __FUNCTION__ << "\n";
    auto total_size = width * height * channel;
    if(total_size <= 0 || channel != 3)
      return false;
    
    std::vector<T> tmp_data;
    auto rect_ = width * height;
    auto rect_x2 = 2 * rect_;
    tmp_data.resize(total_size,0.0);

    T f, p, q, t;
    T R,G,B;
    T H,S,V;

    for(int index=0; index<rect_; index++){
        H = data_[index] * 6.0; 
        S = data_[index+rect_]; 
        V = data_[index+rect_x2];

        if (S == 0) {
            R = G = B = V;
        } 
        else {
            int idx = floor(H);
            f = H - idx;
            p = V*(1-S);
            q = V*(1-S*f);
            t = V*(1-S*(1-f));
            if(idx == 0){
                R = V; G = t; B = p;
            } else if(idx == 1){
                R = q; G = V; B = p;
            } else if(idx == 2){
                R = p; G = V; B = t;
            } else if(idx == 3){
                R = p; G = q; B = V;
            } else if(idx == 4){
                R = t; G = p; B = V;
            } else {
                R = V; G = p; B = q;
            }
        }
        //RGB
        tmp_data[index] = R;
        tmp_data[index+rect_] = G;
        tmp_data[index+rect_x2] = B;
    }
    data_.clear();
    data_ = tmp_data;
    return true;
}

template <typename T>
inline bool ImageLte<T>::shift(int c, T value)
{
    std::cout << __FUNCTION__ << "  channel : " << c << "  value : " << value << "\n";
    if(c < 0 || c >= channel)
      return false;
    auto size = width * height;
    auto pos = c*size;//offset
    for(int idx = 0; idx < size; idx++){
      auto offset = pos+idx;
      data_[offset] = data_[offset] + value;
    }
    return true;
}

template <typename T>
inline bool ImageLte<T>::scale_image(int c, T value)
{
    std::cout << __FUNCTION__ << "  channel : " << c << "  value : " << value << "\n";
    if(c < 0 || c >= channel)
      return false;
    auto size = width * height;
    auto pos = c*size;//offset
    for(int idx = 0; idx < size; idx++){
      auto offset = pos+idx;
      data_[offset] = data_[offset] * value;
    }
    return true;
}

template <typename T>
inline bool ImageLte<T>::set_channel_value(int c, T value)
{
    std::cout << __FUNCTION__ << "  channel : " << c << "  value : " << value << "\n";
    if(c < 0 || c >= channel)
      return false;
    auto size = width * height;
    auto pos = c*size;//offset
    for(int idx = 0; idx < size; idx++){
      auto offset = pos+idx;
      data_[offset] = value;
    }
    return true;
}

template <typename T>
inline bool ImageLte<T>::replace_channel(int c, std::vector<T> data_in)
{
    //data_in should be prepared channel data e.g. pattern or ...
    std::cout << __FUNCTION__ << "  channel : " << c << "\n";
    if(c < 0 || c >= channel)
      return false;
    auto size = width * height;
    if(data_in.size() != size)
      return false;
    auto pos = c*size;//offset
    for(int idx = 0; idx < size; idx++){
      auto offset = pos+idx;
      data_[offset] = data_in[idx];
    }
    return true;
    
}

/* We want to make sure the pixel values in the image stay between 0 and 1. 
   Implement clamping on the image so that any value below zero gets set to 
   zero and any value above 1 gets set to one. */
template <typename T>
inline bool ImageLte<T>::clamp()
{
    std::cout << __FUNCTION__ << "\n";
    for (auto &item : data_) {
        if(item < 0.0){
            item = 0.0;
        } else if(item > 1.0){
            item = 1.0;
        }
    }
    return true;
}
template <typename T>
inline bool ImageLte<T>::same_image(ImageLte<T> &rhs)
{
    std::cout << __FUNCTION__ << "\n";
    if(width != rhs.width || height != rhs.height || channel != rhs.channel) {
        std::cout << "Expected " << width << " x " <<  height << " x " << channel 
                      << " image, got " <<  rhs.width << " x " <<  rhs.height << " x " << rhs.channel << "\n";
        return false;
    }
    auto size = width * height * channel;
    for(int idx = 0; idx < size; idx++){
      if(!within_eps(data_[idx], rhs.data_[idx])){
          std::cout << "[ w: " << width << " , h: " <<  height << " , c: " << channel << " ] idx = " << idx << " the value shoule be "
                      << std::fixed << std::setprecision(3) << data_[idx] << " but it is " << rhs.data_[idx] << " !\n";
          return false;
      }
    }
    return true;
}

template <typename T>
inline bool ImageLte<T>::add_image(ImageLte<T> &rhs)
{
    std::cout << __FUNCTION__ << "\n";
    if(rhs.channel != this->channel) return false;
    if(rhs.width != this->width) return false;
    if(rhs.height != this->height) return false;
    if(rhs.mem_layout != this->mem_layout) return false;

    //std::vector<T> tmp_data;
    auto size = width * height * channel;
    //tmp_data.resize(size,0.0);
    for(int idx = 0; idx < size; idx++){
      data_[idx] = data_[idx] + rhs.data_[idx];
      if(data_[idx] > 1.0) data_[idx] = 1.0;
    }

    return true;
}
}//namespace image_lite_lib

#endif //_IMAGE_LITE_H
