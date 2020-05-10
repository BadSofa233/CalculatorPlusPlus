#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <string>
#include "MathFunctions.hpp"
#include "Operation.hpp"

class Number : public MathFunctions{
public:
    Number();
    Number(const int&);
    Number(const char *);
    //Numebr(const std::string &);
    Number(const char *, const Complex&&);
    Number(const char&, const Complex&&);
    Complex * execute(Complex *) const;
};

class Constant : public Number{
public:
    Constant(const char *, const Complex&&);
    Constant(const char&, const Complex&&);
};

class Variable : public Number{
public:
    Variable(const char *);
    Variable(const char *, const Complex&&);
    Variable(const char& name, const Complex&& x);
};

class Ans : public Variable{
public:
    Ans();
};

class ImaginaryUnit : public Constant{
public:
    ImaginaryUnit(const char &);
};

class Pi : public Constant{
public:
    Pi();
};

class E : public Constant{
public:
    E();
};

#endif // NUMBER_HPP_INCLUDED
