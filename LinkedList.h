#ifndef DATASTRUCTURE_LinkedLIST_H
#define DATASTRUCTURE_LinkedLIST_H

#include <iostream>

using namespace std;

template <typename TYPE>
struct Node {
    TYPE value;
    Node* next;

    Node() {
        value = nullptr;
        next = nullptr;
    }

    Node(TYPE value) {
        this->value = value;
        this->next = nullptr;
    }
};

template <typename TYPE>
class LinkedList {
private:
    Node<TYPE>* head;

public:
    LinkedList() {
        this->head = nullptr;
    }
    LinkedList(Node<TYPE>* head) {
        this -> head = head;
    }
    LinkedList(TYPE value) {
        this -> head = new Node<TYPE>(value);
    }
    TYPE read(int index) {
        Node<TYPE>* current = this->head;
        for (int i=0; i<index; i++) {
            current = current -> next;
        }
        return current -> value;
    }

    Node<TYPE>* search(TYPE value) {
        Node<TYPE>* current = this->head;
        while (current != nullptr && current->value != value) {
            current = current->next;
        }
        return current;
    }

    void insert(TYPE value, int index) {
        Node<TYPE>* current = this->head;
        for (int i=0; i<index-1 && current->next != nullptr; i++) {
            current = current -> next;
        }
        Node<TYPE>* newNode = new Node<TYPE>(value); {
            if (index == 0) {
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    void remove(int index) {
        if (index == -1) {
            return;
        }
        Node<TYPE>* current = this->head;
        for (int i=0; i<index -1 && current!=nullptr; i++) {
            current = current -> next;
        }
        Node<TYPE>* markedForRemove = current -> next;
        if (index == 0) {
            this->head = markedForRemove;
            delete current;
        }
        else {
            current->next = current->next->next;
            delete markedForRemove;
        }
    }

    void remove(TYPE value) {
        Node<TYPE>* current = this->search(value);
        if (current != nullptr) {
            return;
        }
        Node<TYPE>* markedtoRemove = current->next;
        if (current == this->head) {
            this->head = markedtoRemove;
            delete current;
        }
        else {
            current->next = current->next->value;
            current->next = markedtoRemove->next;
            delete markedtoRemove;
        }
    }

    void print() {
        cout<<"[ ";
        Node<TYPE>* current = this->head;
        while (current != nullptr) {
            cout<<current->value<<" ";
            current = current->next;
        }
        cout<<" ]"<<endl;

    }
};

#endif //DATASTRUCTURE_LinkedLIST_H
