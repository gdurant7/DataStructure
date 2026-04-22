#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

#include "Array.h"

using namespace std;

template <typename TYPE>

class Stack : public Array<TYPE> {
public:
    //push
    void push(TYPE value) {
        this->insert(value);
    }
    void pop() {
        this->remove();
    }
    TYPE read() {
        return Array<TYPE>::read(this->size-1);
    }


};

#endif //DATASTRUCTURE_STACK_H
