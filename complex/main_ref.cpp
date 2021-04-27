
#include "complex_ref.h"
#include <iostream>

using std::cout;
using std::endl;

int main(){
    complex c1(2,1);    cout << c1 << endl;
    complex c2(4);      cout << c2 << endl;

    complex *p = new complex(1,2);  cout << *p << endl;
    delete p;

    complex *pa = new complex[3];   
    cout << *pa << endl;
    cout << *(pa+1) << endl;
    cout << *(pa+2) << endl;

    delete[] pa;

    complex objs[3];
    objs[0] = complex(5,5);     cout << objs[0] << endl;
    objs[1] = complex(6,6);     cout << objs[1] << endl;
    objs[2] = complex(7,7);     cout << objs[2] << endl;

    cout << (c1 += c2) << endl;
    cout << (c1 -= c2) << endl;
    cout << (c1 *= c2) << endl;

    cout << real(c1) << endl;
    cout << imag(c1) << endl;

    cout << (c1 + c2) << endl;
    cout << (c1 + 9.28) << endl;
    cout << (4.28 + c1) << endl;

    cout << (c1 - c2) << endl;
    cout << (c1 - 9.28) << endl;
    cout << (4.28 - c1) << endl;

    cout << (c1 * c2) << endl;
    cout << (c1 * 9.28) << endl;
    cout << (4.28 * c1) << endl;

    cout << (c1 / 2.0) << endl;

    cout << +c1 << endl;
    cout << -c1 << endl;

    cout << (c1 == c2) << endl;
    cout << (c1 == 9.28) << endl;
    cout << (4.28 == c1) << endl;

    cout << (c1 != c2) << endl;
    cout << (c1 != 9.28) << endl;
    cout << (4.28 != c1) << endl;

    cout << polar(10,4) << endl;
    cout << conj(c1) << endl;
    cout << norm(c1) << endl;

    cout << objs[0] << endl;
    objs[2] = objs[1] = objs[0];
    cout << objs[1] << endl << objs[2] << endl;
    objs[2] = objs[2] + objs[1] + objs[0];
    cout << objs[2] << endl;


    return 0;
}