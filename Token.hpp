#ifndef TOKEN_HPP_INCLUDED
#define TOKEN_HPP_INCLUDED

#include "Complex.hpp"
#include "ExpressionTree.hpp"

class Expression;

enum TYPE{
    INVALID = 0,
    COMMAND,
    NUMBER,
    VARIABLE,
    FUNCTION,
    OPERATOR,
    OPEN_BRACKET,
    CLOSE_BRACKET
};

class Token{
public:
    Token();
    virtual ~Token();
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
    TYPE type;
};

class Prepos : public Token{
public:
    virtual void formExpressionTree(ExpressionTree &);
};

class Postpos : public Token{
public:
    virtual void formExpressionTree(ExpressionTree &);
};

#endif // TOKEN_HPP_INCLUDED
