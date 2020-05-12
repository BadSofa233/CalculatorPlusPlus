#include "common.hpp"
#include "Number.hpp"

Number::Number(){
    word = "";
    argNum = 0;
    value = Complex(0, 0);
    type = NUMBER;
    rankMatch = 5;
}

Number::Number(const int& x){
    word = '0' + x;
    argNum = 0;
    value = Complex(x, 0);
    type = NUMBER;
    rankMatch = 5;
}

Number::Number(const char * name){
    word = name;
    argNum = 0;
    value = Complex(atof(name), 0);
    type = NUMBER;
    rankMatch = 5;
}

Number::Number(const char * name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    type = NUMBER;
    rankMatch = 5;
}

Number::Number(const char& name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    type = NUMBER;
    rankMatch = 5;
}

Complex * Number::execute(Complex * _) const{
    return new Complex(value);
}

Constant::Constant(const char * name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    type = NUMBER;
}

Constant::Constant(const char& name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    type = NUMBER;
}

Variable::Variable(const char * name){
    word = name;
    argNum = 0;
    value = Complex(0, 0);
    type = NUMBER;
}

Variable::Variable(const char * name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    type = NUMBER;
}

Variable::Variable(const char& name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    type = NUMBER;
}

Ans::Ans() : Variable("ans"){}

ImaginaryUnit::ImaginaryUnit(const char& name) : Constant(name, Complex(0, 1)){
    type = NUMBER;
}

Pi::Pi() : Constant("pi", Complex(PI, 0)){}

E::E() : Constant("e", Complex(EULER_NUMBER, 0)){}
