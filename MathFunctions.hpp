#ifndef MATHFUNCTIONS_HPP_INCLUDED
#define MATHFUNCTIONS_HPP_INCLUDED

#include <cmath>
#include "Complex.hpp"
#include "Token.hpp"

class MathFunctions : public Postpos{
public:
    MathFunctions();
    virtual Complex * execute(Complex *) const;
};

class Sin : public MathFunctions{
public:
    Sin();
    Complex * execute(Complex *) const;
};

class Cos : public MathFunctions{
public:
    Cos();
    Complex * execute(Complex *) const;
};

class Tan : public MathFunctions{
public:
    Tan();
    Complex * execute(Complex *) const;
};

class Cot : public MathFunctions{
public:
    Cot();
    Complex * execute(Complex *) const;
};

class Sinh : public MathFunctions{
public:
    Sinh();
    Complex * execute(Complex *) const;
};

class Cosh : public MathFunctions{
public:
    Cosh();
    Complex * execute(Complex *) const;
};

class Tanh : public MathFunctions{
public:
    Tanh();
    Complex * execute(Complex *) const;
};

class Ln : public MathFunctions{
public:
    Ln();
    Complex * execute(Complex *) const;
};

class Asin : public Ln{
public:
    Asin();
    Complex * execute(Complex *) const;
};

class Acos : public Ln{
public:
    Acos();
    Complex * execute(Complex *) const;
};

class Atan : public Ln{
public:
    Atan();
    Complex * execute(Complex *) const;
};

class Acot : public Atan{
public:
    Acot();
    Complex * execute(Complex *) const;
};

class Asinh : public Asin{
public:
    Asinh();
    Complex * execute(Complex *) const;
};

class Acosh : public Ln{
public:
    Acosh();
    Complex * execute(Complex *) const;
};

class Atanh : public Ln{
public:
    Atanh();
    Complex * execute(Complex *) const;
};

class Log : public Ln{
public:
    Log();
    Complex * execute(Complex *) const;
};

class Db : public Log{
public:
    Db();
    Complex * execute(Complex *) const;
};

class Exp : public MathFunctions{
public:
    Exp();
    Complex * execute(Complex *) const;
};

class Sqrt : public MathFunctions{
public:
    Sqrt();
    Complex * execute(Complex *) const;
};

class Abs : public MathFunctions{
public:
    Abs();
    Complex * execute(Complex *) const;
};

class Angle : public MathFunctions{
public:
    Angle();
    Complex * execute(Complex *) const;
};

class Cis : public MathFunctions{
public:
    Cis();
    Complex * execute(Complex *) const;
};

#endif // MATHFUNCTIONS_HPP_INCLUDED
