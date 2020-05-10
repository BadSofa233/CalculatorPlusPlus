#include "Operation.hpp"
#include "TreeNode.hpp"
#include "Expression.hpp"

Operation::Operation(){}

Operation::~Operation(){}

unsigned Operation::getArgNum() const{
    return argNum;
}

std::string Operation::getWord() const{
    return word;
}

unsigned char Operation::getRankMatch() const{
    return rankMatch;
}

TYPE Operation::getType() const{
    return opType;
}

void Operation::execute(const unsigned int&, std::string *){}

Complex* Operation::execute(Complex * _) const{
    return nullptr;
}

void Operation::setValue(const Complex & z) {
    value = z;
}

Complex Operation::getValue() const {
    return value;
}

void Operation::formExpressionTree(ExpressionTree & expTree) {}

void PreposOp::formExpressionTree(ExpressionTree & expTree) {
    DEBUG_PRINT("Forming expression tree with prepos op %s\n", word);
    // note that these functions has preposition arguments
    // so they must replace a child
    TreeNode<Operation> * oldParent = expTree.getRoot();
    TreeNode<Operation> * it = oldParent->getChild(0);
    for(; it != nullptr; it = it->getLastChild()) {
        if(getRankMatch() < it->getData()->getRankMatch()) { // this becomes new parent of it
            DEBUG_PRINT("The node to be swapped: %s\n", it->getData()->getWord());
            Expression * newParent = new Expression(it->getKey(), this);
            newParent->addChild((Expression *)oldParent->replaceChild(it->getKey(), newParent));
            it->setKey(0);
            return;
        }
        oldParent = it;
    }
    // here means oldParent has no child
    std::cout << "Error forming expression tree at PreposFunction\n";
}

void PostposOp::formExpressionTree(ExpressionTree & expTree) {
    DEBUG_PRINT("Forming expression tree with postpos op %s rank %d\n", word, rankMatch);
    TreeNode<Operation> * oldParent = expTree.getRoot();
    TreeNode<Operation> * it = oldParent->getChild(0);
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
    DEBUG_PRINT("Added first child op %s into expression tree\n", word);
    oldParent->addChild(new Expression(0, this));
}
