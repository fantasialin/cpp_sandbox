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

int main(int argc, char **argv){
    cout << "variadic template" << endl;

    long sum = adder(1, 2, 3, 4, 5, 6, 7, 8, 9);

    cout << " sum 1 + 2 + 3 + ... + 9 = " << sum << endl;

    string s1 ="A ", s2 ="Farewell ", s3 = "to ", s4="Arms.";

    string nNmae = adder(s1, s2, s3, s4);

    cout << "Novel = " << nNmae << endl;

    #if _debug_
        cout << "debug test" << endl;
    #endif

    return 0;
}