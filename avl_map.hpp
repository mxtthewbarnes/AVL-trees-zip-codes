#pragma once
#include <iostream>
#include <vector>

using namespace std;

//AVLNode acts as a node in the tree
//stores key-value pairs 
template<typename Key, typename Value>
class AVLNode {
public:
    Key key;            
    Value value;        
    int height;         
    AVLNode* left;      
    AVLNode* right;     

    //              Constructor
    //---------------------------------------
    AVLNode(const Key& k, const Value& v) :
        key(k), value(v), height(1), left(nullptr), right(nullptr) {}
        
};

//avl_map is a self-balancing avl tree -- stores key-value pairs
//maintains balance with insertion and lookup 
template<typename Key, typename Value>
class avl_map {
private:
    AVLNode<Key, Value>* root;  

    //getHeight() returns "height" of node. null node = 0
    int getHeight(AVLNode<Key, Value>* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    //getBalance() finds balance factor of node (height of left sTree - height of right sTree)
    int getBalance(AVLNode<Key, Value>* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    //rightRotate() used to perform a right rotation
    AVLNode<Key, Value>* rightRotate(AVLNode<Key, Value>* y) {
        AVLNode<Key, Value>* x = y->left;
        AVLNode<Key, Value>* T2 = x->right;

        //perfoms rotation and corrects heights with updated values
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    //leftRotate() same deal as rightRotate(), just obv. used for left rotations
    AVLNode<Key, Value>* leftRotate(AVLNode<Key, Value>* x) {
        AVLNode<Key, Value>* y = x->right;
        AVLNode<Key, Value>* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    //insertNode() uses recursion to insert a key-value pair 
    //into the tree. Calls on rightRotate & leftRotate() to balance tree if
    //necessary
    AVLNode<Key, Value>* insertNode(AVLNode<Key, Value>* node, const Key& key, const Value& value) {
        if (node == nullptr) {
            return new AVLNode<Key, Value>(key, value);
        }

        //insertion 
        if (key < node->key) {
            node->left = insertNode(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key, value);
        } else {
            return node;
        }

        //updates height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        //calls on getBalance() to determine 
        //whether rotations are necessary
        int balance = getBalance(node);

        //LL case
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        //RR case
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        //LR case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //RL case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;  
    }

    //eraseNode() removes a key from the tree while keeping balance
    AVLNode<Key, Value>* eraseNode(AVLNode<Key, Value>* node, const Key& key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = eraseNode(node->left, key);
        else if (key > node->key)
            node->right = eraseNode(node->right, key);
        else {
            // Node has one or no children
            if (!node->left || !node->right) {
                AVLNode<Key, Value>* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            // Node has two children: Find in-order successor (smallest in right subtree)
            AVLNode<Key, Value>* temp = node->right;
            while (temp->left) temp = temp->left;

            // Copy successor's data
            node->key = temp->key;
            node->value = temp->value;

            // Delete successor
            node->right = eraseNode(node->right, temp->key);
        }

        // Balance the tree
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Rebalance if necessary
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

public:
    
    //              Constructor 
    //------------------------------------------
    avl_map() : root(nullptr) {}

    //insert() inserts key value into tree
    void insert(const Key& key, const Value& value) {
        root = insertNode(root, key, value);
    }

    //erase() removes a key from the tree
    void erase(const Key& key) {
        root = eraseNode(root, key);
    }

    //iterator for traversing the tree
    class iterator {
    private:
        AVLNode<Key, Value>* current;

    public:
        iterator(AVLNode<Key, Value>* node) : current(node) {}

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

        pair<Key, Value> operator*() {
            return {current->key, current->value};
        }

        iterator& operator++() {
            current = nullptr; 
            return *this;
        }
    };

    //find() searches for key in the tree and 
    //returns pointer to said value if found
    iterator find(const Key& key) {
        AVLNode<Key, Value>* current = root;

        while (current != nullptr) {
            if (key == current->key) {
                return iterator(current);
            } else if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return end(); 
    }

    //begin() returns an iterator to the smallest element
    iterator begin() {
        AVLNode<Key, Value>* current = root;
        while (current && current->left) current = current->left;
        return iterator(current);
    }

    //end() returns an iterator at the end
    iterator end() {
        return iterator(nullptr);
    }
};