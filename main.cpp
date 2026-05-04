#include <iostream>
#include "Array.h"
#include "OrderedArray.h"
#include "Map.h"
#include "Stack.h"
#include "Linter.h"
#include "LinkedList.h"

using namespace std;

int main() {
    //testing for Array.h

    //testing for orderedArray.h

    //testing for map.h

    //testing for stack.h

    //testing for Linter.h

    //testing for LinkedList.h
    LinkedList<string> sports;
    sports.insert("football", 0);
    sports.insert("soccer", 1);
    sports.insert("baseball", 2);
    sports.insert("basketball", 3);
    sports.insert("lacrosse", 4);
    sports.insert("golf", 5);
    sports.insert("bowling", 6);
    sports.print();
    sports.remove("");
    sports.search("baseball");
    sports.print();

}
