
#include "common.hpp"
#include "Number.hpp"

Number::Number(){
    word = "";
    argNum = 0;
    value = Complex(0, 0);
    opType = NUMBER;
    rankMatch = 5;
}

Number::Number(const int& x){
    word = '0' + x;
    argNum = 0;
    value = Complex(x, 0);
    opType = NUMBER;
    rankMatch = 5;
}

Number::Number(const char * name){
    word = name;
    argNum = 0;
    value = Complex(atof(name), 0);
    opType = NUMBER;
    rankMatch = 5;
}

//Number::Number(const std::string & name){
//    word = name;
//    argNum = 0;
//    data = Complex(0, 0);
//    opType = NUMBER;
//}

Number::Number(const char * name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    opType = NUMBER;
    rankMatch = 5;
}

Number::Number(const char& name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    opType = NUMBER;
    rankMatch = 5;
}

Complex * Number::execute(Complex * _) const{
    return new Complex(value);
}

Constant::Constant(const char * name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    opType = FUNCTION;
}

Constant::Constant(const char& name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    opType = FUNCTION;
}

Variable::Variable(const char * name){
    word = name;
    argNum = 0;
    value = Complex(0, 0);
    opType = FUNCTION;
}

Variable::Variable(const char * name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    opType = FUNCTION;
}

Variable::Variable(const char& name, const Complex&& x){
    word = name;
    argNum = 0;
    value = x;
    opType = FUNCTION;
}

Ans::Ans() : Variable("ans"){}

ImaginaryUnit::ImaginaryUnit(const char& name) : Constant(name, Complex(0, 1)){
    opType = IMAG_UNIT;
}

Pi::Pi() : Constant("pi", Complex(PI, 0)){}

E::E() : Constant("e", Complex(EULER_NUMBER, 0)){}
