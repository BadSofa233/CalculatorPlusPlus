#ifndef EXPRESSIONTREE_HPP_INCLUDED
#define EXPRESSIONTREE_HPP_INCLUDED

#include "Complex.hpp"

class Expression;

class ExpressionTree{
public:
    ExpressionTree();
    ~ExpressionTree();
    Expression * getRoot() const;
    void setRoot(Expression *);
    Complex * execute();
private:
    Expression * root;
};

#endif // EXPRESSIONTREE_HPP_INCLUDED
