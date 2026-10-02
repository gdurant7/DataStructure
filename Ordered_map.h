#ifndef DATASTRUCTURE_ORDERED_MAP_H
#define DATASTRUCTURE_ORDERED_MAP_H

#include <iostream>
#include <optional>
#include "OrderedArray.h"
#include "Map.h"

using namespace std;

template <typename KEY, typename VALUE>
class ordered_map {
public:
    // Data Members
    // pairs are kept sorted by key
    OrderedArray<Pair<KEY, VALUE>> store;

    //find index of key, -1 if not found
    int findIndex(KEY key) {
        Pair<KEY, VALUE> target(key, VALUE());
        return this->store.find(target);
    }

    //get function
    optional<VALUE> get(KEY key) {
        int index = this->findIndex(key);
        if (index == -1) {
            return nullopt;
        }
        return this->store.read(index).value;
    }

    //add function, updates value if key already exists
    void add(KEY key, VALUE value) {
        int index = this->findIndex(key);
        if (index != -1) {
            this->store.remove(index);
        }
        this->store.insert(Pair<KEY, VALUE>(key, value));
    }

    //display function, prints pairs in key order
    void display() {
        for (int i = 0; i < this->store.len(); i++) {
            cout << "(" << this->store.read(i).key
            << "," << this->store.read(i).value << ") ";
        }
        cout << endl;
    }

    //check if key exists
    bool isKey(KEY key) {
        return this->findIndex(key) != -1;
    }
};

#endif //DATASTRUCTURE_ORDERED_MAP_H