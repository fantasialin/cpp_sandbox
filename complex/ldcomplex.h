#ifndef __MY_LDCOMPLEX__
#define __MY_LDCOMPLEX__


extern "C++" {

template <>
class complex<long double>
{
public:
    complex (long double r=0, long double i=0): re(r), im(i){}
    explicit complex (const complex<double>& r) {this->re = r.real(); this->im = r.imag();}
    explicit complex (const complex<float>& r) {this->re = r.real(); this->im = r.imag();}

    complex& operator += (const complex& r) { return __doapl (*this, r);}
    complex& operator -= (const complex& r) { return __doami (*this, r);}
    complex& operator *= (const complex& r) { return __doaml (*this, r);}
    
    long double real () const {return re;}
    long double imag () const {return im;}

private:
    long double re, im;

    friend complex& __doapl <> (complex&, const complex&);
    friend complex& __doami <> (complex&, const complex&);
    friend complex& __doaml <> (complex&, const complex&);

    #ifndef __STRICT_ANSI__
    friend inline complex operator + (const complex& x, long double y) { return operator +<> (x,y);}
    friend inline complex operator + (long double x, const complex& y) { return operator +<> (x,y);}
    friend inline complex operator - (const complex& x, long double y) { return operator -<> (x,y);}
    friend inline complex operator - (long double x, const complex& y) { return operator -<> (x,y);}
    friend inline complex operator * (const complex& x, long double y) { return operator *<> (x,y);}
    friend inline complex operator * (long double x, const complex& y) { return operator *<> (x,y);}
    friend inline complex operator / (const complex& x, long double y) { return operator /<> (x,y);}
    friend inline complex operator == (const complex& x, long double y) { return operator ==<> (x,y);}
    friend inline complex operator == (long double x, const complex& y) { return operator ==<> (x,y);}
    friend inline complex operator != (const complex& x, long double y) { return operator !=<> (x,y);}
    friend inline complex operator != (long double x, const complex& y) { return operator !=<> (x,y);}
    #endif //__STRICT_ANSI__
};

} //extern "c++"

#endif //__MY_LDCOMPLEX__