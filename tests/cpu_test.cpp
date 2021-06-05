
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <vector>
#include <numeric>

#include <algorithm>

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
    {
        double sum = std::accumulate(duration.begin(), duration.end(), 0.0);
        double mean = sum / duration.size();

        double sq_sum = std::inner_product(duration.begin(), duration.end(), duration.begin(), 0.0); //d1^2 + d2^2 + ... + d1000^2
        double stdev = std::sqrt(sq_sum / duration.size() - mean * mean);
        
        cout << "stdev : " << stdev << endl;
        cout << "mean : " << mean << endl;
    }
    #ifndef WIN32
    {
        double sum = std::accumulate(duration.begin(), duration.end(), 0.0);
        double mean = sum / duration.size();

        std::vector<double> diff(duration.size());
        std::transform(duration.begin(), duration.end(), diff.begin(),
                std::bind2nd(std::minus<double>(), mean));
        double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / duration.size());

        cout << "stdev : " << stdev << endl;
        cout << "mean : " << mean << endl;
    }
    #endif
    {
        double sum = std::accumulate(std::begin(duration), std::end(duration), 0.0);
        double m =  sum / duration.size();

        double accum = 0.0;
        std::for_each (std::begin(duration), std::end(duration), [&](const double d) {
            accum += (d - m) * (d - m);
        });

        double stdev = sqrt(accum / (duration.size()));

        cout << "stdev : " << stdev << endl;
        cout << "mean : " << m << endl;
    }
    
    if(nullptr != pUHD){
        ::operator delete(pUHD);
    }
    return 0;
}
