#include "Expression.hpp"
#include "ExpressionTree.hpp"
//#include "TreeNode.hpp"
#include "Bracket.hpp"
#include "common.hpp"

Bracket::Bracket() : Operation(){}

OpenBracket::OpenBracket() : Bracket(){
    argNum = 1;
    opType = OPEN_BRACKET;
    rankMatch = 5;
}

Complex * OpenBracket::execute(Complex * x) const{
    DEBUG_PRINT("in open bracket execute\n");
    Complex * ret = new Complex(x->getReal(), x->getImag());
    delete x;
    return ret;
}

void OpenBracket::formExpressionTree(ExpressionTree & expTree) {
    // set the new root of expression tree
//    TreeNode<Operation> * it = expTree.getRoot();
//    for(; it->hasChildren(); it = it->getLastChild());
//    Expression * openBr = new Expression(0, this);
//    it->addChild(openBr);
//    expTree.setRoot(openBr);
//    DEBUG_PRINT("Root is now %s\n", expTree.getRoot()->getData()->getWord());
    DEBUG_PRINT("Forming expression tree with open bracket %s rank %d\n", word, rankMatch);
    TreeNode<Operation> * oldParent = expTree.getRoot();
    TreeNode<Operation> * it = oldParent->getChild(0);
    Expression * openBr = new Expression(0, this);
    for(; it != nullptr; it = it->getLastChild()) {
        DEBUG_PRINT("it op: %s, rank: %d\n", it->getData()->getWord(), it->getData()->getRankMatch());
        // this is for functions with postposition arguments
        if(getRankMatch() <= it->getData()->getRankMatch()) {
            openBr->setKey(it->getKey() + 1);

            break;
        }
        oldParent = it;
    }
    // here means oldParent has no child yet so add this as oldParent's child
    DEBUG_PRINT("Added child op %s into expression tree\n", word);
    oldParent->addChild(openBr);
    expTree.setRoot(openBr);
    DEBUG_PRINT("Root is now %s\n", expTree.getRoot()->getData()->getWord());
}

CloseBracket::CloseBracket() : Bracket(){
    argNum = 0;
    opType = CLOSE_BRACKET;
}

void CloseBracket::formExpressionTree(ExpressionTree & expTree) {
    Expression * root = expTree.getRoot();
    if(!root->getData())
        DEBUG_PRINT("Root has not been set\n");
    DEBUG_PRINT("close bracket %s, root is %s\n", word, root->getData()->getWord());
    if((root->getData()->getWord())[0] != rankMatch) {
        invalid_bracket err(word[0]);
        throw(err);
    }
    // move root to the previous open bracket or the original root
    TreeNode<Operation> * it = root->getParent();
    DEBUG_PRINT("root parent is not null\n");
    for(; (it->getData()!= nullptr) && (it->getData()->getType() != OPEN_BRACKET); it = it->getParent()){
        DEBUG_PRINT("it: %s\n", it->getData()->getWord());
    }
    DEBUG_PRINT("found new root\n");
    expTree.setRoot((Expression *)it);
    DEBUG_PRINT("Root reset\n");
}

OpenRound::OpenRound() : OpenBracket(){
    word = "(";
}

CloseRound::CloseRound() : CloseBracket(){
    word = ")";
    rankMatch = '(';
}

OpenSquare::OpenSquare() : OpenBracket(){
    word = "[";
}

CloseSquare::CloseSquare() : CloseBracket(){
    word = "]";
    rankMatch = '[';
}

OpenCurly::OpenCurly() : OpenBracket(){
    word = "{";
}

CloseCurly::CloseCurly() : CloseBracket(){
    word = "}";
    rankMatch = '{';
}
