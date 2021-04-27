#ifndef __MY_DCOMPLEX__
#define __MY_DCOMPLEX__


extern "C++" {

template <>
class complex<double>
{
public:
    complex (double r=0, double i=0): re(r), im(i){}
    explicit complex (const complex<float>& r) {this->re = r.real(); this->im = r.imag();}
    explicit complex (const complex<long double>& r) {this->re = r.real(); this->im = r.imag();}

    complex& operator += (const complex& r) { return __doapl (*this, r);}
    complex& operator -= (const complex& r) { return __doami (*this, r);}
    complex& operator *= (const complex& r) { return __doaml (*this, r);}
    
    double real () const {return re;}
    double imag () const {return im;}

private:
    double re, im;

    friend complex& __doapl <> (complex&, const complex&);
    friend complex& __doami <> (complex&, const complex&);
    friend complex& __doaml <> (complex&, const complex&);

    #ifndef __STRICT_ANSI__
    friend inline complex operator + (const complex& x, double y) { return operator +<> (x,y);}
    friend inline complex operator + (double x, const complex& y) { return operator +<> (x,y);}
    friend inline complex operator - (const complex& x, double y) { return operator -<> (x,y);}
    friend inline complex operator - (double x, const complex& y) { return operator -<> (x,y);}
    friend inline complex operator * (const complex& x, double y) { return operator *<> (x,y);}
    friend inline complex operator * (double x, const complex& y) { return operator *<> (x,y);}
    friend inline complex operator / (const complex& x, double y) { return operator /<> (x,y);}
    friend inline complex operator == (const complex& x, double y) { return operator ==<> (x,y);}
    friend inline complex operator == (double x, const complex& y) { return operator ==<> (x,y);}
    friend inline complex operator != (const complex& x, double y) { return operator !=<> (x,y);}
    friend inline complex operator != (double x, const complex& y) { return operator !=<> (x,y);}
    #endif //__STRICT_ANSI__
};

} //extern "c++"

#endif //__MY_DCOMPLEX__