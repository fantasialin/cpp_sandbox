#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include <limits>
#include <chrono>

using namespace std;
using namespace chrono;

#if 0
#define JOE_TIME_PROFILE_INIT()
#define JOE_TIME_PROFILE_START()
#define JOE_TIME_PROFILE_COUNT(message)
#else

// #define JOE_TIME_PROFILE_INIT() \
//   std::chrono::microseconds delta;\
//   std::chrono::_V2::system_clock::time_point start_;\
//   std::chrono::_V2::system_clock::time_point now_;

// #define JOE_TIME_PROFILE_START() start_ = std::chrono::high_resolution_clock::now();
// #define JOE_TIME_PROFILE_COUNT(message) \
//   now_ = std::chrono::high_resolution_clock::now();\
//   delta = std::chrono::duration_cast<std::chrono::microseconds>(now_ - start_);\
//   start_ = now_;\
//   std::cout << message << (delta.count() / 1000.0f) << " ms";

#define JOE_TIME_PROFILE_INIT() \
  std::chrono::microseconds delta;\
  std::chrono::microseconds start_;\
  std::chrono::microseconds now_;

#define JOE_TIME_PROFILE_START() start_ = duration_cast<microseconds>(system_clock::now().time_since_epoch());

#define JOE_TIME_PROFILE_COUNT(message) \
  now_ = duration_cast<microseconds>(system_clock::now().time_since_epoch());\
  delta = (now_ - start_);\
  start_ = now_;\
  std::cout << message << " : " << (delta.count() / 1.0f) << " us\n";
  //std::cout << message << " : " << (delta.count() / 1000.0f) << " ms\n";
#endif

// 1, 1, 2, 3, 5, 8, 13, 21, ...
int Fibonacci(int n){
    if(n <= 0) return 0;
    if(n <= 2)
        return 1;
    else
        return Fibonacci(n-1) + Fibonacci(n-2);
}

int lookup(int i, vector<int>&table){
    if(-1 == table[i])
        table[i] = lookup(i-1, table) + lookup(i-2, table);
    return table[i];
}

int Fibonacci_recur_mem(int n, vector<int>&table){
    if(table.size()<n+1) return 0;//error
    table[0]=0;table[1]=1;
    return lookup(n,table);
}

int Fibonacci_iter(int n){
    if(n <= 0) return 0;
    if(n <= 1) return 1;
    vector<int> number_prev = {0,1};
    int result = 1;
    for(int i = 0; i < n-1 ; i++){
        result = number_prev[0] + number_prev[1];
        number_prev[0] = number_prev[1];
        number_prev[1] = result;
    }
    return result;
}

int TripleFibonacci_iter(int n){
    if(n <= 1) return 0;
    if(n <= 2) return 1;
    vector<int> number_prev = {0,0,1};
    int result = 1;
    for(int i = 0; i < n-2 ; i++){
        result = number_prev[0] + number_prev[1] + number_prev[2];
        number_prev[0] = number_prev[1];
        number_prev[1] = number_prev[2];
        number_prev[2] = result;
    }
    return result;
}

int main(int argc, char **argv){
    cout << "exercise - 0004" << endl;

    JOE_TIME_PROFILE_INIT()
    cout << "recursive fib()" << endl;
    for(int i = 1; i < 40 ; i++){
        JOE_TIME_PROFILE_START()
        int result = Fibonacci(i);
        std::string str = std::string("fib(") + to_string(i) + std::string(") = ") + to_string(result);
        JOE_TIME_PROFILE_COUNT(str)
    }
    cout << endl;

    cout << "interative fib()" << endl;
    for(int i = 1; i < 40 ; i++){
        JOE_TIME_PROFILE_START()
        int result = Fibonacci_iter(i);
        std::string str = std::string("fib(") + to_string(i) + std::string(") = ") + to_string(result);
        JOE_TIME_PROFILE_COUNT(str)
    }
    cout << endl;

    cout << "recursive fib() with LUT" << endl;
    vector<int> LUT;
    for(int i = 1; i < 40 ; i++){
        LUT.clear();
        LUT.resize(i+1,-1);//inital value = -1
        JOE_TIME_PROFILE_START()
        int result = Fibonacci_recur_mem(i,LUT);
        std::string str = std::string("fib(") + to_string(i) + std::string(") = ") + to_string(result);
        JOE_TIME_PROFILE_COUNT(str)
    }
    cout << endl;

    cout << "interative triple fib()" << endl;
    for(int i = 1; i < 40 ; i++){
        JOE_TIME_PROFILE_START()
        int result = TripleFibonacci_iter(i);
        std::string str = std::string("triple-fib(") + to_string(i) + std::string(") = ") + to_string(result);
        JOE_TIME_PROFILE_COUNT(str)
    }
    cout << endl;

    return 0;
};
