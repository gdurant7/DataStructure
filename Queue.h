#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H
#include "Array.h"

using namespace std;

template <typename TYPE>

class Queue : public Array<TYPE> {
public:
    void enqueue(TYPE value) {
        Array<TYPE>::insert(value);
    }

    void dequeue() {
        this->remove(0);
    }

    TYPE read () {
        return Array<TYPE>::read(0);
    }


};

#endif //DATASTRUCTURE_QUEUE_H
