#include <exception>
#include <vector>
#include "common.hpp"
#include "Dictionary.hpp"
#include "MathFunctions.hpp"
#include "Token.hpp"
#include "Operator.hpp"
#include "Number.hpp"
#include "Dictionary.hpp"
#include "Expression.hpp"

Complex * calcString(std::string& inputStr){
    if(inputStr.length() == 0){
        Complex * zeroPtr = new Complex(0, 0);
        return zeroPtr;
        // this pointer will be taken by Calculate::execute() and will be deleted there
    }
    DEBUG_PRINT("Calculating string\n");
    std::string numberString = "";
    TYPE t = INVALID, prev = INVALID;
    Token * op = nullptr;
    Token * const multiply = dictionary.searchString("*");
    Token * const negative = dictionary.searchString("negative");

    std::vector<Token *> operations;
    // a copy of tokens that are generated in this process but not fetched from dictionary
    std::vector<Token *> temps;

    for(unsigned pos = 0; pos < inputStr.length(); ++pos){
        inputStr[pos] = tolower(inputStr[pos]);
        if((inputStr[pos] >= '0' && inputStr[pos] <= '9') || inputStr[pos] == '.') {
            numberString += inputStr[pos];
            continue;
        }
        else if(numberString != "") {
            op = new Number(numberString.c_str());
            temps.push_back(op);
            numberString = "";
            --pos;
        }
        else {
            for(; pos < inputStr.length() && dictionary.hasNext(inputStr[pos]); ++pos){
                dictionary.gotoNext(inputStr[pos]);
            }
            DEBUG_PRINT("Dictionary search finished\n");
            --pos;
            // if this children of it is not found, reset dictionary cursor
            op = dictionary.getData(); // attempt to get the Token of this word
            dictionary.reset();
            if(!op){ // if wrong word
                DEBUG_PRINT("Word not found\n");
                invalid_expression err;
                throw err;
            }
            DEBUG_PRINT("Retrieved pointer for %s\n", op->getWord());
        }

        t = op->getType();
        switch(t){
        case NUMBER:
        case FUNCTION:
        case OPEN_BRACKET:
            if(prev == CLOSE_BRACKET || prev == NUMBER){
                operations.push_back(multiply);
            }
            operations.push_back(op);
            break;

        case OPERATOR:
            if(inputStr[pos] == '-' &&
                (pos == 0 || prev == OPERATOR || prev == OPEN_BRACKET)){
                operations.push_back(negative);
                DEBUG_PRINT("Negative sign, pushed negative into operations\n");
            }
            else operations.push_back(op);
            break;

        case CLOSE_BRACKET:
            operations.push_back(op);
            break;

        default:{
            invalid_expression err;
            throw err;
        }
        }
        prev = t; // store the previous type fetched
    }
    if(numberString != "") {
        op = new Number(numberString.c_str());
        if(prev == CLOSE_BRACKET || prev == NUMBER){
            operations.push_back(multiply);
        }
        operations.push_back(op);
        temps.push_back(op);
        numberString = "";
    }
    ExpressionTree expressionTree;
    for(unsigned i = 0; i < operations.size(); ++i) {
        DEBUG_PRINT("%s\n", operations[i]->getWord());
        operations[i]->formExpressionTree(expressionTree);
        if(expressionTree.getRoot()->getData())
            DEBUG_PRINT("Root is %s\n", expressionTree.getRoot()->getData()->getWord());
    }
    DEBUG_PRINT("top of expression tree: %s\n", expressionTree.getRoot()->getChild(0)->getData()->getWord());
    Complex * result = expressionTree.execute();
    Token * ans = dictionary.searchString("ans");
    ans->setValue(*result);
    DEBUG_PRINT("Answer stored\n");
    for(unsigned i = 0; i < temps.size(); ++i) {
        delete temps[i];
    }
    return result;
}
