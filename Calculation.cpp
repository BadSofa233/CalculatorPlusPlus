#include <exception>
#include <vector>
#include "common.hpp"
#include "Dictionary.hpp"
#include "MathFunctions.hpp"
#include "Operation.hpp"
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
    Operation * op = nullptr;
    Operation * const multiply = dictionary.searchString("*");
    Operation * const negative = dictionary.searchString("negative");

    std::vector<Operation *> operations;// some experiments

    for(unsigned pos = 0; pos < inputStr.length(); ++pos){
        inputStr[pos] = tolower(inputStr[pos]);

        dictionary.reset();

        DEBUG_PRINT("Fetching pointer for: ");
        for(; pos < inputStr.length() && dictionary.hasNext(inputStr[pos]); ++pos){
            dictionary.gotoNext(inputStr[pos]);
            DEBUG_PRINT_NO_TIMESTAMP("%c", inputStr[pos]);
        }
        DEBUG_PRINT_NO_TIMESTAMP("\n");
        DEBUG_PRINT("Dictionary search finished.\n");
        --pos;

        // if this children of it is not found, reset dictionary cursor
        op = dictionary.getData(); // attempt to get the Operation of this word
        DEBUG_PRINT("Retrieved Operation pointer\n");
        dictionary.reset();
        DEBUG_PRINT("Reset dictionary\n");

        if(!op){ // if wrong word
            DEBUG_PRINT("Word not found, terminating.\n");
            invalid_expression err;
            throw err;
        }

        t = op->getType();
        switch(t){
        case NUMBER:{
            Operation * num = nullptr;
            numberString += op->getWord();
            DEBUG_PRINT("Added current number to number string\n");
            ++pos;
            for(; pos < inputStr.length(); ++pos){
                num = dictionary.searchNextChar(inputStr[pos]);
                if(num && num->getType() == NUMBER){
                    numberString += inputStr[pos];
                }
                else{
                    DEBUG_PRINT("Terminating number fetch\n");
                    --pos;
                    break;
                }
            }
            if(prev == CLOSE_BRACKET || (prev == IMAG_UNIT && GIO.CompNumIO.preOrPost())){
                operations.push_back(multiply);
            }
            operations.push_back(new Number(numberString.c_str()));
            numberString = "";
            break;
        }
        case FUNCTION:
            DEBUG_PRINT("Handling function %s\n", op->getWord());
            if(prev == NUMBER || prev == CLOSE_BRACKET || prev == IMAG_UNIT){
                operations.push_back(multiply);
            }
            operations.push_back(op); //////////////////// experiments //////////////////////
            break;
        case OPERATOR:
            if(inputStr[pos] == '-' &&
                (pos == 0 || prev == OPERATOR || prev == OPEN_BRACKET)){
                operations.push_back(negative);
                DEBUG_PRINT("Negative sign, pushed negative into operations\n");
                //break;
            }
            else operations.push_back(op); //////////////////// experiments //////////////////////
            break;
        case OPEN_BRACKET:
            DEBUG_PRINT("Handling open bracket %s\n", op->getWord()); ///////////////////////debug
            if(prev == NUMBER || prev == CLOSE_BRACKET || prev == IMAG_UNIT){
                operations.push_back(multiply);
            }
            operations.push_back(op); //////////////////// experiments //////////////////////
            break;
        case CLOSE_BRACKET:
            operations.push_back(op); //////////////////// experiments //////////////////////
            break;
        case IMAG_UNIT:
            if(prev == NUMBER || prev == CLOSE_BRACKET){
                if(GIO.CompNumIO.preOrPost()){ // if imaginary unit is set to prefix
                    invalid_expression err;
                    throw err;
                }
                operations.push_back(multiply);
            }
            operations.push_back(op);
            break;
        default:{
            invalid_expression err;
            throw err;
        }
        }
        prev = t; // store the previous type fetched
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
    Operation * ans = dictionary.searchString("ans");
    ans->setValue(*result);
    DEBUG_PRINT("Answer stored\n");
    return result;
}
