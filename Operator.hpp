#ifndef OPERATOR_HPP_INCLUDED
#define OPERATOR_HPP_INCLUDED

#include "Token.hpp"
#include "ExpressionTree.hpp"

class Operator : public Prepos{
public:
    Operator();
    virtual ~Operator();
    virtual Complex * execute(Complex *) const;
};

/// Assignment operator ///
class Assignment : public Operator{ // =
public:
    Assignment();
    Complex * execute(Complex *) const;
    void formExpressionTree(ExpressionTree &);
};

/// Arithmetic operators ///
class Plus : public Operator{ // +
public:
    Plus();
    Complex * execute(Complex *) const;
};

class Minus : public Operator{ // -
public:
    Minus();
    Complex * execute(Complex *) const;
};

class Multiply : public Operator{ // *
public:
    Multiply();
    Complex * execute(Complex *) const;
};

class Divide : public Operator{ // /
public:
    Divide();
    Complex * execute(Complex *) const;
};

class Power : public Operator{ // ^
public:
    Power();
    Complex * execute(Complex *) const;
};

class Negative : public Postpos{
public:
    Negative();
    Complex * execute(Complex *) const;
};

class RealOnly : public Operator{ // Abstract Operators that only operates real numbers
public:
    RealOnly();
    void checkReal(Complex * const) const;
};

#ifdef CALCULATOR_VERSION_2_0
// Logic operators, literal //
class And : public RealOnly{ // AND
public:
    And();
    Complex * execute(Complex *) const;
};

class Or : public RealOnly{ // OR
public:
    Or();
    Complex * execute(Complex *) const;
};

class Not : public Postpos{ // NOT
public:
    Not();
    Complex * execute(Complex *) const;
};

class Xor : public RealOnly{ // XOR
public:
    Xor();
    Complex * execute(Complex *) const;
};

class Nor : public RealOnly{ // NOR
public:
    Nor();
    Complex * execute(Complex *) const;
};

class Nand : public RealOnly{ // NAND
public:
    Nand();
    Complex * execute(Complex *) const;
};

// Logic operators, symbolic //
class AndSymbolic : public And{ // &
public:
    AndSymbolic();
};

class OrSymbolic : public Or{ // |
public:
    OrSymbolic();
};

class NotSymbolic : public Not{ // ~
public:
    NotSymbolic();
};

class XorSymbolic : public Xor{ // ^^
public:
    XorSymbolic();
};
#endif // CALCULATOR_VERSION_2_0

// Electrical operators //
class Parallel : public Operator{ // Parallel impedance symbol ||
public:
    Parallel();
    Complex * execute(Complex *) const;
};

#endif // OPERATOR_HPP_INCLUDED
