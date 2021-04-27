#ifndef __MY_COMPLEX_TEMPLATE__
#define __MY_COMPLEX_TEMPLATE__


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
};

// operator +=
template <typename T>
inline complex<T>&
complex<T>::operator += (const complex<T>& r)
{
    this->re += r.re;
    this->im += r.im;
    return *this;
}

// operator -=
template <typename T>
inline complex<T>&
complex<T>::operator -= (const complex<T>& r)
{
    this->re -= r.re;
    this->im -= r.re;
    return *this;
}

// operator *=
template <typename T>
inline complex<T>&
complex<T>::operator *= (const complex<T>& r)
{
    T f = this->re * r.re - this->im * r.im;
    this->im = this->re * r.im + this->im * r.re;
    this->re = f;
    return *this;
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

#endif //__MY_COMPLEX_TEMPLATE__