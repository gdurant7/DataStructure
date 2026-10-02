#ifndef DOUBLELINKEDLIST_LIST_H
#define DOUBLELINKEDLIST_LIST_H
#include <iostream>
#include <ostream>

using namespace std;

template <typename TYPE>
struct dllNode {
    TYPE value;
    dllNode<TYPE>* next;
    dllNode<TYPE>* prev;

    dllNode(TYPE value) {
        this-> value = value;
        this->next= nullptr;
        this->prev = nullptr;
    }

    dllNode() : dllNode<TYPE>(TYPE()) {}
};

template <typename TYPE>
class List {
private:
    dllNode<TYPE>* head;
    dllNode<TYPE>* tail;
    int size;

public:
    List() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    // Destructor
    ~List() {
        dllNode<TYPE>* current = this->head;
        while (current != nullptr) {
            dllNode<TYPE>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void print() {
        cout << "[ ";
        dllNode<TYPE>* current = this->head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << " ]\n";
    }

    //read
    TYPE read(int index) {
        dllNode<TYPE>* current = this->head;
        for (int i = 0; i<index; i++) {
            current = current -> next;
            if (current == nullptr) {
                return TYPE();
            }
        }
        return current->value;
    }

    //search
    dllNode<TYPE>* search(TYPE value) {
        dllNode<TYPE>* current = this->head;
        while (current != nullptr && current->value != value) {
            current = current->next;
        }
        return current;
    }

    //insert
    void insert(TYPE value, int index) {
        //create new node
        dllNode<TYPE>* newNode = new dllNode<TYPE>(value);

        dllNode<TYPE>* current = this->head;
        //empty list
        if (this->head  == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        }
        //insert at front
        else if (index <= 0) {
            newNode->next = this->head;
            this->head->prev = newNode;
            this->head = newNode;
        }
        //insert at back
        else if (index >= this->size) {
        newNode->prev = this->tail;
        this->tail->next = newNode;
        this->tail = newNode;
        }
        //insert in middle
        else {
            for (int i=0; i<index; i++) {
                current = current->next;
            }
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
        //increment size
        this->size++;
    }

    void insert(TYPE value) {
        this->insert(value, this->size);
    }
    //delete
    void remove(int index) {
        //set curret to head
        dllNode<TYPE>* current = this->head;

        //empty list?
        if (this->head == nullptr) {
            return;
        }
        //remove head
        else if (index <= 0) {
            this->head = this->head->next;
            if (this->head != nullptr) {
                this->head->prev = nullptr;
            }
            else {
                this->tail = nullptr;
            }
            delete current;
        }
        //remove tail
        else if (index >= this->size-1) {
            current = this->tail;
            this->tail = this->tail->prev;
            if (this->tail != nullptr) {
                this->tail->next = nullptr;
            }
            else {
                this->head = nullptr;
            }
            delete current;
        }
        //remove from middle
        else {
            for (int i = 0; i< index; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        //decrement size
        this->size--;
    }

    //delete by value
    void removeValue(TYPE value) {
        dllNode<TYPE>* current = this->search(value);
        //value not found
        if (current == nullptr) {
            return;
        }
        //unlink from previous node, or move head
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        else {
            this->head = current->next;
        }
        //unlink from next node, or move tail
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
        else {
            this->tail = current->prev;
        }
        delete current;
        this->size--;
    }

};

#endif //DOUBLELINKEDLIST_LIST_H