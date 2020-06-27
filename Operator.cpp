#include "Operator.hpp"
#include "common.hpp"
#include "TreeNode.hpp"
#include "Expression.hpp"

Operator::Operator() : Prepos(){
    type = OPERATOR;
    argNum = 2;
}

Operator::~Operator(){}

Complex * Operator::execute(Complex * argList) const{
    return nullptr;
}

Assignment::Assignment() : Operator(){
    word = "=";
    rankMatch = 0;
}

Complex * Assignment::execute(Complex * x) const {
    return x;
}

void Assignment::formExpressionTree(ExpressionTree & expTree) {
    DEBUG_PRINT("Forming expression tree with %s\n", word);
    // note that these functions has preposition arguments
    // so they must replace a child
    TreeNode<Token> * oldParent = expTree.getRoot();
    TreeNode<Token> * it = oldParent->getChild(0);
    for(; it != nullptr; it = it->getLastChild()) {
        if(getRankMatch() < it->getData()->getRankMatch()) { // this becomes new parent of it
            DEBUG_PRINT("The node to be swapped: %s\n", it->getData()->getWord());
            AssignmentExpression * newParent = new AssignmentExpression(it->getKey(), this);
            newParent->addChild((Expression *)oldParent->replaceChild(it->getKey(), newParent));
            it->setKey(0);
            return;
        }
        oldParent = it;
    }
    // here means oldParent has no child
    throw invalid_expression();
}

Plus::Plus() : Operator(){
    word = "+";
    rankMatch = 1;
}

Complex * Plus::execute(Complex * argList) const{
    Complex * result = new Complex(argList[0] + argList[1]);
    delete[] argList;
    return result;
}

Minus::Minus() : Operator(){
    word = "-";
    rankMatch = 1;
}

Complex * Minus::execute(Complex * argList) const{
    Complex * result = new Complex(argList[0] - argList[1]);
    delete[] argList;
    return result;
}

Multiply::Multiply() : Operator(){
    word = "*";
    rankMatch = 2;
}

Complex * Multiply::execute(Complex * argList) const{
    Complex * result = new Complex(argList[0] * argList[1]);
    delete[] argList;
    return result;
}

Divide::Divide() : Operator(){
    word = "/";
    rankMatch = 2;
}

Complex * Divide::execute(Complex * argList) const{
    Complex * result = new Complex(argList[0] / argList[1]);
    delete[] argList;
    return result;
}

Power::Power() : Operator(){
    word = "^";
    rankMatch = 3;
}

Complex * Power::execute(Complex * argList) const{
    Complex * result = new Complex(argList[0].complexPow(argList[1]));
    delete[] argList;
    return result;
}

Negative::Negative() : Postpos(){
    argNum = 1;
    word = "negative";
    rankMatch = 4;
}

Complex * Negative::execute(Complex * x) const{
    Complex * result = new Complex(-1 * x->getReal(), -1 * x->getImag());
    delete x;
    return result;
}

RealOnly::RealOnly() : Operator(){}

void RealOnly::checkReal(Complex * const x) const{
    for(unsigned i = 0; i < argNum; ++i)
        if(x->getImag()){
            invalid_func_arg err(word);
            throw err;
        }
}

#ifdef CALCULATOR_VERSION_2_0

And::And() : RealOnly(){
    word = "and";
    rankMatch = 4;
    DEBUG_PRINT((word + "\n").c_str());
}

Complex * And::execute(Complex * argList) const{
    RealOnly::checkReal(argList);
    unsigned temp = (int)argList[0].getReal() & (int)argList[1].getReal();
    unsigned mask = 0b1 << globalFormat.WordLength.length();
    if(mask & temp){ // detect if the highest bit is 1, the original number is negative
        temp |= ~((unsigned)pow(2,globalFormat.WordLength.length()) - 1);
    }
    Complex * result = new Complex((double)temp, 0);
    delete[] argList;
    return result;
}

Or::Or() : RealOnly(){
    word = "or";
    rankMatch = 4;
    DEBUG_PRINT((word + "\n").c_str());
}

Complex * Or::execute(Complex * argList) const{
    RealOnly::checkReal(argList);
    Complex * result = new Complex((int)argList[0].getReal() | (int)argList[1].getReal(), 0);
    delete[] argList;
    return result;
}

Not::Not() : Postpos(){
    word = "not";
    argNum = 1;
    rankMatch = 4;
    DEBUG_PRINT((word + "\n").c_str());
}

Complex * Not::execute(Complex * x) const{
    //RealOnly::checkReal(x);
    long temp = ~((long)x->getReal());
    unsigned long mask = 0 & (0b1 << globalFormat.WordLength.length());
    if(mask & temp){ // detect if the highest bit is 1, the original number is negative
        temp |= ~((long)pow(2, globalFormat.WordLength.length()) - 1);
    }
    x->setReal((double)temp);
    return x;
}

Xor::Xor() : RealOnly(){
    word = "xor";
    rankMatch = 4;
    DEBUG_PRINT((word + "\n").c_str());
}

Complex * Xor::execute(Complex * argList) const{
    RealOnly::checkReal(argList);
    Complex * result = new Complex((int)argList[0].getReal() ^ (int)argList[1].getReal(), 0);
    delete[] argList;
    return result;
}

Nor::Nor() : RealOnly(){
    word = "nor";
    rankMatch = 4;
    DEBUG_PRINT((word + "\n").c_str());
}

Complex * Nor::execute(Complex * argList) const{
    RealOnly::checkReal(argList);
    Complex* result = new Complex(~((int)argList[0].getReal() | (int)argList[1].getReal()), 0);
    delete[] argList;
    return result;
}

Nand::Nand() : RealOnly(){
    word = "nand";
    rankMatch = 4;
    DEBUG_PRINT((word + "\n").c_str());
}

Complex * Nand::execute(Complex * argList) const{
    RealOnly::checkReal(argList);
    Complex* result = new Complex(~((int)argList[0].getReal() & (int)argList[1].getReal()), 0);
    delete[] argList;
    return result;
}

AndSymbolic::AndSymbolic() : And(){
    word = "&";
}

OrSymbolic::OrSymbolic() : Or(){
    word = "|";
}

NotSymbolic::NotSymbolic() : Not(){
    word = "~";
}

XorSymbolic::XorSymbolic() : Xor(){
    word = "^^";
}

#endif // CALCULATOR_VERSION_2_0

Parallel::Parallel() : Operator(){
    word = "||";
    rankMatch = 2; // same as * and /
}

Complex * Parallel::execute(Complex * argList) const{
    Complex * result = new Complex();
    *result = (argList[0] * argList[1]) / (argList[0] + argList[1]);
    delete[] argList;
    return result;
}
