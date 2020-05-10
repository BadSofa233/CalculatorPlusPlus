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

//    void addChild(TreeNode<Operation> * child) override{
//        TreeNode * it = children, * prev = children;
//        for(it = children; (it != nullptr) && ((int)it->getKey() <= (int)child->getKey()); it = it->sibling){
//        // move it to the position where the char to be added follows an ascending order
//            if(it->getKey() == child->getKey()){
//                if(it == children){
//                    children = child;
//                    return;
//                }
//                prev->sibling = child;
//                child->sibling = it->sibling;
//                return;
//            }
//            prev = it;
//        }
//        if(it == children){ // if it is at the head
//            children = child;
//            child->setParent(this);
//            children->sibling = it;
//        }
//        else{ // if it is in the middle
//            prev->sibling = child;
//            child->setParent(this);
//            prev = prev->sibling;
//            prev->sibling = it;
//        }
//
//    }

    void traverse() override {
        DEBUG_PRINT("Traverse Expression with op %s and argNum %d\n", getData()->getWord(), getData()->getArgNum());
        Complex * argList = nullptr;
        Operation * op = getData();
        unsigned argNum = op->getArgNum();
        if(argNum > 1) {
            argList = new Complex[argNum];
            for(unsigned i = 0; i < argNum; ++i){
                getChild(i)->traverse();
                argList[i] = getChild(i)->getData()->getValue();
            }
        }
        else if(argNum) {
            getChild(0)->traverse();
            argList = new Complex;
            *argList = getChild(0)->getData()->getValue();
        }
        DEBUG_PRINT("Fetch arg complete\n");
        op->setValue(*(op->execute(argList)));
        DEBUG_PRINT("execute result: %z\n", op->getValue());
    }
};

#endif // EXPRESSION_H_INCLUDED
