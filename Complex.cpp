#include "Complex.hpp"
#include "common.hpp"
#include <iostream>
#include <math.h>

Complex::Complex(){
    real = imag = 0;
}

Complex::Complex(const double& r, const double& i){
    real = r;
    imag = i;
    elimErr();
}

void Complex::setReal(const double& r){
    real = r;
    elimErr();
}

void Complex::setImag(const double& i){
    imag = i;
    elimErr();
}

void Complex::setMagn(const double& m){
    double r = m * cos(atan2(imag, real));
    double i = m * sin(atan2(imag, real));
    real = r;
    imag = i;
    elimErr();
}

void Complex::setAngl(const double& a){
    double r = sqrt(pow(real, 2) + pow(imag, 2)) * cos(a);
    double i = sqrt(pow(real, 2) + pow(imag, 2)) * sin(a);
    real = r;
    imag = i;
    elimErr();
}

void Complex::setAbi(const double& r, const double& i){
    real = r;
    imag = i;
    elimErr();
}
void Complex::setCis(const double& m, const double& a){
    real = m * cos(a);
    imag = m * sin(a);
    elimErr();
}

double Complex::getReal() const{
    return real;
}

double Complex::getImag() const{
    return imag;
}

double Complex::getMagn() const{
    return sqrt(pow(real, 2) + pow(imag, 2));
}

double Complex::getAngl() const{
    return atan2(imag, real);
}

Complex Complex::conjugate(const Complex& z) const{
    return Complex(z.getReal(), -1 * z.getImag());
}

Complex Complex::operator+(const Complex& z) const{
    Complex result(this->getReal() + z.getReal(), this->getImag() + z.getImag());
    if(abs(result.getReal()) < VERY_SMALL_DOUBLE &&
        (abs(result.getReal() / this->getReal()) < VERY_SMALL_DOUBLE || abs(result.getReal() / z.getReal()) < VERY_SMALL_DOUBLE))
            result.setReal(0);
    if(abs(result.getImag()) < VERY_SMALL_DOUBLE &&
        (abs(result.getImag() / this->getImag()) < VERY_SMALL_DOUBLE || abs(result.getImag() / z.getImag()) < VERY_SMALL_DOUBLE))
            result.setImag(0);
    return result;
}

Complex Complex::operator-(const Complex& z) const{
    Complex result(this->getReal() - z.getReal(), this->getImag() - z.getImag());
    if(abs(result.getReal()) < VERY_SMALL_DOUBLE &&
        (abs(result.getReal() / this->getReal()) < VERY_SMALL_DOUBLE || abs(result.getReal() / z.getReal()) < VERY_SMALL_DOUBLE))
            result.setReal(0);
    if(abs(result.getImag()) < VERY_SMALL_DOUBLE &&
        (abs(result.getImag() / this->getImag()) < VERY_SMALL_DOUBLE || abs(result.getImag() / z.getImag()) < VERY_SMALL_DOUBLE))
            result.setImag(0);
    return result;
}

Complex Complex::operator*(const Complex& z) const{
    Complex result(this->getReal() * z.getReal() - this->getImag() * z.getImag(),
                    this->getReal() * z.getImag() + this->getImag() * z.getReal());
    return result;
}

Complex Complex::operator/(const Complex& z) const{
    Complex result = conjugate(z);
    result = result * *this;
    double divider = pow(z.getReal(), 2) + pow(z.getImag(), 2);
    result.setReal(result.getReal() / divider);
    result.setImag(result.getImag() / divider);
    return result;
}

Complex Complex::complexPow(const Complex& z) const{
    Complex result(0, 0);
    if(getMagn() == 0)
        return Complex(0, 0);
    result.setMagn(pow(getMagn(), z.getReal()) * pow(EULER_NUMBER, (-1 * z.getImag() * getAngl())));
    result.setAngl(z.getImag() * log(getMagn()) + z.getReal() * getAngl());
    return result;
}

Complex Complex::complexPow(const double& i) const{
    Complex result(0, 0);
    result.setMagn(pow(getMagn(), i));
    result.setAngl(getAngl() * i);
    return result;
}
