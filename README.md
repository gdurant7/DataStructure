# DataStructure

A C++ project for learning how data structures work and how to build them. Each structure is written from scratch as a header-only template class, and a menu-driven `main.cpp` runs a test for each one.

## Structures

| Structure | Description |
|---|---|
| `Array` | Dynamic array that resizes as it grows, with bubble sort, selection sort, and copy support. |
| `OrderedArray` | Array that keeps its values sorted on insert and finds values with binary search. |
| `Map` | Hash map that stores key/value pairs in buckets and grows when it fills up. |
| `ordered_map` | Key/value map that keeps its pairs sorted by key, built on `OrderedArray`. |
| `Stack` | Last-in, first-out structure built on `Array`. |
| `Queue` | First-in, first-out structure built on `Array`. |
| `Linter` | Checks that brackets in a string are balanced, using `Map` and `Stack`. |
| `LinkedList` | Singly linked list. |
| `List` (`DoubleLinkedList.h`) | Doubly linked list. |
| `Tree` | Binary search tree. |

## Requirements

- A C++ compiler that supports C++26 (`CMAKE_CXX_STANDARD 26`)
- CMake 4.2 or newer
- CLion (or another CMake-based IDE)

## Build and Run

1. Open the project folder in CLion.
2. Let CLion load the CMake project.
3. Build and run the `DataStructure` target.

## Running the Tests

`main.cpp` shows a menu of all the structures:

```
==================== DATA STRUCTURES ====================
   1. Array
   2. OrderedArray
   3. Map
   4. ordered_map
   5. Stack
   6. Queue
   7. Linter
   8. LinkedList
   9. List (DoubleLinkedList)
  10. Tree
```

Type a number or a name to run that structure's test, or type `exit` to quit.

Each test prints a label, the expected result, and the actual result so you can compare them.

Most tests end with a commented-out block of invalid-input cases. Remove the `//` (or the `/* */` markers) on one case to run it.

## AI Use

All of the code and implemented data structures in this project were written without the use of AI and will continue to do so.

AI will only be used only as a reviewer. It helps find:

- errors in the code
- structural issues in the design
- possible problems with how the data structures behave

## Known Issues and Planned Work

Known issues, open design decisions, and planned structures are tracked in [ITS.md](ITS.md).
