#ifndef COMPLEX_HPP_INCLUDED
#define COMPLEX_HPP_INCLUDED

#include <iostream>
#include <math.h>
#include "config.hpp"

#define COMPLEX_PRINT 'z'

class Complex{
public:
    Complex();
    Complex(const double&, const double&);
    Complex operator+(const Complex&) const;
    Complex operator-(const Complex&) const;
    Complex operator*(const Complex&) const;
    Complex operator/(const Complex&) const;
    Complex complexPow(const Complex&) const;
    Complex complexPow(const double&) const;
    Complex conjugate(const Complex&) const;
    friend class ImaginaryUnitDisplay;
    void setAbi(const double&, const double&);
    void setCis(const double&, const double&);
    void setReal(const double&);
    void setImag(const double&);
    void setMagn(const double&);
    void setAngl(const double&);
    double getReal() const;
    double getImag() const;
    double getMagn() const;
    double getAngl() const;
private:
    void elimErr(){
        bool clrReal = (imag != 0) && (abs(real / imag) < VERY_SMALL_DOUBLE);
        bool clrImag = (real != 0) && (abs(imag / real) < VERY_SMALL_DOUBLE);
        if(clrReal)
            real = 0;
        if(clrImag)
            imag = 0;
    }
    double real;
    double imag;
};

#endif // COMPLEX_HPP_INCLUDED
