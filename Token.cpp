#include "Token.hpp"
#include "TreeNode.hpp"
#include "Expression.hpp"
#include "common.hpp"

Token::Token(){}

Token::~Token(){}

unsigned Token::getArgNum() const{
    return argNum;
}

std::string Token::getWord() const{
    return word;
}

unsigned char Token::getRankMatch() const{
    return rankMatch;
}

TYPE Token::getType() const{
    return type;
}

void Token::execute(const unsigned int&, std::string *){}

Complex* Token::execute(Complex * _) const{
    return nullptr;
}

void Token::setValue(const Complex & z) {
    value = z;
}

Complex Token::getValue() const {
    return value;
}

void Token::formExpressionTree(ExpressionTree & expTree) {}

void Prepos::formExpressionTree(ExpressionTree & expTree) {
    DEBUG_PRINT("Forming expression tree with prepos op %s\n", word);
    // note that these functions has preposition arguments
    // so they must replace a child
    TreeNode<Token> * oldParent = expTree.getRoot();
    TreeNode<Token> * it = oldParent->getChild(0);
    for(; it != nullptr; it = it->getLastChild()) {
        if(getRankMatch() <= it->getData()->getRankMatch()) { // this becomes new parent of it
            DEBUG_PRINT("The node to be swapped: %s\n", it->getData()->getWord());
            Expression * newParent = new Expression(it->getKey(), this);
            newParent->addChild((Expression *)oldParent->replaceChild(it->getKey(), newParent));
            it->setKey(0);
            return;
        }
        oldParent = it;
    }
    // here means oldParent has no child
    throw invalid_expression();
}

void Postpos::formExpressionTree(ExpressionTree & expTree) {
    DEBUG_PRINT("Forming expression tree with postpos op %s rank %d\n", word, rankMatch);
    TreeNode<Token> * oldParent = expTree.getRoot();
    TreeNode<Token> * it = oldParent->getChild(0);
    for(; it != nullptr; it = it->getLastChild()) {
        DEBUG_PRINT("it op: %s, rank: %d\n", it->getData()->getWord(), it->getData()->getRankMatch());
        // this is for functions with postposition arguments
        if(it->getData()->getArgNum() && it->hasChildren() && !it->getChild(it->getData()->getArgNum() - 1)) {
            it->addChild(new Expression(it->getLastChild()->getKey() + 1, this));
            DEBUG_PRINT("Added op %s into expression tree\n", word);
            return;
        }
        oldParent = it;
    }
    // here means oldParent has no child yet so add this as oldParent's child
    oldParent->addChild(new Expression(0, this));
    DEBUG_PRINT("Added first child op %s into expression tree\n", word);
}
