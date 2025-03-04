#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename Key, typename Value>
class AVLNode {
public:
    Key key;
    Value value;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const Key& k, const Value& v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

template<typename Key, typename Value>
class avl_map {
private:
    AVLNode<Key, Value>* root;

    int getHeight(AVLNode<Key, Value>* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode<Key, Value>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode<Key, Value>* rightRotate(AVLNode<Key, Value>* y) {
        AVLNode<Key, Value>* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode<Key, Value>* leftRotate(AVLNode<Key, Value>* x) {
        AVLNode<Key, Value>* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode<Key, Value>* insertNode(AVLNode<Key, Value>* node, const Key& key, const Value& value) {
        if (!node) return new AVLNode<Key, Value>(key, value);

        if (key < node->key)
            node->left = insertNode(node->left, key, value);
        else if (key > node->key)
            node->right = insertNode(node->right, key, value);
        else
            return node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);

        // Balancing cases
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

public:
    avl_map() : root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        root = insertNode(root, key, value);
    }

    Value* find(const Key& key) {
        AVLNode<Key, Value>* current = root;
        while (current) {
            if (key == current->key)
                return &current->value;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }
};