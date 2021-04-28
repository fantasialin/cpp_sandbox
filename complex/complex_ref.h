#ifndef __MY_COMPLEX_REF__
#define __MY_COMPLEX_REF__

#include <iostream>

class complex;
complex& __doapl (complex& ths, const complex& r);
complex& __doami (complex& ths, const complex& r);
complex& __doaml (complex& ths, const complex& r);

class complex
{
public:
    complex (double r=0, double i=0): re(r), im(i){}
    complex (const complex& rhs) {this->re = rhs.re; this->im = rhs.im; std::cout << "copy ctor invoked!\n";} //copy constructor
    complex& operator = (const complex& rhs) {this->re = rhs.re; this->im = rhs.im; std::cout << "copy assignment invoked!\n"; return *this;} //copy assignment
    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    complex& operator *= (const complex&);
    complex& operator /= (const complex&);
    double real () const {return re;}
    double imag () const {return im;}

private:
    double re, im;

    friend complex& __doapl (complex&, const complex&);
    friend complex& __doami (complex&, const complex&);
    friend complex& __doaml (complex&, const complex&);
};

inline complex&
__doapl (complex& ths, const complex& r)
{
    ths.re += r.re;
    ths.im += r.im;
    return ths;
}

// operator +=
inline complex&
complex::operator += (const complex& r)
{
    return __doapl (*this, r);
}

inline complex& 
__doami (complex& ths, const complex& r)
{
    ths.re -= r.re;
    ths.im -= r.im;
    return ths;
}

// operator -=
inline complex&
complex::operator -= (const complex& r)
{
    return __doami (*this, r);
}

inline complex& 
__doaml (complex& ths, const complex& r)
{
    double f = ths.re * r.re - ths.im * r.im;
    ths.im = ths.re * r.im + ths.im * r.re;
    ths.re = f;
    return ths;
}

// operator *=
inline complex&
complex::operator *= (const complex& r)
{
    return __doaml (*this, r);
}

inline double
imag (const complex& x)
{
    return x.imag();
}

inline double
real (const complex& x)
{
    return x.real();
}

// operator +
inline complex
operator + (const complex& x, const complex& y)
{
    return complex(real(x)+real(y),imag(x)+imag(y));
}

inline complex
operator + (const complex& x, double y)
{
    return complex(real(x)+y,imag(x));
}

inline complex
operator + (double x, const complex& y)
{
    return complex(x+real(y),imag(y));
}

// operator -
inline complex
operator - (const complex& x, const complex& y)
{
    return complex(real(x)-real(y),imag(x)-imag(y));
}

inline complex
operator - (const complex& x, double y)
{
    return complex(real(x)-y,imag(x));
}

inline complex
operator - (double x, const complex& y)
{
    return complex(x-real(y),imag(y));
}

// operator *
inline complex
operator * (const complex& x, const complex& y)
{
    return complex(real(x)*real(y) - imag(x)*imag(y),
            real(x)*imag(y) + imag(x)*real(y));
}

inline complex
operator * (const complex& x, double y)
{
    return complex(real(x)*y,imag(x)*y);
}

inline complex
operator * (double x, const complex& y)
{
    return complex(x*real(y),x*imag(y));
}

// operator /
inline complex
operator / (const complex& x, double y)
{
    //std::cout << "operator divide\n"; no RVO
    return complex(real(x)/y,imag(x)/y);
}

// positive
inline complex
operator + (const complex& x)
{
    return x;
}

// negative
inline complex
operator - (const complex& x)
{
    return complex(-real(x),-imag(x));
}

// operator ==
inline bool
operator == (const complex& x, const complex& y)
{
    return (real(x) == real(y) && imag(x) == imag(y));
}

inline bool
operator == (const complex& x, double y)
{
    return (real(x) == y && imag(x) == 0.0);
}

inline bool
operator == (double x, const complex& y)
{
    return (x == real(y) && imag(y) == 0.0);
}


// operator !=
inline bool
operator != (const complex& x, const complex& y)
{
    return (real(x) != real(y) || imag(x) != imag(y));
}

inline bool
operator != (const complex& x, double y)
{
    return (real(x) != y || imag(x) != 0.0);
}

inline bool
operator != (double x, const complex& y)
{
    return (x != real(y) || imag(y) != 0.0);
}

#include <cmath>

inline complex
polar (double r, double t)
{
    return complex (r*cos(t), r*sin(t));
}

inline complex
conj (const complex& x)
{
    return complex (real(x), -imag(x));
}

inline double
norm (const complex& x)
{
    return real(x) * real (x) + imag (x) * imag(x);
}

#include <iostream>
using std::ostream;

ostream&
operator << (ostream& os, const complex& x)
{
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

#endif //__MY_COMPLEX_REF__