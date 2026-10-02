cmake_minimum_required(VERSION 4.2)
project(DataStructure)

set(CMAKE_CXX_STANDARD 26)

add_executable(DataStructure main.cpp
        Array.h
        OrderedArray.h
        Map.h
        Stack.h
        Linter.h
        Queue.h
        LinkedList.h
        Ordered_map.h
        DoubleLinkedList.h
        Tree.h)
