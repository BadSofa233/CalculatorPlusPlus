#ifndef TOKENIZER_HPP_INCLUDED
#define TOKENIZER_HPP_INCLUDED

#include <vector>
#include "TokenDictionary.hpp"
#include "Token.hpp"
#include "common.hpp"

class Tokenizer{
private:
//    enum ParseStates{
//        PARSE_INIT = 0,
//        PARSE_NUMBER,
//        PARSE_FROM_DICT,
//        PARSE_ID
//    };
    enum ParseStates{
        PARSE_INIT = 0,
        PARSE_NUMBER,
        PARSE_NAME,
        PARSE_OPERATOR
    };
    ParseStates state;
    std::vector<Token *> tempTokens;

    inline bool isNumber(char c) {
        return (c >= '0' && c <= '9') || (c == '.');
    }

    inline bool isValidIDChar(char c) {
        return (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') ||
                c == '_';
    }

    void pushbackHelper(std::vector<Token *> * ret, Token * token) {
        Token * multiply = tokenDictionary.searchString("*");
        Token * negative = tokenDictionary.searchString("negative");
        if(token->getType() == COMMAND) {
            throw invalid_expression();
        }
        TYPE prev = INVALID;
        if(ret->size()) {
            prev = (*ret)[ret->size() - 1]->getType();
        }
        if(token->getWord() == "-" && (ret->size() == 0 || prev == OPERATOR || prev == OPEN_BRACKET)) {
            //if() {
                token = negative;
                //ret->push_back(negative);
            //}
            //else ret->push_back(token);
        }
        else if((token->getType() != OPERATOR && token->getType() != CLOSE_BRACKET) &&
                (prev == CLOSE_BRACKET || prev == NUMBER || prev == VARIABLE)) {
            ret->push_back(multiply);
            //ret->push_back(token);
        }
        else {
            //ret->push_back(token);
        }
        ret->push_back(token);
        tokenDictionary.reset();
    }

public:
    Tokenizer(){
        state = PARSE_INIT;
    }

    std::vector<Token *> * tokenize(const std::string & inputStr) {
        std::string numberStr = "";
        std::string IDStr = "";
        std::string opStr = "";
        std::vector<Token *> * ret = new std::vector<Token *>;
        unsigned pos = 0;
        Token * token;
        for(; pos < inputStr.length(); ++pos){
            token = nullptr;
            DEBUG_PRINT("Tokenizer at %c\n", inputStr[pos]);
            DEBUG_PRINT("State is %d\n", state);
            switch(state) {
            case PARSE_INIT:
                if(isNumber(inputStr[pos])) {
                    state = PARSE_NUMBER;
                    numberStr += inputStr[pos];
                }
                else if(isValidIDChar(inputStr[pos])) {
                    IDStr += inputStr[pos];
                    state = PARSE_NAME;
                }
                else if(tokenDictionary.hasNext(inputStr[pos])) {
                    tokenDictionary.gotoNext(inputStr[pos]);
                    opStr += inputStr[pos];
                    state = PARSE_OPERATOR;
                }
                else {
                    throw invalid_character(inputStr[pos]);
                }
                break;

            case PARSE_NUMBER:
                if(isNumber(inputStr[pos])) {
                    numberStr += inputStr[pos];
                }
                else if(isValidIDChar(inputStr[pos])) {
                    token = new Number(numberStr.c_str());
                    pushbackHelper(ret, token);
                    tempTokens.push_back(token);
                    numberStr = "";
                    IDStr += inputStr[pos];
                    state = PARSE_NAME;
                }
                else if(tokenDictionary.hasNext(inputStr[pos])) {
                    token = new Number(numberStr.c_str());
                    pushbackHelper(ret, token);
                    tempTokens.push_back(token);
                    numberStr = "";
                    opStr += inputStr[pos];
                    state = PARSE_OPERATOR;
                    tokenDictionary.gotoNext(inputStr[pos]);
                }
                else {
                    throw invalid_character(inputStr[pos]);
                }
                break;

            case PARSE_NAME:
                if(isValidIDChar(inputStr[pos])) {
                    IDStr += inputStr[pos];
                }
                else if(tokenDictionary.hasNext(inputStr[pos])) {
                    if(!(token = tokenDictionary.searchString(IDStr))) {
                        token = new Variable(IDStr.c_str());
                        if(inputStr[pos] != '=') {
                            print_warning("using uninitialized variable " + IDStr);
                            tempTokens.push_back(token);
                        }
                        else {
                            tokenDictionary.addToken(token);
                        }
                    }
                    pushbackHelper(ret, token);

                    IDStr = "";
                    state = PARSE_OPERATOR;
                    opStr += inputStr[pos];
                    tokenDictionary.gotoNext(inputStr[pos]);
                }
                else {
                    throw invalid_character(inputStr[pos]);
                }
                break;

            case PARSE_OPERATOR:
                if(tokenDictionary.hasNext(inputStr[pos])) {
                    opStr += inputStr[pos];
                    tokenDictionary.gotoNext(inputStr[pos]);
                }
                else {
                    if(!(token = tokenDictionary.getData())) {
                        throw invalid_func_name(opStr);
                    }
                    pushbackHelper(ret, token);
                    opStr = "";
                    if(isNumber(inputStr[pos])) {
                        state = PARSE_NUMBER;
                        numberStr += inputStr[pos];
                    }
                    else if(isValidIDChar(inputStr[pos])) {
                        state = PARSE_NAME;
                        IDStr += inputStr[pos];
                    }
                    else {
                        state = PARSE_INIT;
                        --pos;
                    }
                }
            }
        }

        if(tokenDictionary.getData()) {
            pushbackHelper(ret, tokenDictionary.getData());
            tokenDictionary.reset();
            IDStr = "";
        }
        if(IDStr != "") {
            if(!(token = tokenDictionary.searchString(IDStr))) {
                print_warning("using uninitialized variable " + IDStr);
                token = new Variable(IDStr.c_str());
            }
            pushbackHelper(ret, token);
            IDStr = "";
        }
        if(numberStr != "") {
            token = new Number(numberStr.c_str());
            pushbackHelper(ret, token);
            tempTokens.push_back(token);
            numberStr = "";
        }

        return ret;
    }

    ~Tokenizer() {
        for(unsigned i = 0; i < tempTokens.size(); ++i) {
            delete tempTokens[i];
        }
    }

};

#endif // TOKENIZER_HPP_INCLUDED
