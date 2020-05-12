#include "Dictionary.hpp"
#include "Token.hpp"
#include "Operator.hpp"
#include "Number.hpp"
#include "Command.hpp"
#include "MathFunctions.hpp"
#include "Bracket.hpp"
#include <iostream>
#include <string>

Dictionary dictionary;

Dictionary::Dictionary(){
    dictionary = new Trie<Token>();
    cursor = dictionary->getRoot();
    /// Operators:
    dictionary->addWord(new Plus());
    dictionary->addWord(new Minus());
    dictionary->addWord(new Multiply());
    dictionary->addWord(new Divide());
    dictionary->addWord(new Power());
    dictionary->addWord(new Negative());
#ifdef CALCULATOR_VERSION_2_0
    /// Logic operators:
    dictionary->addWord(new And());
    dictionary->addWord(new Or());
    dictionary->addWord(new Not());
    dictionary->addWord(new Xor());
    dictionary->addWord(new Nor());
    dictionary->addWord(new Nand());
    dictionary->addWord(new AndSymbolic());
    dictionary->addWord(new OrSymbolic());
    dictionary->addWord(new NotSymbolic());
    dictionary->addWord(new XorSymbolic());
#endif // CALCULATOR_VERSION_2_0
    /// Brackets:
    dictionary->addWord(new OpenRound());
    dictionary->addWord(new CloseRound());
    dictionary->addWord(new OpenSquare());
    dictionary->addWord(new CloseSquare());
    dictionary->addWord(new OpenCurly());
    dictionary->addWord(new CloseCurly());
    /// Numbers:
    dictionary->addWord(new Pi());
    dictionary->addWord(new E());
    for(int i = 0; i < 10; ++i)
        dictionary->addWord(new Number(i));
    dictionary->addWord(new Number("."));
    /// Math functions:
    dictionary->addWord(new Sin());
    dictionary->addWord(new Cos());
    dictionary->addWord(new Tan());
    dictionary->addWord(new Cot());
    dictionary->addWord(new Sinh());
    dictionary->addWord(new Cosh());
    dictionary->addWord(new Tanh());
    dictionary->addWord(new Asin());
    dictionary->addWord(new Acos());
    dictionary->addWord(new Atan());
    dictionary->addWord(new Acot());
    dictionary->addWord(new Asinh());
    dictionary->addWord(new Acosh());
    dictionary->addWord(new Atanh());
    dictionary->addWord(new Log());
    dictionary->addWord(new Ln());
    dictionary->addWord(new Db());
    dictionary->addWord(new Exp());
    dictionary->addWord(new Sqrt());
    dictionary->addWord(new Abs());
    dictionary->addWord(new Angle());
    dictionary->addWord(new Cis());
    ///Commands:
    dictionary->addWord(new Help());
    dictionary->addWord(new Calculate());
    dictionary->addWord(new Exit());
    dictionary->addWord(new Use());
    dictionary->addWord(new License());
    dictionary->addWord(new About());
    ///Misc:
    dictionary->addWord(new Ans());
    dictionary->addWord(new Parallel());
    DEBUG_PRINT("Tokens added\n");
}

bool Dictionary::hasNext(char c) const {
    return cursor->getChild(c) != nullptr;
}

void Dictionary::reset() {
    cursor = dictionary->getRoot();
    DEBUG_PRINT("reset dictionary\n");
}

Token * Dictionary::getData() const {
    return cursor->getData();
}

Token * Dictionary::searchNextChar(char c) const {
    TreeNode<Token> * retNode = cursor->getChild(c);
    if(retNode)
        return retNode->getData();
    return nullptr;
}

Token * Dictionary::searchString(const std::string & s){
    reset();
    unsigned i = 0;
    for(; i < s.length() && cursor->getChild(s[i]); gotoNext(s[i++]));
    Token * ret = nullptr;
    if(i == s.length())
        ret = cursor->getData();
    cursor = dictionary->getRoot();
    return ret;
}

void Dictionary::addWord(Token * op) {
    dictionary->addWord(op);
}

void Dictionary::deleteWord(const char & c) {
    dictionary->deleteWord(c);
}

void Dictionary::deleteWord(const std::string & s) {
    dictionary->deleteWord(s);
}

void Dictionary::gotoNext(const char & c) {
    cursor = cursor->getChild(c);
}
