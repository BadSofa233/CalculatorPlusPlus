#include "MathFunctions.hpp"
#include "common.hpp"

MathFunctions::MathFunctions() : PostposOp(){
    argNum = 1;
    //command = 0;
    rankMatch = 4;
    opType = FUNCTION;
}

Complex* MathFunctions::execute(Complex* x) const{
    std::cout << "MathFunctions ()\n";
    return nullptr;
}

Sin::Sin() : MathFunctions(){
    word = "sin";
}

Complex* Sin::execute(Complex* x) const{
    x->setAbi(sin(GIO.AngIO.d2r(x->getReal())) * cosh(GIO.AngIO.d2r(x->getImag())),
              cos(GIO.AngIO.d2r(x->getReal())) * sinh(GIO.AngIO.d2r(x->getImag())));
    return x;
}

Cos::Cos() : MathFunctions(){
    word = "cos";
}

Complex* Cos::execute(Complex* x) const{
    x->setAbi(cos(GIO.AngIO.d2r(x->getReal())) * cosh(GIO.AngIO.d2r(x->getImag())),
              sin(GIO.AngIO.d2r(x->getReal())) * sinh(GIO.AngIO.d2r(x->getImag())));
    return x;
}

Tan::Tan() : MathFunctions(){
    word = "tan";
}

Complex* Tan::execute(Complex* x) const{
    Complex SinOfX(sin(GIO.AngIO.d2r(x->getReal())) * cosh(GIO.AngIO.d2r(x->getImag())),
                   cos(GIO.AngIO.d2r(x->getReal())) * sinh(GIO.AngIO.d2r(x->getImag())));
    Complex CosOfX(cos(GIO.AngIO.d2r(x->getReal())) * cosh(GIO.AngIO.d2r(x->getImag())),
                   sin(GIO.AngIO.d2r(x->getReal())) * sinh(GIO.AngIO.d2r(x->getImag())));
    *x = SinOfX / CosOfX;
    return x;
}

Cot::Cot() : MathFunctions(){
    word = "cot";
}

Complex* Cot::execute(Complex* x) const{
    Complex SinOfX(sin(GIO.AngIO.d2r(x->getReal())) * cosh(GIO.AngIO.d2r(x->getImag())),
                   cos(GIO.AngIO.d2r(x->getReal())) * sinh(GIO.AngIO.d2r(x->getImag())));
    Complex CosOfX(cos(GIO.AngIO.d2r(x->getReal())) * cosh(GIO.AngIO.d2r(x->getImag())),
                   sin(GIO.AngIO.d2r(x->getReal())) * sinh(GIO.AngIO.d2r(x->getImag())));
    *x = CosOfX / SinOfX;
    return x;
}

Sinh::Sinh() : MathFunctions(){
    word = "sinh";
}

Complex* Sinh::execute(Complex* x) const{
    x->setAbi(sinh(GIO.AngIO.d2r(x->getReal())) * cos(GIO.AngIO.d2r(x->getImag())),
              cosh(GIO.AngIO.d2r(x->getReal())) * sin(GIO.AngIO.d2r(x->getImag())));
    return x;
}

Cosh::Cosh() : MathFunctions(){
    word = "cosh";
}

Complex* Cosh::execute(Complex* x) const{
    x->setAbi(cosh(GIO.AngIO.d2r(x->getReal())) * cos(GIO.AngIO.d2r(x->getImag())),
              sinh(GIO.AngIO.d2r(x->getReal())) * sin(GIO.AngIO.d2r(x->getImag())));
    return x;
}

Tanh::Tanh() : MathFunctions(){
    word = "tanh";
}

Complex* Tanh::execute(Complex* x) const{
    Complex SinhOfX(sinh(GIO.AngIO.d2r(x->getReal())) * cos(GIO.AngIO.d2r(x->getImag())),
                    cosh(GIO.AngIO.d2r(x->getReal())) * sin(GIO.AngIO.d2r(x->getImag())));
    Complex CoshOfX(cosh(GIO.AngIO.d2r(x->getReal())) * cos(GIO.AngIO.d2r(x->getImag())),
                    sinh(GIO.AngIO.d2r(x->getReal())) * sin(GIO.AngIO.d2r(x->getImag())));
    *x = SinhOfX / CoshOfX;
    return x;
}

Ln::Ln() : MathFunctions(){
    word = "ln";
}

Complex* Ln::execute(Complex* x) const{
    x->setAbi(log(x->getMagn()),
              GIO.AngIO.r2d(x->getAngl()));
    return x;
}

Asin::Asin() : Ln(){
    word = "asin";
}

Complex* Asin::execute(Complex* x) const{
    Complex* result = new Complex(0, 0);
    Complex temp(1, 0); // temp = 1
    *result = temp - x->complexPow(2); // 1-x^2
    *result = result->complexPow(0.5); // sqrt(1-x^2)
    temp.setAbi(0, 1); // temp = i
    *result = (*x) * temp + *result; // ix + sqrt(1-x^2)
    result = Ln::execute(result); // ln(ix + sqrt(1-x^2))
    temp.setAbi(0, -1); // temp = -i
    *x = (*result) * temp; // -iln(ix + sqrt(1-x^2))
    delete result;
    return x;
}

Acos::Acos() : Ln(){
    word = "acos";
}

Complex* Acos::execute(Complex* x) const{
    Complex* result = new Complex(0, 0);
    Complex temp(1, 0); // temp = 1
    *result = temp - x->complexPow(2); // 1-x^2
    *result = result->complexPow(0.5); // sqrt(1-x^2)
    temp.setAbi(0, 1); // temp = i
    *result = (*x) + temp * (*result); // x + sqrt(1-x^2)i
    result = Ln::execute(result); // ln(x + sqrt(1-x^2)i)
    temp.setAbi(0, -1); // temp = -i
    *x = *result * temp; // -iln(x + sqrt(1-x^2)i)
    delete result;
    return x;
}

Atan::Atan() : Ln(){
    word = "atan";
}

Complex* Atan::execute(Complex* x) const{
    Complex* result = new Complex(0, 0);
    Complex temp(0, 1); // temp = i
    *result = (temp + (*x)) / ( temp - (*x)); // (i+x)/(i-x)
    result = Ln::execute(result); // ln((i+x)/(i-x))
    temp.setAbi(0, 0.5); // temp = i/2
    *x = (*result) * temp; // (i/2)ln((i+x)/(i-x))
    delete result;
    return x;
}

Acot::Acot() : Atan(){
    word = "acot";
}

Complex* Acot::execute(Complex* x) const{
    Complex result(1, 0);
    *x = result / (*x); // 1/x
    return Atan::execute(x); // atan(1/x)
}

Asinh::Asinh() : Asin(){
    word = "asinh";
}

Complex* Asinh::execute(Complex* x) const{
    Complex* result = new Complex(1, 0); // result = 1
    *result = x->complexPow(2) + (*result); // 1+x^2
    *result = result->complexPow(0.5) + (*x); // x+sqrt(1+x^2)
    *x = *(Ln::execute(result));
    x->setReal(GIO.AngIO.r2d(result->getReal()));
    delete result;
    return x;
}

Acosh::Acosh() : Ln(){
    word = "acosh";
}

Complex* Acosh::execute(Complex* x) const{
    Complex* result = new Complex(1, 0); // result = 1
    *result = x->complexPow(2) - (*result); // (x^2)-1
    *result = result->complexPow(0.5) + (*x);
    *x = *(Ln::execute(result));
    x->setReal(GIO.AngIO.r2d(result->getReal()));
    delete result;
    return x;
}

Atanh::Atanh() : Ln(){
    word = "atanh";
}

Complex* Atanh::execute(Complex* x) const{
    Complex* result = new Complex(0, 0);
    Complex* temp = new Complex(1, 0);
    *result = (*temp) - (*x); // 1-x
    result = Ln::execute(result); // ln(1-x)
    *temp = (*temp) + (*x); // 1+x
    temp = Ln::execute(temp); // ln(1+x)
    *result = (*temp) - (*result); // ln(1+x)-ln(1-x)
    temp->setAbi(0.5, 0); // temp = 1/2
    *x = (*temp) * (*result); // (1/2)(ln(1+x)-ln(1-x))
    x->setReal(GIO.AngIO.r2d(result->getReal()));
    delete temp; delete result;
    return x;
}

Log::Log() : Ln(){
    word = "log";
}

Complex* Log::execute(Complex* x) const{
    Complex lnOf10(log(10), 0);
    x = Ln::execute(x);
    *x = (*x) / lnOf10;
    return x;
}

Db::Db() : Log(){
    word = "db";
}

Complex* Db::execute(Complex* x) const{
    Complex twenty(20, 0);
    x = Log::execute(x);
    *x = twenty * (*x);
    return x;
}

Exp::Exp() : MathFunctions(){
    word = "exp";
}

Complex* Exp::execute(Complex* x) const{
    Complex temp = *x;
    x->setMagn(pow(EULER_NUMBER, temp.getReal()));
    x->setAngl(GIO.AngIO.d2r(temp.getImag()));
    return x;
}

Sqrt::Sqrt() : MathFunctions(){
    word = "sqrt";
}

Complex* Sqrt::execute(Complex* x) const{
    *x = x->complexPow(0.5);
    return x;
}

Abs::Abs() : MathFunctions(){
    word = "abs";
}

Complex* Abs::execute(Complex* x) const{
    x->setAbi(sqrt(pow(x->getReal(),2) + pow(x->getImag(),2)), 0);
    return x;
}

Angle::Angle() : MathFunctions(){
    word = "angle";
}

Complex* Angle::execute(Complex * x) const{
    x->setAbi(GIO.AngIO.r2d(x->getAngl()), 0);
    return x;
}

Cis::Cis() : MathFunctions(){
    word = "cis";
}

Complex* Cis::execute(Complex* x) const{
    if(x->getImag() != 0){
        invalid_func_arg err(word);
        throw(err);
    }
    Complex* result = new Complex(0, 0);
    result->setCis(1, GIO.AngIO.d2r(x->getReal())); // note that the angle is stored in radians
    if(x != nullptr){
        delete x;
        x = nullptr;
    }
    return result;
}
