#ifndef Operation_HPP_INCLUDED
#define Operation_HPP_INCLUDED

#include <stack>
#include "Complex.hpp"
#include "ExpressionTree.hpp"

class Expression;

enum TYPE{
    INVALID = 0,
    COMMAND,
    NUMBER,
    IMAG_UNIT,
    FUNCTION,
    OPERATOR,
    OPEN_BRACKET,
    CLOSE_BRACKET
};

class Operation{
public:
    Operation();
    virtual ~Operation();
    virtual Complex * execute(Complex *) const;
    void setWord(const std::string &);
    std::string getWord() const;
    TYPE getType() const;
    unsigned getArgNum() const;
    unsigned char getRankMatch() const;
    virtual void execute(const unsigned&, std::string *);
    virtual void formExpressionTree(ExpressionTree &);
    void setValue(const Complex &);
    Complex getValue() const;
protected:
    Complex value;
    unsigned argNum;
    std::string word;
    unsigned char rankMatch; // stores the rank of the operator or the match of a bracket
    /**
     * Stores the type of this Operation:
     * INVALID, COMMAND, FUNCTION, OPERATOR, OPEN_BR, CLOSE_BR, NUMBER
     */
    TYPE opType;
};

class PreposOp : public Operation{
public:
    virtual void formExpressionTree(ExpressionTree &);
};


class PostposOp : public Operation{
public:
    virtual void formExpressionTree(ExpressionTree &);
};
#endif // Operation_HPP_INCLUDED
