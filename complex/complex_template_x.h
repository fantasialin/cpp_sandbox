#ifndef __MY_COMPLEX_TEMPLATE_X__
#define __MY_COMPLEX_TEMPLATE_X__


template <typename T> class complex;
template <typename T> complex<T>& __doapl (complex<T>& ths, const complex<T>& r);
template <typename T> complex<T>& __doami (complex<T>& ths, const complex<T>& r);
template <typename T> complex<T>& __doaml (complex<T>& ths, const complex<T>& r);

template <typename T>
class complex
{
public:
    complex (T r=0, T i=0): re(r), im(i){}
    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    complex& operator *= (const complex&);
    complex& operator /= (const complex&);
    T real () const {return re;}
    T imag () const {return im;}

private:
    T re, im;

    friend complex& __doapl <> (complex&, const complex&);
    friend complex& __doami <> (complex&, const complex&);
    friend complex& __doaml <> (complex&, const complex&);
};

//declare specializations.
//template <> class complex<float>;
//template <> class complex<double>;
//template <> class complex<long double>;

template <typename T>
inline complex<T>&
__doapl (complex<T>& ths, const complex<T>& r)
{
    ths.re += r.re;
    ths.im += r.im;
    return ths;
}

// operator +=
template <typename T>
inline complex<T>&
complex<T>::operator += (const complex<T>& r)
{
    return __doapl (*this, r);
}

template <typename T>
inline complex<T>& 
__doami (complex<T>& ths, const complex<T>& r)
{
    ths.re -= r.re;
    ths.im -= r.im;
    return ths;
}

// operator -=
template <typename T>
inline complex<T>&
complex<T>::operator -= (const complex<T>& r)
{
    return __doami (*this, r);
}

template <typename T>
inline complex<T>& 
__doaml (complex<T>& ths, const complex<T>& r)
{
    T f = ths.re * r.re - ths.im * r.im;
    ths.im = ths.re * r.im + ths.im * r.re;
    ths.re = f;
    return ths;
}

// operator *=
template <typename T>
inline complex<T>&
complex<T>::operator *= (const complex<T>& r)
{
    return __doaml (*this, r);
}

template <typename T>
inline T
imag (const complex<T>& x)
{
    return x.imag();
}

template <typename T>
inline T
real (const complex<T>& x)
{
    return x.real();
}

// operator +
template <typename T>
inline complex<T>
operator + (const complex<T>& x, const complex<T>& y)
{
    return complex<T>(real(x)+real(y),imag(x)+imag(y));
}

template <typename T>
inline complex<T>
operator + (const complex<T>& x, T y)
{
    return complex<T>(real(x)+y,imag(x));
}

template <typename T>
inline complex<T>
operator + (T x, const complex<T>& y)
{
    return complex<T>(x+real(y),imag(y));
}

// operator -
template <typename T>
inline complex<T>
operator - (const complex<T>& x, const complex<T>& y)
{
    return complex<T>(real(x)-real(y),imag(x)-imag(y));
}

template <typename T>
inline complex<T>
operator - (const complex<T>& x, T y)
{
    return complex<T>(real(x)-y,imag(x));
}

template <typename T>
inline complex<T>
operator - (T x, const complex<T>& y)
{
    return complex<T>(x-real(y),imag(y));
}

// operator *
template <typename T>
inline complex<T>
operator * (const complex<T>& x, const complex<T>& y)
{
    return complex<T>(real(x)*real(y) - imag(x)*imag(y),
            real(x)*imag(y) + imag(x)*real(y));
}

template <typename T>
inline complex<T>
operator * (const complex<T>& x, T y)
{
    return complex<T>(real(x)*y,imag(x)*y);
}

template <typename T>
inline complex<T>
operator * (T x, const complex<T>& y)
{
    return complex<T>(x*real(y),x*imag(y));
}

// operator /
template <typename T>
inline complex<T>
operator / (const complex<T>& x, T y)
{
    return complex<T>(real(x)/y,imag(x)/y);
}

// positive
template <typename T>
inline complex<T>
operator + (const complex<T>& x)
{
    return x;
}

// negative
template <typename T>
inline complex<T>
operator - (const complex<T>& x)
{
    return complex<T>(-real(x),-imag(x));
}

// operator ==
template <typename T>
inline bool
operator == (const complex<T>& x, const complex<T>& y)
{
    return (real(x) == real(y) && imag(x) == imag(y));
}

template <typename T>
inline bool
operator == (const complex<T>& x, T y)
{
    return (real(x) == y && imag(x) == 0.0);
}

template <typename T>
inline bool
operator == (T x, const complex<T>& y)
{
    return (x == real(y) && imag(y) == 0.0);
}


// operator !=
template <typename T>
inline bool
operator != (const complex<T>& x, const complex<T>& y)
{
    return (real(x) != real(y) || imag(x) != imag(y));
}

template <typename T>
inline bool
operator != (const complex<T>& x, T y)
{
    return (real(x) != y || imag(x) != 0.0);
}

template <typename T>
inline bool
operator != (T x, const complex<T>& y)
{
    return (x != real(y) || imag(y) != 0.0);
}

#include <cmath>

template <typename T>
inline complex<T>
polar (T r, T t)
{
    return complex<T> (r*cos(t), r*sin(t));
}

template <typename T>
inline complex<T>
conj (const complex<T>& x)
{
    return complex<T> (real(x), -imag(x));
}

template <typename T>
inline T
norm (const complex<T>& x)
{
    return real(x) * real (x) + imag (x) * imag(x);
}

#include <iostream>
using std::ostream;

template <typename T>
ostream&
operator << (ostream& os, const complex<T>& x)
{
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

//declare specializations.
template <> class complex<float>;
//template <> class complex<double>;
//template <> class complex<long double>;

// implementation of specializations...
#include "fcomplex.h"
//#include "dcomplex.h"
//#include "ldcomplex.h"

#endif //__MY_COMPLEX_TEMPLATE_X__