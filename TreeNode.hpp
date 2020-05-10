#ifndef TREENODE_HPP_INCLUDED
#define TREENODE_HPP_INCLUDED
//#include "common.hpp"

template <class T>
class TreeNode{
protected:
    char key;
    T * data;
    TreeNode<T> * children; // a pointer to next valid characters
    TreeNode<T> * sibling;
    TreeNode<T> * parent;

public:
    TreeNode(){
        key = 0;
        data = nullptr;
        children = nullptr;
        sibling = nullptr;
        parent = nullptr;
    }

    TreeNode(const char& c){
        key = c;
        data = nullptr;
        children = nullptr;
        sibling = nullptr;
        parent = nullptr;
    }

    TreeNode(const char& c, T * o) {
        key = c;
        data = o;
        children = nullptr;
        sibling = nullptr;
        parent = nullptr;
    }

    TreeNode(const char& c, T * o, TreeNode<T> * p) {
        key = c;
        data = o;
        children = nullptr;
        sibling = nullptr;
        parent = p;
    }

    virtual ~TreeNode(){
        if(data != nullptr)
            delete data;
        TreeNode * temp;
        while(children){
            temp = children;
            children = children->sibling;
            delete temp;
        }
    }

    bool hasChildren() const{
        return children != nullptr;
    }

    char getKey() const {
        return key;
    }

    T * getData() const{
        return data;
    }

    TreeNode * getChild(const char& c) const{
        for(TreeNode * it = children; it != nullptr; it = it->sibling){
            if(it->getKey() == c){
                return it;
            }
        }
        return nullptr;
    }

    TreeNode * getLastChild() const {
        TreeNode * it = children;
        if(it) {
            for(; it->sibling != nullptr; it = it->sibling);
        }
        return it;
    }

    TreeNode * getParent() const {
        return parent;
    }

    void addChild(const char & c) {
        TreeNode * it = children, * prev = children;
        for(it = children; it != nullptr && (int)it->getKey() <= (int)c; it = it->sibling){
        // move it to the position where the char to be added follows an ascending order
            if(it->getKey() == c){
                return;
            }
            prev = it;
        }
        if(it == children){ // if it is at the head
            children = new TreeNode(c, nullptr, this);
            children->sibling = it;
        }
        else{ // if it is in the middle
            prev->sibling = new TreeNode(c, nullptr, this);
            prev = prev->sibling;
            prev->sibling = it;
        }
    }

    void addChild(const char& c, T * o){
        TreeNode * it = children, * prev = children;
        for(it = children; it != nullptr && (int)it->getKey() <= (int)c; it = it->sibling){
        // move it to the position where the char to be added follows an ascending order
            if(it->getKey() == c){
                if(o != nullptr)
                    it->setData(o);
                return;
            }
            prev = it;
        }
        if(it == children){ // if it is at the head
            children = new TreeNode(c, o, this);
            children->sibling = it;
        }
        else{ // if it is in the middle
            prev->sibling = new TreeNode(c, o, this);
            prev = prev->sibling;
            prev->sibling = it;
        }
    }

    virtual void addChild(TreeNode * child) {
        TreeNode * it = children, * prev = children;
        for(it = children; (it != nullptr) && ((int)it->getKey() <= (int)child->getKey()); it = it->sibling){
        // move it to the position where the char to be added follows an ascending order
            if(it->getKey() == child->getKey()){
                if(child->getData() != nullptr)
                    it->setData(child->getData());
                return;
            }
            prev = it;
        }
        if(it == children){ // if it is at the head
            children = child;
            child->setParent(this);
            children->sibling = it;
        }
        else{ // if it is in the middle
            prev->sibling = child;
            child->setParent(this);
            prev = prev->sibling;
            prev->sibling = it;
        }
    }

    void deleteChild(const char& c){
        TreeNode * it = children, * prev = children;
        if(!it)
            return;
        for(; it != nullptr; it = it->sibling){
            if(it->getKey() == c){
                prev->sibling = it->sibling;
                delete it;
                return;
            }
            prev = it;
        }
    }

    TreeNode * replaceChild(const char & k, TreeNode * child) {
        TreeNode * it = children, * prev = children;
        for(; it != nullptr; it = it->sibling){
        // move it to the position where the char to be added follows an ascending order
            if(it->getKey() == k){
                if(it == children){
                    children = child;
                    break;
                }
                prev->sibling = child;
                child->sibling = it->sibling;
                break;
            }
            prev = it;
        }
        child->setKey(k);
        child->setParent(this);
        return it;
    }

    void setKey(const char& k){
        key = k;
    }

    void setData(T * o){
        data = o;
    }

    void setParent(TreeNode<T> * p) {
        parent = p;
    }

    virtual void traverse() {
        TreeNode * it = children;
        for(; it != nullptr; it = it->sibling){
            it->traverse();
        }
    }
};

#endif // TREENODE_HPP_INCLUDED
