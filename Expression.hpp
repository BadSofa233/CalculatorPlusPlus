#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include "TreeNode.hpp"
#include "Complex.hpp"
#include "Token.hpp"
#include "common.hpp"

// An Expression object is a tree containing tokens as data
// Key of node is the position of argument

class Expression : public TreeNode<Token> {
public:
    Expression(const char & c, Token * o) : TreeNode(c, o) {}

    void traverse() override {
        DEBUG_PRINT("Traverse Expression with token %s and argNum %d\n", getData()->getWord(), getData()->getArgNum());
        Complex * argList = nullptr;
        Token * token = getData();
        unsigned argNum = token->getArgNum();
        // check expression tree for syntax errors
        if(argNum && (!hasChildren() || (unsigned)getLastChild()->getKey() != argNum - 1))
            throw invalid_expression();
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
        // argList will be taken care of in token->execute()
        // but token->execute creates new pointer with return value
        // so it is in this process the pointer
        // returned by token->execute() should be freed
        DEBUG_PRINT("Fetch arg complete\n");
        Complex * result = token->execute(argList);
        token->setValue(*result);
        DEBUG_PRINT("execute result: %z\n", token->getValue());
        delete result;
    }

    virtual ~Expression() {
        setData(nullptr);
    }
};

class AssignmentExpression : public Expression {
public:
    AssignmentExpression(const char & c, Token * o) : Expression(c, o) {}

    void traverse() override {
        //Token * token = getData();
        if(getChild(0)->getData()->getType() != VARIABLE ||
           (unsigned)getLastChild()->getKey() != getData()->getArgNum() - 1)
            throw invalid_expression();
        if(getChild(0))
        getChild(1)->traverse();
        Complex val = getChild(1)->getData()->getValue();
        getChild(0)->getData()->setValue(val);
        getData()->setValue(val);
    }
};

#endif // EXPRESSION_H_INCLUDED
