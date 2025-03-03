#pragma once

#include <iostream> 
using namespace std; 


template<typename Key, typename Value> 
class avl_map{
    private: 
        AVLNode<Key, Value> * root; 



    public: 



}; 


//AVLNode class to store key-value pairs
template <typename Key, typename Value> 
class AVLNode{
    private: 
        Key key; 
        Value value; 
        int height; 
        AVLNode* left; 
        AVLNode* right; 


    public: 
    //              Constructor
    //------------------------------------
    AVLNode(const Key& k, const Value& v) : 
    key(k), value(v), height(1), left(nullptr), right(nullptr) {}


    //              Getters
    //------------------------------------
    Key getKey() const{
        return key; 
    }
    Value getValue() const{
        return value; 
    }

    AVLNode* getLeft() const{
        return left; 
    }
    AVLNode* getRight() const{
        return right; 
    }

    int getHeight() const{
        return height; 
    }

    //              Setters
    //-------------------------------------
    void setValue(const Value& k)
    {
        value = v; 
    }

    void setHeight(int h)
    {
        height = h; 
    }

    void setLeft(AVLNode* node)
    {
        left = node; 
    }

    void setRight(AVLNode* node)
    {
        right = node; 
    }

    //              Friend declerations
    //-------------------------------------
    template<typename K, typename V> 
    friend class avl_map; 
}; 
