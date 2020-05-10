#ifndef BRACKET_HPP_INCLUDED
#define BRACKET_HPP_INCLUDED

#include "Operation.hpp"

/// Brackets ///
class Bracket : public Operation{
public:
    Bracket();
};

class OpenBracket : public Bracket{
public:
    OpenBracket();
    void formExpressionTree(ExpressionTree &);
    Complex * execute(Complex *) const;
};

class CloseBracket : public Bracket{
public:
    CloseBracket();
    void formExpressionTree(ExpressionTree &);
};

class OpenRound : public OpenBracket{ // (
public:
    OpenRound();
};

class OpenSquare : public OpenBracket{ // [
public:
    OpenSquare();
};

class OpenCurly : public OpenBracket{ // {
public:
    OpenCurly();
};

class CloseRound : public CloseBracket{ // )
public:
    CloseRound();
};

class CloseSquare : public CloseBracket{ // ]
public:
    CloseSquare();
};

class CloseCurly : public CloseBracket{ // }
public:
    CloseCurly();
};

#endif // BRACKET_HPP_INCLUDED
