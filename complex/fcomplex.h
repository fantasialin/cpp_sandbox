#ifndef __MY_FCOMPLEX__
#define __MY_FCOMPLEX__

#include <iostream>

extern "C++" {

template <>
class complex<float>
{
public:
    complex (float r=0, float i=0): re(r), im(i){}
    explicit complex (const complex<double>& r) {this->re = (float)r.real(); this->im = (float)r.imag();}
    explicit complex (const complex<long double>& r) {this->re = r.real(); this->im = r.imag();}

    complex (const complex& rhs) {this->re = rhs.re; this->im = rhs.im; std::cout << "fc copy ctor invoked!\n";} //copy constructor
    complex& operator = (const complex& rhs) {this->re = rhs.re; this->im = rhs.im; std::cout << "fc copy assignment invoked!\n"; return *this;} //copy assignment

    complex& operator += (const complex& r) { return __doapl (*this, r);}
    complex& operator -= (const complex& r) { return __doami (*this, r);}
    complex& operator *= (const complex& r) { return __doaml (*this, r);}
    
    float real () const {return re;}
    float imag () const {return im;}

private:
    float re, im;

    friend complex& __doapl <> (complex&, const complex&);
    friend complex& __doami <> (complex&, const complex&);
    friend complex& __doaml <> (complex&, const complex&);

    #ifndef __STRICT_ANSI__
    friend inline complex operator + (const complex& x, float y) { return operator +<> (x,y);}
    friend inline complex operator + (float x, const complex& y) { return operator +<> (x,y);}
    friend inline complex operator - (const complex& x, float y) { return operator -<> (x,y);}
    friend inline complex operator - (float x, const complex& y) { return operator -<> (x,y);}
    friend inline complex operator * (const complex& x, float y) { return operator *<> (x,y);}
    friend inline complex operator * (float x, const complex& y) { return operator *<> (x,y);}
    friend inline complex operator / (const complex& x, float y) { return operator /<> (x,y);}
    friend inline complex operator == (const complex& x, float y) { return operator ==<> (x,y);}
    friend inline complex operator == (float x, const complex& y) { return operator ==<> (x,y);}
    friend inline complex operator != (const complex& x, float y) { return operator !=<> (x,y);}
    friend inline complex operator != (float x, const complex& y) { return operator !=<> (x,y);}
    #endif //__STRICT_ANSI__
};

} //extern "c++"

#endif //__MY_FCOMPLEX__