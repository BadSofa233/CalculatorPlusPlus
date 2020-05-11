#include "ExpressionTree.hpp"
#include "Expression.hpp"

ExpressionTree::ExpressionTree() {
    root = new Expression(0, nullptr);
}

Expression * ExpressionTree::getRoot() const {
    return root;
}

void ExpressionTree::setRoot(Expression * r) {
    root = r;
}

Complex * ExpressionTree::execute() {
    root->getChild(0)->traverse();
    return new Complex(root->getChild(0)->getData()->getValue());
    // this pointer will be taken by result in Calculation.cpp
}

ExpressionTree::~ExpressionTree() {
    delete root;
    // destruction of TreeNode is recursive;
}
