#ifndef DATASTRUCTURES_ARRAY_H
#define DATASTRUCTURES_ARRAY_H

#include <iostream>
using namespace std;

template <typename TYPE>
class Array {
protected:
    TYPE* data;
    int size;
    int capacity;
    double multiplier;

public:
    Array(int capacity, double multiplier) {
        this->size = 0;
        this->capacity = capacity;
        this->multiplier = multiplier;
        this->data = new TYPE[this->capacity];
    }

    Array(int capacity) : Array(capacity, 10) {}

    Array(double multiplier) : Array(10, multiplier) {}

    Array() : Array(10, 10) {}

    ~Array() {
        delete[] this->data;
    }

    // Get Size
    int length() {
        return this->size;
    }

    int len() {
        return this->size;
    }

    // Resize Method
    void resize() {
        // Remember the location of the original array
        TYPE* ogData = this->data;

        // Increase capacity for the new underlying array
        this->capacity *= this->multiplier;

        // Create the new larger underlying array
        this->data = new TYPE[this->capacity];

        // Copy old array to new one
        for(int i = 0; i < this->size; i++){
           this->data[i] = ogData[i];
        }

        // Delete the original array
        delete[] ogData;
    }

    // Read Method
    TYPE read(int index) {
            return this->data[index];
    }

    TYPE findMax() {
        TYPE maxVal = this->data[0];
        for (int i=1; i<this->size; i++) {
            if (maxVal < this->data[i]) {
                maxVal = this-data[i];
            }
        }
        return maxVal;
    }

    TYPE findMin(){
        TYPE minVal = this->data[0];
        for (int i=0; i<this->size; i++) {
            if (minVal > this->data[i]) {
                minVal = this->data[i];
            }
        }
        return minVal;
    }

    //insert elements into array
    //add to end of deck
    virtual void add(TYPE value){
        if (this->size == this->capacity) {
            this->resize();
        }
        this->data[this->size]=value;
        this->size++;
    }
    //add to start
    virtual void add(TYPE value, int index){
        if (this->size == this->capacity) {
            this->resize();
        }
        //shift elements from end up to desired indes
        for (int i=this->size; i>0; i--) {
            this->data[i]=this->data[i-1];
        }
        //replace value at index location
        this->data[index]=value;
        this->size++;
    }
    //insert
    virtual void insert(TYPE value) {
        //check if array is at capacity
        if (this->size == this->capacity) {
            this->resize();
        }
        //insert value at end of array
        this->data[this->size]=value;
        this->size++;
    }

    virtual void insert(TYPE value, int index){
        //check size
        if (this->size == this->capacity) {
            this->resize();
        }
        //shift elements from end up to desired indes
        for (int i=this->size; i>index; i--) {
            this->data[i]=this->data[i-1];
        }
        //replace value at index location
        this->data[index]=value;
        this->size++;
    }
    //swap positions
    virtual void swap(int index1, int index2){
        if (index1 < this->size && index2 < this->size) {
            TYPE temp = this->data[index1];
            this->data[index1] = this->data[index2];
            this->data[index2] = temp;
        }
    }
    //swap between different array
    static void swap(Array<TYPE>& Array1, int indexA, Array<TYPE>& Array2, int indexB) {
        TYPE temp = Array1.data[indexA];
        Array1.data[indexA] = Array2.data[indexB];
        Array2.data[indexB] = temp;
    }

    // Remove Methods

    //Remove last element
    void remove() {
        this->size--;
    }

    //remove element [i]
    void remove(int index) {
        for(int i = index; i < this->size - 1; i++){
            this->data[i] = this->data[i + 1];
        }
        this->size--;
    }

    //linear search
    virtual int find(TYPE value) {
        //loop through array
        for (int i=0; i<this->size; i++) {
            //if index is found
            if (this->data[i] == value)
                return i;
        }
        //if its not found
        return -1;
    }

    // Overload of << Operator
    friend ostream& operator<<(ostream& left, Array<TYPE>& right) {
        left << "[ ";
        for(int i = 0; i < right.size; i++){
            left << right.data[i] << " ";
        }
        left << "]";
        return left;
    }

    // Overload of + Operator
    Array<TYPE> operator+(Array<TYPE> right) {
        Array<TYPE> noob;
        for(int i = 0; i < this->size; i++){
            noob.insert(this->data[i]);
        }
        for(int i = 0; i < right.size; i++){
            noob.insert(right.data[i]);
        }
        return noob;
    }

    void operator+(TYPE right) {
        this->insert(right);
    }

    // HELPER SWAP FUNCTION
    void simpleSwap(int a, int b){
        TYPE temp = this->data[a];
        this->data[a] = this->data[b];
        this->data[b] = temp;
    }

    // BUBBLE SORT
    void bubbleSort(){
        int unsorted = this->size - 1;
        bool sorted = false;
        while(!sorted){
            sorted = true;
            for(int i = 0; i < unsorted; i++){
                if(this->data[i] > this->data[i + 1]){
                    this->simpleSwap(i, i + 1);
                    sorted = false;
                }
            }
            unsorted -= 1;
        }
    }

    // SELECTION SORT
    void selectionSort(){
        // To hold index of lowest value
        int lowest = 0;
        // Outside loop represents passes
        for(int i = 0; i < this->size - 1; i++){
            lowest = i;
            // Inside loop is the traversal of array for comparison
            for(int j = i; j < size; j++){
                // Compare current value to current lowest value
                if(this->data[j] < this->data[lowest]){
                    lowest = j;
                }
            }
            // Make swap if necessary
            if(lowest != i)
                this->swap(i, lowest);
        }
    }
};


#endif //DATASTRUCTURES_ARRAY_H
