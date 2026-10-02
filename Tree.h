#ifndef TREES_TREE_H
#define TREES_TREE_H
#include <iostream>

using namespace std;

template <typename TYPE>
struct trNode {
    TYPE value;
    trNode<TYPE>* left;
    trNode<TYPE>* right;

    trNode(TYPE value){
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

    trNode() : trNode(TYPE()){}
};

template <typename TYPE>
class Tree {
private:
    trNode<TYPE>* root;

    //delete current node and every node below it
    void destroyRec(trNode<TYPE>* current) {
        if (current == nullptr) {
            return;
        }
        this->destroyRec(current->left);
        this->destroyRec(current->right);
        delete current;
    }

public:
    Tree() {
        this->root=nullptr;
    }

    // Destructor
    ~Tree() {
        this->destroyRec(this->root);
    }

    trNode<TYPE>* search(TYPE target, trNode<TYPE>* current) {
        if (current == nullptr) {
            return nullptr;
        }
        else if (current->value==target) {
            return current;
        }
        else if (target < current->value) {
            return this->search(target, current->left);
        }
        else if (target > current->value) {
            return this->search(target, current->right);
        }
        return nullptr;
    }

    trNode<TYPE>* search(TYPE value) {
        return this->search(value, this->root);
    }

    void insertRec(TYPE value, trNode<TYPE>* current) {
        if (value < current->value) {
            if (current->left == nullptr) {
                current->left = new trNode<TYPE>(value);
            }
            else {
                this->insertRec(value, current->left);
            }
        }
        else {
            if (current->right == nullptr) {
                current->right = new trNode<TYPE>(value);
            }
            else {
                this->insertRec(value, current->right);
            }
        }
    }

    void insert(TYPE value) {
        //empty tree
        if (this->root == nullptr) {
            this->root = new trNode<TYPE>(value);
        }
        else {
            this->insertRec(value, this->root);
        }
    }

};

#endif //TREES_TREE_H