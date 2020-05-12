#ifndef DICTIONARY_HPP_INCLUDED
#define DICTIONARY_HPP_INCLUDED

#include <string>
#include "Token.hpp"
#include "Trie.hpp"
#define ALPHABET_SIZE 26

class Dictionary {
private:
    Trie<Token> * dictionary;
    TreeNode<Token> * cursor;

public:
    Dictionary();
    bool hasNext(char c) const; // returns the current node has a child with data c
    void reset(); // reset the cursor of trie to root
    Token * getData() const; // return the operation pointer of current string
    Token * searchNextChar(char) const;
    Token * searchString(const std::string &); // search the dictionary with an entire string
    void addWord(Token *);
    void deleteWord(const char &);
    void deleteWord(const std::string &);
    void gotoNext(const char &);
};

extern Dictionary dictionary;

#endif // DICTIONARY_HPP_INCLUDED
