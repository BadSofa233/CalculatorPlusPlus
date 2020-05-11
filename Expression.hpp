#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include "TreeNode.hpp"
#include "Complex.hpp"
#include "Operation.hpp"

// An Expression object is a tree of Operations
// Data in node is the position of argument

class Expression : public TreeNode<Operation> {
public:
    Expression(const char & c, Operation * o) : TreeNode(c, o) {}

    void traverse() override {
        DEBUG_PRINT("Traverse Expression with op %s and argNum %d\n", getData()->getWord(), getData()->getArgNum());
        Complex * argList = nullptr;
        Operation * op = getData();
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
            // but anyway it is this function's responsibility
            // to free the pointer returned by op->execute().
            *argList = getChild(0)->getData()->getValue();
        }

        DEBUG_PRINT("Fetch arg complete\n");
        Complex * result = op->execute(argList);
        op->setValue(*result);
        DEBUG_PRINT("execute result: %z\n", op->getValue());
        delete result;
    }
};

#endif // EXPRESSION_H_INCLUDED
