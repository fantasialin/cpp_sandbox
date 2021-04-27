
#include "complex_template.h"
#include <iostream>

using std::cout;
using std::endl;

//typedef long double T;
//typedef double T;
typedef float T;

int main(){
    complex<T> c1(2,1);    cout << c1 << endl;
    complex<T> c2(4);      cout << c2 << endl;

    complex<T> *p = new complex<T>(1,2);  cout << *p << endl;
    delete p;

    complex<T> *pa = new complex<T>[3];   
    cout << *pa << endl;
    cout << *(pa+1) << endl;
    cout << *(pa+2) << endl;

    delete[] pa;

    complex<T> objs[3];
    objs[0] = complex<T>(5,5);     cout << objs[0] << endl;
    objs[1] = complex<T>(6,6);     cout << objs[1] << endl;
    objs[2] = complex<T>(7,7);     cout << objs[2] << endl;

    cout << (c1 += c2) << endl;
    cout << (c1 -= c2) << endl;
    cout << (c1 *= c2) << endl;

    cout << real(c1) << endl;
    cout << imag(c1) << endl;

    cout << (c1 + c2) << endl;
    cout << (c1 + (T)9.28) << endl;
    cout << ((T)4.28 + c1) << endl;

    cout << (c1 - c2) << endl;
    cout << (c1 - (T)9.28) << endl;
    cout << ((T)4.28 - c1) << endl;

    cout << (c1 * c2) << endl;
    cout << (c1 * (T)9.28) << endl;
    cout << ((T)4.28 * c1) << endl;

    cout << (c1 / (T)2.0) << endl;

    cout << +c1 << endl;
    cout << -c1 << endl;

    cout << (c1 == c2) << endl;
    cout << (c1 == (T)9.28) << endl;
    cout << ((T)4.28 == c1) << endl;

    cout << (c1 != c2) << endl;
    cout << (c1 != (T)9.28) << endl;
    cout << ((T)4.28 != c1) << endl;

    cout << polar((T)10,(T)4) << endl;
    cout << conj(c1) << endl;
    cout << norm(c1) << endl;

    cout << objs[0] << endl;
    objs[2] = objs[1] = objs[0];
    cout << objs[1] << endl << objs[2] << endl;
    objs[2] = objs[2] + objs[1] + objs[0];
    cout << objs[2] << endl;


    return 0;
}