#ifndef TRIE_HPP_INCLUDED
#define TRIE_HPP_INCLUDED

#include "TreeNode.hpp"
#include <string>

template <class T>
class Trie{
public:
    Trie(){
        root = new TreeNode<T>();
    }

    ~Trie(){
        delete root;
    }

    TreeNode<T> * getRoot() const{
        return root;
    }

    void addWord(T * op){
        TreeNode<T> * it = root; // set an iterator to root
        std::string s = op->getWord(); // get the word from the functor
        unsigned i;
        for(i = 0; i < s.length() - 1; ++i){
            if(s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
            it->addChild(s[i]); // add child to the current node with no terminal
            it = it->getChild(s[i]);
        }
        it->addChild(s[i], op); // add child to the current node with terminal and functor pointer
    }

    void deleteWord(const char& c){
        TreeNode<T> * it = root;
        it = it->getChild(c);
        if(!it || !it->getData()){
            std::invalid_argument err("Error deleting word.");
            throw err;
        }
        if(it->hasChildren()) // if this word is in another word, eg, sin in sinh
            delete it->getData();
        else{
            root->deleteChild(c);
        }
    }

    void deleteWord(const std::string& s){
        TreeNode<T> * it = root;
        unsigned i = 0;
        int mark = -1;
        for(; i < s.length(); ++i){
            it = it->getChild(s[i]);
            if(!it){
                std::invalid_argument err("Error deleting word.");
                throw err;
            }
            if(i < s.length() - 1 && it->getData())
                mark = i;
        }
        if(!it->getData()){
            std::invalid_argument err("Error deleting word.");
            throw err;
        }
        if(it->hasChildren()) // if this word is in another word, eg, sin in sinh
            delete it->getData();
        else{
            it = root; // start again, delete everything after the mark
            for(i = 0; i < (unsigned)(mark + 1); ++i){
                it = it->getChild(s[i]);
            }
            it->deleteChild(s[mark + 1]);
        }
    }

    void deleteWord(const char * name){
        TreeNode<T> * it = root;
        std::string s = name;
        unsigned i = 0;
        int mark = -1;
        for(; i < s.length(); ++i){
            it = it->getChildren(s[i]);
            if(!it){
                std::invalid_argument err("Error deleting word.");
                throw err;
            }
            if(i < s.length() - 1 && it->getData())
                mark = i;
        }
        if(!it->getData()){
            std::invalid_argument err("Error deleting word.");
            throw err;
        }
        if(it->hasChildren()) // if this word is in another word, eg, sin in sinh
            delete it->getData();
        else{
            it = root; // start again, delete everything after the mark
            for(i = 0; i < (unsigned)(mark + 1); ++i){
                it = it->getChildren(s[i]);
            }
            it->deleteChild(s[mark + 1]);
        }
    }

    T * retrieve(const std::string& s) const{
        TreeNode<T> * it = root;
        for(unsigned i = 0; i < s.length(); ++i){
            it = it->getChildren(s[i]);
            if(!it)
                return nullptr;
        }
        return it->getData();
    }

    T * retrieve(const char& c) const{
        TreeNode<T> * it = root;
        it = it->getChildren(c);
        return it ? it->getData() : nullptr;
    }

    T * retrieve(std::string&& s) const{
        TreeNode<T> * it = root;
        for(unsigned i = 0; i < s.length(); ++i){
            if(s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
            it = it->getChildren(s[i]);
            if(!it)
                return nullptr;
        }
        if(!it->getData()) return nullptr;
        return it->getData();
    }

private:
    TreeNode<T> * root;
};

#endif // TRIE_HPP_INCLUDED
