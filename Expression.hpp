#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include "TreeNode.hpp"
#include "Complex.hpp"
#include "Token.hpp"

// An Expression object is a tree of Tokens
// Key of node is the position of argument

class Expression : public TreeNode<Token> {
public:
    Expression(const char & c, Token * o) : TreeNode(c, o) {}

    void traverse() override {
        DEBUG_PRINT("Traverse Expression with op %s and argNum %d\n", getData()->getWord(), getData()->getArgNum());
        Complex * argList = nullptr;
        Token * op = getData();
        unsigned argNum = op->getArgNum();
        if(argNum > 1) {
            argList = new Complex[argNum];
            // argList will be taken by op->execute() and be destroyed in there
            for(unsigned i = 0; i < argNum; ++i){
                getChild(i)->traverse();
                argList[i] = getChild(i)->getData()->getValue();
            }
        }
        else if(argNum) {
            getChild(0)->traverse();
            argList = new Complex;
            // op->execute() might not free argList it there only one argument
            // but anyway it is in this process the pointer
            // returned by op->execute() should be freed
            *argList = getChild(0)->getData()->getValue();
        }

        DEBUG_PRINT("Fetch arg complete\n");
        Complex * result = op->execute(argList);
        op->setValue(*result);
        DEBUG_PRINT("execute result: %z\n", op->getValue());
        delete result;
    }

    ~Expression() {
        DEBUG_PRINT("Expression destruction\n");
        setData(nullptr);
    }
};

#endif // EXPRESSION_H_INCLUDED
