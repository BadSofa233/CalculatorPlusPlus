#include <exception>
#include <vector>
#include "Calculation.hpp"
#include "common.hpp"
#include "Dictionary.hpp"
#include "MathFunctions.hpp"
#include "Operation.hpp"
#include "Operator.hpp"
#include "Number.hpp"
#include "Dictionary.hpp"
#include "Expression.hpp"

#define OPERATOR_RANK_MAX 6

Complex * grabArgs(std::stack<Complex*>& numSt, unsigned argNum){
    DEBUG_PRINT("Fetching arguments for the current operator: ");
    Complex * argList = new Complex[argNum];
    if(numSt.size() < argNum){
        std::invalid_argument err("Invalid argument(s).");
        throw(err);
    }
    for(unsigned i = 0; i < argNum; ++i){
        DEBUG_PRINT_NO_TIMESTAMP("arg[%d] = %z", i, *(numSt.top())); /////////////////////debug
        argList[i] = *(numSt.top()); // argList[0] = y, argList[1] = x
        delete numSt.top();
        numSt.pop();
        DEBUG_PRINT_NO_TIMESTAMP("\t"); /////////////////////debug
    }
    DEBUG_PRINT_NO_TIMESTAMP("\n");
    return argList;
}

Complex * convertAndSet(std::string& input){
    Complex * result = new Complex(0,0);
    if(input == "-")
        result->setReal(-1);
    else
        result->setReal(atof(input.c_str()));
    return result;
}

void calcStacks(std::stack<Complex *>& numSt,
                std::stack<Operation *>& opSt){
    DEBUG_PRINT("Calculating current number stack\n"); ///////////////////////debug
    DEBUG_PRINT("Current operator is %s\n", opSt.top()->getWord()); //////////////////////////debug
    Operation * op = opSt.top();
    opSt.pop();
    Complex * result = op->execute(grabArgs(numSt, op->getArgNum()));

    if(result != nullptr){
        numSt.push(result);
        DEBUG_PRINT("Pushing \'%z\' to number stack\n", (*numSt.top())); ///////////////////////debug
    }
}

bool calcOrPush(std::stack<Operation *>& opSt,
                std::stack<linkedStackElement<Operation *>>& brSt,
                Operation * op){
    if(opSt.size() == 0) // if there's no Operation left, push
        return false;
    if(op != nullptr && brSt.size() != 0)                           // if there are brackets in the expression and a valid Operation
        return (opSt.top()->getRankMatch() >= op->getRankMatch() && // and if calculation process hasn't reached the bottom of the bracket
                opSt.size() > brSt.top().pos);                     // and this current operator is of lower rank, calculate
    if(brSt.size() == 0) // if there are no brackets
        return opSt.top()->getRankMatch() >= op->getRankMatch(); // and if this current operator is of lower rank, calculate
    if(op == nullptr)
        return opSt.size() > brSt.top().pos;
    return false;
}

Complex * calcString(std::string& inputStr){
    if(inputStr.length() == 0){
        Complex * zeroPtr = new Complex(0, 0);
        return zeroPtr;
    }
    DEBUG_PRINT("Calculating string\n"); //////////////////////////debug
    std::stack<Complex *> numberSt;
    std::stack<Operation *> OperationSt;
    std::stack<linkedStackElement<Operation *>> bracketSt;
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

        // if this children of it is not fount, reset it to root
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

#if DEBUG_MODE
        numberSt.size() == 0 ?
            DEBUG_PRINT("numberSt.size() == 0\n") :
            DEBUG_PRINT("numberSt.size() == %d, numberSt.top() == %z\n", numberSt.size(), (*numberSt.top()));
        OperationSt.size() == 0 ?
            DEBUG_PRINT("OperationSt.size() == 0\n") :
            DEBUG_PRINT("OperationSt.size() == %d, OperationSt.top() == %s\n", OperationSt.size(), OperationSt.top()->getWord());
        bracketSt.size() == 0 ?
            DEBUG_PRINT("bracketSt.size() == 0\n") :
            DEBUG_PRINT("bracketSt.size() == %d, bracketSt.top().elem == %s, bracketSt.top().pos == %d\n", bracketSt.size(), bracketSt.top().elem->getWord(), bracketSt.top().pos);
#endif // DEBUG_MODE

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
                    //DEBUG_PRINT_NO_TIMESTAMP("%c", inputStr[pos]);
                }
                else{
                    DEBUG_PRINT("Terminating number fetch\n");
                    --pos;
                    break;
                }
            }
            DEBUG_PRINT("Number in string: %s and converted to: ", numberString);
            operations.push_back(new Number(numberString.c_str())); //////////////////// experiments //////////////////////
            Complex * currentNumber = convertAndSet(numberString);
            numberString = "";
            DEBUG_PRINT_NO_TIMESTAMP("%z\n", *currentNumber);
            numberSt.push(currentNumber);
            DEBUG_PRINT("Pushed %z into number stack\n", *currentNumber);
            if(prev == CLOSE_BRACKET || (prev == IMAG_UNIT && GIO.CompNumIO.preOrPost())){
                while(calcOrPush(OperationSt, bracketSt, op))
                    calcStacks(numberSt, OperationSt);
                OperationSt.push(multiply); // if an operator is not specified, * by default
                DEBUG_PRINT("Pushed additional * into opSt.\n"); ///////////////////////debug
            }
            break;
        }
        case FUNCTION:
            DEBUG_PRINT("Processing function %s\n", op->getWord());
            operations.push_back(op); //////////////////// experiments //////////////////////
            if(prev == NUMBER || prev == CLOSE_BRACKET || prev == IMAG_UNIT){
                while(calcOrPush(OperationSt, bracketSt, op))
                    calcStacks(numberSt, OperationSt);
                OperationSt.push(multiply); // if an operator is not specified, * by default
                DEBUG_PRINT("Pushed additional * into opSt.\n"); ///////////////////////debug
            }

            while(calcOrPush(OperationSt, bracketSt, op))
                calcStacks(numberSt, OperationSt);

            OperationSt.push(op);
            DEBUG_PRINT("Pushed %s into Operation stack\n", op->getWord());
            break;
        case OPERATOR:
            if(inputStr[pos] == '-' &&
                (pos == 0 || prev == OPERATOR || prev == OPEN_BRACKET)){
                operations.push_back(negative);
                DEBUG_PRINT("Negative sign, pushed negative into operations\n");
                //break;
            }
            else operations.push_back(op); //////////////////// experiments //////////////////////
            if(inputStr[pos] == '-' &&
                (pos == 0 || prev == OPERATOR || prev == OPEN_BRACKET)){
                //numberString += '-';
                numberSt.push(new Complex(0, 0));
                DEBUG_PRINT("Negative sign, pushed 0 into numberSt\n");
                //break;
            }
            DEBUG_PRINT("Processing operator %s\n", op->getWord());
            while(calcOrPush(OperationSt, bracketSt, op))
                calcStacks(numberSt, OperationSt);
            OperationSt.push(op);
            DEBUG_PRINT("Pushed %s into Operation stack\n", op->getWord());
            break;
        case OPEN_BRACKET:
            operations.push_back(op); //////////////////// experiments //////////////////////
            DEBUG_PRINT("Processing open bracket %s\n", op->getWord()); ///////////////////////debug
            if(prev == NUMBER || prev == CLOSE_BRACKET || prev == IMAG_UNIT){
                while(calcOrPush(OperationSt, bracketSt, multiply))
                    calcStacks(numberSt, OperationSt);
                OperationSt.push(multiply); // if an operator is not specified, * by default
                DEBUG_PRINT("Pushed additional * into opSt.\n"); ///////////////////////debug
            }
            bracketSt.push({dictionary.searchNextChar(inputStr[pos]), OperationSt.size()});
            DEBUG_PRINT("Pushed %s, %d to bracket stack\n", bracketSt.top().elem->getWord(), bracketSt.top().pos); ///////////////////////debug
            break;
        case CLOSE_BRACKET: {
            operations.push_back(op); //////////////////// experiments //////////////////////
            DEBUG_PRINT("Processing open bracket %s\n", op->getWord()); ///////////////////////debug
            if(bracketSt.size() == 0 ||
               dictionary.searchNextChar(inputStr[pos])->getRankMatch() != (bracketSt.top().elem->getWord())[0]){
                invalid_bracket err(inputStr[pos]);
                throw(err);
            }
            while(calcOrPush(OperationSt, bracketSt, nullptr))
                calcStacks(numberSt, OperationSt);
            DEBUG_PRINT("Popping %s, %d from bracket stack\n", bracketSt.top().elem->getWord(), bracketSt.top().pos); ///////////////////////debug
            bracketSt.pop();
            break;
        }
        case IMAG_UNIT:
            operations.push_back(op); //////////////////// experiments //////////////////////
            if(prev == NUMBER || prev == CLOSE_BRACKET){
                if(GIO.CompNumIO.preOrPost()){ // if imaginary unit is set to prefix
                    invalid_expression err;
                    throw err;
                }
                while(calcOrPush(OperationSt, bracketSt, op))
                    calcStacks(numberSt, OperationSt);
                OperationSt.push(multiply); // if an operator is not specified, * by default
                DEBUG_PRINT("Pushed additional * into opSt.\n"); ///////////////////////debug
            }

            while(calcOrPush(OperationSt, bracketSt, op))
                calcStacks(numberSt, OperationSt);

            OperationSt.push(op);
            DEBUG_PRINT("Pushed %s into Operation stack\n", op->getWord());
            break;
        default:{
            invalid_expression err;
            throw err;
        }
        }
        prev = t; // store the previous type fetched
    }
    /////////////////
    ExpressionTree expressionTree;
    for(unsigned i = 0; i < operations.size(); ++i) {
        DEBUG_PRINT("%s\n", operations[i]->getWord());
        operations[i]->formExpressionTree(expressionTree);
        //expressionTree.printTree((Expression*)expressionTree.getRoot()->getChild(0));
        if(expressionTree.getRoot()->getData())
            DEBUG_PRINT("Root is %s\n", expressionTree.getRoot()->getData()->getWord());
    }
    DEBUG_PRINT("top of expression tree: %s\n", expressionTree.getRoot()->getChild(0)->getData()->getWord());
    DEBUG_PRINT("expression tree result: %z\n", expressionTree.execute());
    //////////////////

    while(OperationSt.size() != 0)
        calcStacks(numberSt, OperationSt);

    if(bracketSt.size() != 0){
        char unmatchedBr = bracketSt.top().elem->getWord()[0];
        while(bracketSt.size() != 0){
            bracketSt.pop();
        }
        invalid_bracket err(unmatchedBr);
        throw(err);
    }
    if(numberSt.size() == 1){
        Complex* result = numberSt.top();
        numberSt.pop();
        Operation * ans = dictionary.searchString("ans");
        ans->setValue(*result);
        DEBUG_PRINT("Answer stored\n");
        return result;
    }
    else{
        invalid_expression err;
        throw err;
    }
    return new Complex(0, 0);
}
