#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include <complex>

#include <type_traits>
#include <typeinfo>

using namespace std;

int main(int argc, char **argv){
    cout << "tupple test" << endl;

    cout << "string size of = " << sizeof(string) << endl;
    cout << "double size of = " << sizeof(double) << endl;
    cout << "float size of = " << sizeof(float) << endl;
    cout << "int size of = " << sizeof(int) << endl;
    cout << "complex<double> size of = " << sizeof(complex<double>) << endl;

    //tuples
    //create a four-element tuple
    // - elements are initialized with default value (0 for fundamental type)
    tuple<string, int, int, complex<double>> t;
    cout << "size of tuple t = " << sizeof(t) << endl;

    // create and initialize a tuple explicity
    tuple<int, float, string> t1(41, 6.3, "nico");
    cout << "sizeof tuple<int, float, string> = " << sizeof(t1) << endl;
    //iterate over elements:
    cout << "t1 : " << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1) << endl;

    //create tuple with make_tuple()
    auto t2 = make_tuple(22, 44, "stacy");
    cout << "t2 : " << get<0>(t2) << " " << get<1>(t2) << " " << get<2>(t2) << endl;

    //assign second value in t2 to t1
    get<1>(t1) = get<1>(t2);
    cout << "t1 : " << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1) << endl;
    cout << "sizeof tuple<int, float, string> t1 = " << sizeof(t1) << endl;
    cout << "t2 : " << get<0>(t2) << " " << get<1>(t2) << " " << get<2>(t2) << endl;

    //comparison and assignment
    // - including type conversion from tuple<int, int, string>
    // to tuple<int, float, string>
    if( t1 < t2 ) { //compares value from value
        cout << "t1 < t2" << endl;
    }
    else {
        cout << "t1 >= t2" << endl;
    }

    t1 = t2;//OK, assigns value from value
    #if WIN32
    cout << t1 << endl;
    cout << t2 << endl;
    #endif

    tuple<int, float, string> t3(77, 1.1, "more light");
    int i1;
    float f1;
    string s1;
    tie(i1, f1, s1) = t3; //assigns values of t3 to i1, f1 and s1
    cout << "tie : " << i1 << " " << f1 << " " << s1 << endl;

    typedef tuple<int, float, string> TupleType;
    cout << tuple_size<TupleType>::value << endl;
    tuple_element<1, TupleType>::type f2 = 1.2; //yields float
    cout << "f2 : " << typeid(f2).name() << " = " << f2 << endl;
    cout << "t3 : " << typeid(t3).name() << endl;
    
    typedef tuple_element<1, TupleType>::type T;
    cout << "T type is : " << typeid(T).name() << endl;

    return 0;
}