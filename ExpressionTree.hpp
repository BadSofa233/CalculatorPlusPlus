#ifndef EXPRESSIONTREE_HPP_INCLUDED
#define EXPRESSIONTREE_HPP_INCLUDED

#include "Complex.hpp"

class Expression;

class ExpressionTree{
public:
    ExpressionTree();
    Expression * getRoot() const;
    void setRoot(Expression *);
    Complex execute();

    void printTree(Expression *);
private:
    Expression * root;
};

#endif // EXPRESSIONTREE_HPP_INCLUDED
