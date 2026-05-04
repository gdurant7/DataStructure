#ifndef DATASTRUCTURES_ORDEREDARRAY_H
#define DATASTRUCTURES_ORDEREDARRAY_H

#include <iostream>
#include "Array.h"
using namespace std;

template <typename TYPE>
class OrderedArray : public Array<TYPE> {
public:

    //insert method
    void insert(TYPE value) override {
        if (this->size == this->capacity) {
            this->resize();
        }
        //get correct index
        int index = 0;
        for (int i=0; this->data[i] < value && i < this->size; i++) {
            index=i;
        }
        for ( int i = this->size; i > index; i--) {
            this->data[i] = this->data[i-1];
        }
        this->data[index] = value;
    }
    void insert(TYPE value, int index) {
        this->insert(value);
        this->size++;
    }

    //binary search
    TYPE find(TYPE target) override {
        int l=0;
        int r= this->size-1;
        while (l <= r) {
            int m = l + (r-l)/2;
            if (this->data[m]==target) {
                return this->data[m];
            }
            if ( this->data[m] < target ) {
                l = m+1;
            }
            if (this->data[m] > target) {
                r = m-1;
            }
        }
        return TYPE();
    }

    //get max value
    TYPE findMax() {
        return this->data[this->size-1];
    }

};


#endif //DATASTRUCTURES_ORDEREDARRAY_H
