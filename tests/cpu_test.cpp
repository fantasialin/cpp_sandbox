
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <cstring>
#include <chrono>
#include <ctime>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

constexpr int loop_count = 1000;
constexpr int _debug_ = 0;

int main(int argc, char **argv){
    cout << "test CPU fill\n";
    
    int sizeUHD = 3840*2160*4;
    
    vector<float> duration;
    
    void* pUHD = ::operator new(sizeUHD);
    
    if(nullptr == pUHD){
        cout << "fail to allocate memory";
        return -1;
    }
    
    cout << "buffer size : " << sizeUHD << endl;
    
    
    for(int i=0; i<loop_count; i++){
        auto start_ = chrono::high_resolution_clock::now();
        
        std::memset(pUHD, 0x5A, sizeUHD);
        
        auto stop_ = chrono::high_resolution_clock::now();
        auto delta = chrono::duration_cast<chrono::microseconds>(stop_ - start_);
        
        #if _debug_
        cout << "compute time : " << (delta.count()/1000.0f) << " ms\n";
        #endif
        
        duration.push_back((delta.count()/1000.0f));
    }
    
    //compare stddev, mean
    cout << "perform test : " << duration.size() << " times" << endl;
    
    double sum = std::accumulate(duration.begin(), duration.end(), 0.0);
    double mean = sum / duration.size();

    double sq_sum = std::inner_product(duration.begin(), duration.end(), duration.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / duration.size() - mean * mean);
    
    cout << "stdev : " << stdev << endl;
    cout << "mean : " << mean << endl;
    
    if(nullptr != pUHD){
        ::operator delete(pUHD);
    }
    return 0;
}
