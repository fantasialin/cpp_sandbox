#include <iostream>


using namespace std;

template<typename T>
T adder(T v) {
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args){
    return first + adder(args...);
}

int main(int argc, char **argv){
    cout << "variadic template" << endl;

    long sum = adder(1, 2, 3, 4, 5, 6, 7, 8, 9);

    cout << " sum 1 + 2 + 3 + ... + 9 = " << sum << endl;

    return 0;
}