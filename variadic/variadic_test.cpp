#include <iostream>


using namespace std;

#define _DEBUG_ 1
constexpr int _debug_ = 0;

template<typename T>
T adder(T v) {
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args){
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    return first + adder(args...);
}


template<typename T>
bool pair_comparer(T a){
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    //floating point might not correct to use "==" to compare
    return false;
}

template<typename T>
bool pair_comparer(T a, T b){
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    //floating point might not correct to use "==" to compare
    return a == b;
}

template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    return a == b && pair_comparer(args...);
}


template<class... Ts> struct tuple_custom {
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
};

template<class T, class... Ts>
struct tuple_custom<T, Ts...> : tuple_custom<Ts...> {
    tuple_custom(T t, Ts... ts) : tuple_custom<Ts...>(ts...), tail(t) {
        #ifndef WIN32
        #if _DEBUG_
        cout << __PRETTY_FUNCTION__ << endl;
        #endif
        #endif
    }

    T tail;
};

int main(int argc, char **argv){
    cout << "variadic template" << endl;

    long sum = adder(1, 2, 3, 4, 5, 6, 7, 8, 9);

    cout << " sum 1 + 2 + 3 + ... + 9 = " << sum << endl;

    string s1 ="A ", s2 ="Farewell ", s3 = "to ", s4="Arms.";

    string nNmae = adder(s1, s2, s3, s4);

    cout << "Novel = " << nNmae << endl;

    cout << "pair compare (1.5 , 1.5, 2, 2, 6, 6) : " << pair_comparer(1.5 , 1.5, 2, 2, 6, 6) << endl;
    // does not compile; the compiler complains that the base case expects 2 arguments but only 1 is provied (if 1 argument base case is not provided).
    cout << "pair compare (1.5 , 1.5, 2, 2, 6, 6, 7) : " << pair_comparer(1.5 , 1.5, 2, 2, 6, 6, 7) << endl; 


    tuple_custom<double, uint64_t, const char*> t1(12.2, 42, "big");

    return 0;
}