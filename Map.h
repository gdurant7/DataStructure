#ifndef DATASTRUCTURE_MAP_H
#define DATASTRUCTURE_MAP_H

#include <optional>
#include <string>
#include "Array.h"

template <typename KEY, typename VALUE>
struct Pair {
    KEY key;
    VALUE value;
    Pair(KEY k, VALUE v){
        this->key = k;
        this->value = v;
    }
    Pair(){}

    bool operator==(Pair<KEY, VALUE> right) {
        return this->key == right.key;
    }

    bool operator<(Pair<KEY, VALUE> right) {
        return this->key < right.key;
    }

    bool operator>(Pair<KEY, VALUE> right) {
        return this->key > right.key;
    }
};

template <typename KEY, typename VALUE>
class Map {
public:
    // Data Members
    Array<Pair<KEY, VALUE>>** store;
    int size;
    int capacity;
    int startingCapacity;

    // Constructors
    Map(int startCap){
        this->store = new Array<Pair<KEY, VALUE>>*[startCap];
        this->size = 0;
        this->capacity = startCap;
        this->startingCapacity = startCap;
        for(int i = 0; i < startCap; i++){
            store[i] = nullptr;
        }
    }

    Map() : Map(10) {}

    // Copy Constructor
    Map(const Map<KEY, VALUE>& other){
        this->size = other.size;
        this->capacity = other.capacity;
        this->startingCapacity = other.startingCapacity;
        this->store = new Array<Pair<KEY, VALUE>>*[this->capacity];
        for(int i = 0; i < this->capacity; i++){
            if(other.store[i] != nullptr){
                this->store[i] = new Array<Pair<KEY, VALUE>>(*other.store[i]);
            }
            else {
                this->store[i] = nullptr;
            }
        }
    }

    // Copy Assignment
    Map<KEY, VALUE>& operator=(const Map<KEY, VALUE>& other){
        if(this != &other){
            // Copy buckets into a new store
            Array<Pair<KEY, VALUE>>** newStore = new Array<Pair<KEY, VALUE>>*[other.capacity];
            for(int i = 0; i < other.capacity; i++){
                if(other.store[i] != nullptr){
                    newStore[i] = new Array<Pair<KEY, VALUE>>(*other.store[i]);
                }
                else {
                    newStore[i] = nullptr;
                }
            }
            // Delete the original store
            for(int i = 0; i < this->capacity; i++){
                if(store[i] != nullptr){
                    delete store[i];
                }
            }
            delete[] this->store;
            this->store = newStore;
            this->size = other.size;
            this->capacity = other.capacity;
            this->startingCapacity = other.startingCapacity;
        }
        return *this;
    }

    // Destructor
    ~Map(){
        for(int i = 0; i < this->capacity; i++){
            if(store[i] != nullptr){
                delete store[i];
            }
        }
        delete[] this->store;
    }

    // HASH FUNCTIONS
    // Each function takes a different type and converts it to an int index

    // int keys
    int hash(int key){
        int index = key % this->capacity;
        if (index < 0) {
            index += this->capacity;
        }
        return index;
    }

    // double keys
    int hash(double key){
        int index = int(key * 1000000) % this->capacity;
        if (index < 0) {
            index += this->capacity;
        }
        return index;
    }

    //char keys
    int hash(char key) {
        return (unsigned char)key % this->capacity;
    }
    // string keys
    int hash(string key){
        unsigned int value = 0;
        for(int i = 0; i < key.size(); i++){
            value += (unsigned int)(i + 1) * (unsigned char)key[i];
        }
        return value % this->capacity;
    }

    // RESIZE
    void resize() {
        //create new store, remember location of oldstore
        Array< Pair<KEY, VALUE>>** ogStore = this->store;
        this->store= new Array<Pair<KEY, VALUE>>*[this->capacity + this->startingCapacity];

        //update capacity but remember old
        int ogCapacity = this->capacity;
        this->capacity = this->capacity + this->startingCapacity;
        //place nullptr in each location of new store
        for(int i = 0; i < this->capacity; i++) {
            this->store[i] = nullptr;
        }
        //move key/value pairs from old store to new store
        int index = 0;
        Pair<KEY, VALUE> pair;

        for (int i = 0; i < ogCapacity; i++) {
            //if bucket in this location
            if (ogStore[i] != nullptr) {
                //loop through bucke list in thislocation
                for (int j=0; j<ogStore[i]->len();j++) {
                    //new index for key for each pair in bucket
                    index = hash(ogStore[i]->read(j).key);
                    //check to see if there is a bucket at that location in new store
                    //create one if not
                    if (this->store[index]==nullptr) {
                        this->store[index]=new Array< Pair<KEY, VALUE>>();
                    }
                    //add pair to new store
                    pair = Pair(ogStore[i]->read(j).key, ogStore[i]->read(j).value);
                    this->store[index]->add(pair);
                }
            }
        }

        //delete old store
        for (int i = 0 ; i < ogCapacity; i++) {
            if (ogStore[i] != nullptr) {
                delete ogStore[i];
            }
        }
        delete[] ogStore;
    }
    //get function
    optional<VALUE> get(KEY key) {
        int index = hash(key);

        //loop through bucket at location to get pair with key
        if (this->store[index] != nullptr) {
            for (int i=0; i<this->store[index]->len(); i++) {
                //check to see if matching
                if (this->store[index]->read(i).key == key) {
                    return this->store[index]->read(i).value;
                }
            }
        }
        return nullopt;
    }
    //add function
    void add(KEY key, VALUE value) {
        //hash key to find index
        int index = hash(key);

        //if key already exists, update its value
        if (this->store[index] != nullptr) {
            for (int i=0; i<this->store[index]->len(); i++) {
                if (this->store[index]->read(i).key == key) {
                    this->store[index]->remove(i);
                    this->store[index]->insert(Pair<KEY, VALUE>(key, value));
                    return;
                }
            }
        }

        //check size
        if (this->size >= this-> capacity * 0.7) {
            this->resize();
            //capacity changed, hash key again
            index = hash(key);
        }

        //check to see if bucket exists
        if (this->store[index]==nullptr) {
            this->store[index] = new Array< Pair<KEY, VALUE>>();
        }
        //creat new pair for the key and value
        Pair<KEY, VALUE> pair(key, value);

        //insert pair into bucket at index location
        this->store[index]->insert(pair);

        //update size
        this->size++;
    }

    //display function
    void display() {
        //loop through store array
        for (int i = 0; i < this->capacity; i++) {
            //print index location
            cout << i << " : ";
            //check for bucket at this location
            if (this->store[i] != nullptr) {
                //check bucket and print item
                for (int j=0; j<this->store[i]->len(); j++) {
                    cout << "(" << this->store[i]->read(j).key
                    << "," << this->store[i]->read(j).value << ")- ";
                }
            }
            cout << endl;
        }
    }

    //check if key exists
    bool isKey(KEY key) {
        return this->get(key).has_value();
    }

};


#endif //DATASTRUCTURE_MAP_H