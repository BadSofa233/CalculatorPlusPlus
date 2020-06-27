#include <exception>
#include <vector>
#include "common.hpp"
#include "TokenDictionary.hpp"
#include "MathFunctions.hpp"
#include "Token.hpp"
#include "Operator.hpp"
#include "Number.hpp"
#include "TokenDictionary.hpp"
#include "Expression.hpp"
#include "Tokenizer.hpp"

Complex * calcString(std::string & inputStr) {
    if(inputStr.length() == 0){
        Complex * zeroPtr = new Complex(0, 0);
        return zeroPtr;
        // this pointer will be taken by Calculate::execute() and will be deleted there
    }
    DEBUG_PRINT("Tokenizing string\n");
    Tokenizer tokenizer;
    std::vector<Token *> * tokens = tokenizer.tokenize(inputStr);
    ExpressionTree expressionTree;
    for(unsigned i = 0; i < tokens->size(); ++i) {
        DEBUG_PRINT("%s\n", (*tokens)[i]->getWord());
        (*tokens)[i]->formExpressionTree(expressionTree);
        if(expressionTree.getRoot()->getData())
            DEBUG_PRINT("Root is %s\n", expressionTree.getRoot()->getData()->getWord());
    }
    DEBUG_PRINT("top of expression tree: %s\n", expressionTree.getRoot()->getChild(0)->getData()->getWord());
    Complex * result = expressionTree.execute();
    Token * ans = tokenDictionary.searchString("ans");
    ans->setValue(*result);
    DEBUG_PRINT("Answer stored\n");
    return result;
}
