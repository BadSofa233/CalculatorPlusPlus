#include "ExpressionTree.hpp"
#include "Expression.hpp"
#include <iostream>

ExpressionTree::ExpressionTree() {
        root = new Expression(0, nullptr);
}

Expression * ExpressionTree::getRoot() const {
    return root;
}

void ExpressionTree::setRoot(Expression * r) {
    root = r;
}

Complex ExpressionTree::execute() {
    root->getChild(0)->traverse();
    return root->getChild(0)->getData()->getValue();
}

void ExpressionTree::printTree(Expression * r){
    //std::cout << "stuck in recursion\n";
    TreeNode<Operation> * it = r;
    std::cout << it->getData()->getWord() << '\t';
    if(r == r->getParent()->getLastChild())
        std::cout << '\n';
    if(!(it->getChild(0))) {
        std::cout << '\n';
        return;
    }
    for(unsigned i = 0; it->getChild(i); ++i) {
        printTree((Expression *)it->getChild(i));
    }
    //printTree((Expression *)it->getLastChild());
    std::cout << '\n';
}
