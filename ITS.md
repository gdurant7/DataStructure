# ITS — DataStructure Project

Line numbers refer to the files as of this ITS.md version.

---

## To Do

### 1. Invalid inputs (documented only, not handled)

| File | Line | Function | Invalid input | Current behavior | Demonstrated in main.cpp (commented out) |
|---|---|---|---|---|---|
| Array.h | 16 | `Array(int capacity, double multiplier)` | capacity ≤ 0, or multiplier ≤ 1 | `resize()` (line 77) does not grow the array; the next `add`/`insert` writes past the end | line 123: `Array<int> a(0, 2.0); a.add(1);`; line 124: `Array<int> a(2, 1.0); … a.add(3);` |
| Array.h | 92 | `read(int index)` | index < 0 or index ≥ size | Reads outside the stored values or outside the array | line 125: `a.read(-1)`; line 126: `a.read(5)` |
| Array.h | 96 | `findMax()` | empty array | Returns an uninitialized `data[0]` | line 127: `a.findMax()` |
| Array.h | 106 | `findMin()` | empty array | Returns an uninitialized `data[0]` | line 128: `a.findMin()` |
| Array.h | 136 | `insert(TYPE value, int index)` | index < 0 or index > size | Writes outside the array, or leaves a gap of unset values | line 129: `a.insert(9, 3)`; line 130: `a.insert(9, -1)` |
| Array.h | 150 | `swap(int index1, int index2)` | negative index | Only checks `< size`; a negative index reads/writes before the array | line 131: `a.swap(-1, 0)` |
| Array.h | 158 | `static swap(...)` | any out-of-range index | No checks; reads/writes outside either array | line 132: `Array<int>::swap(a, 50, b, 0)` |
| Array.h | 167 | `remove()` | empty array | `size` becomes negative | line 133: `a.remove()` |
| Array.h | 172 | `remove(int index)` | index < 0 | Writes before the start of the array | line 134: `a.remove(-1)` |
| Array.h | 172 | `remove(int index)` | index ≥ size | Silently removes the last element | line 135: `a.remove(10)` |
| OrderedArray.h | 52 | `findMax()` | empty array | Reads `data[-1]` | line 189: `a.findMax()` |
| Stack.h | 16 | `pop()` | empty stack | `size` becomes negative | line 327: `s.pop()` |
| Stack.h | 19 | `read()` | empty stack | Reads `data[-1]` | line 328: `s.read()` |
| Queue.h | 15 | `dequeue()` | empty queue | `size` becomes negative | line 398: `q.dequeue()` |
| Queue.h | 19 | `read()` | empty queue | Returns an uninitialized `data[0]` | line 399: `q.read()` |
| LinkedList.h | 48 | `read(int index)` | index < 0 | Returns the head value | line 466: `t.read(-1)` |
| LinkedList.h | 48 | `read(int index)` | empty list, or index ≥ length | Null pointer dereference (crash) | line 467: `t.read(5)`; line 468: `t.read(0)` |
| LinkedList.h | 64 | `insert(TYPE value, int index)` | index ≤ 0 / index > length | Inserts at front / appends at end (clamped) | line 469: `t.insert("front", -5)`; line 470: `t.insert("end", 99)` |
| LinkedList.h | 81 | `remove(int index)` | empty list, or index ≥ length | Null pointer dereference (crash) | line 471: `t.remove(0)`; line 472: `t.remove(5)` |
| LinkedList.h | 81 | `remove(int index)` | index < -1 | Removes the second node (crashes if there is only one node); -1 is ignored | line 473: `t.remove(-1)`; line 474: `t.remove(-2)` |
| DoubleLinkedList.h | 58 | `read(int index)` | empty list | Null pointer dereference (crash) | line 525: `t.read(0)` |
| DoubleLinkedList.h | 58 | `read(int index)` | index < 0 / index ≥ size | Returns the head value / returns `TYPE()` | line 526: `t.read(-1)`; line 527: `t.read(99)` |
| DoubleLinkedList.h | 79 | `insert(TYPE value, int index)` | index ≤ 0 / index ≥ size | Inserts at front / appends at back (clamped) | line 528: `t.insert("front", -3)`; line 529: `t.insert("back", 99)` |
| DoubleLinkedList.h | 119 | `remove(int index)` | index ≤ 0 / index ≥ size − 1 | Removes the head / removes the tail (clamped) | line 530: `t.remove(-5)`; line 531: `t.remove(99)` |
| Map.h | 41 | `Map(int startCap)` | startCap = 0 | Every hash function divides by zero | line 244: `Map<string, string> m(0); m.add("a", "b");` |
| Map.h | 41 | `Map(int startCap)` | startCap < 0 | `new[]` with a negative size | line 245: `Map<string, string> m(-1);` |
| Map.h | 120 | `hash(double key)` | \|key × 1,000,000\| larger than the `int` range, or NaN | Integer overflow (undefined behavior) | line 246: `m.hash(1e10)`; line 247: `m.hash(nan(""))` |

### 2. Return type undecided

**Issue:** functions that receive invalid input (section 1) have no way to report failure to the caller.

**2a. Functions that return a value**
Array.h `read` (92), `findMax` (96), `findMin` (106); OrderedArray.h `findMax` (52); Stack.h `read` (19); Queue.h `read` (19); LinkedList.h `read` (48); DoubleLinkedList.h `read` (58).

Options:
- Return `std::optional<TYPE>`, with `nullopt` on bad input or an empty container. This changes the return type, so callers must change (Map.h `resize` uses `read(j).key`, which would become `read(j)->key`). Linter.h compiles unchanged.
- Return a default value (`TYPE()`). No type change, but the caller can't tell a failure from a stored default value.
- Throw an exception (e.g. `out_of_range`). No type change; the caller needs `try`/`catch` or the program ends.
- Use `assert`. Catches the problem during development only; disabled in release builds.
- Leave as is.

**2b. Functions that return nothing (remove, pop, dequeue, swap)**
Array.h `remove()` (167), `remove(int index)` (172), `swap` (150), static `swap` (158); Stack.h `pop` (16); Queue.h `dequeue` (15); LinkedList.h `remove(int index)` (81), `removeValue` (100, value not found); DoubleLinkedList.h `remove(int index)` (119), `removeValue` (164, value not found).

Options:
- Return `bool`: true on success, false on bad input or value not found.
- Return `std::optional<TYPE>` holding the removed value (`remove`, `pop`, `dequeue`), `nullopt` on failure.
- Return a pointer, `nullptr` on failure. Does not fit these functions: the removed value or node is gone, and pointing to the next element gives `nullptr` when the last element is removed, which looks the same as failure. `swap` has nothing natural to point to.
- Throw an exception.
- Keep `void` and do nothing on bad input.
- Leave as is.

**2c. Insert functions**
Array.h `insert(TYPE value, int index)` (136); LinkedList.h `insert` (64); DoubleLinkedList.h `insert` (79).

Options:
- Return `bool`.
- Return a pointer to the inserted element or node, `nullptr` on bad input. Works for LinkedList (`Node<TYPE>*`) and DoubleLinkedList (`dllNode<TYPE>*`). For Array, a `TYPE*` dangles after the next `resize()`.
- Return an iterator, `end()` on bad input (depends on section 4).
- Throw an exception.
- Keep `void`. LinkedList and DoubleLinkedList currently clamp bad indexes (section 1).
- Note: `Array::insert` is `virtual` and OrderedArray overrides it, so a return-type change in Array.h requires the same change in OrderedArray.h.

**2d. Consistency**
- Same method everywhere: one rule to learn and teach.
- Vary by structure: each function gets the most natural behavior, but more rules to remember.

### 3. Copying linked structures deletes nodes twice

LinkedList.h `~LinkedList` (line 40), DoubleLinkedList.h `~List` (line 38), and Tree.h `~Tree` (line 43) delete their nodes, but none of these classes has a copy constructor or copy assignment. Copying one (for example, passing it by value) gives two objects sharing the same nodes, and both destructors delete them.

Options:
- Add a copy constructor and copy assignment that copy every node (deep copy), as Array and Map do.
- Disable copying (`= delete` on the copy constructor and copy assignment).
- Leave as is.

### 4. Iterators

**Issue:** no structure has iterators. There is no range-based `for` (`for (auto x : list)`) and no way to insert or remove at a position found by traversal.

Options for each design point:

- **Which structures:** all of them, or only some (e.g. the linked lists).
- **Where the iterator code goes:**
  - One shared `Iterator.h` (must avoid circular includes; see below).
  - Each iterator in its own container's header.
  - A class nested inside each container (e.g. `Array<int>::Iterator`); names can never clash.
- **Names (if not nested):** e.g. `ArrayIterator`, `ListIterator`, `dllIterator`, `TreeIterator`, `MapIterator`, `ordered_mapIterator`. ordered_map could also reuse `ArrayIterator<Pair<KEY, VALUE>>`.
- **Operations:**
  - Traversal only: `begin()`, `end()`, `++`, `*`.
  - Traversal plus `insert(iterator, value)` and `remove(iterator)`.
- **Moving backward (`--`):**
  - Only where natural: Array, OrderedArray, DoubleLinkedList, ordered_map.
  - Everywhere: LinkedList has no `prev` link, Map buckets are unordered, and `trNode` has no parent link, so these would need extra work or new members.
- **What `remove(iterator)` returns:** `bool`, or an iterator to the next element (standard library style; allows removing inside a loop).
- **What `insert(iterator, value)` returns:** a node pointer, an iterator to the new element, or `bool`.
- **Structures that choose their own order (OrderedArray, Tree, Map, ordered_map):** inserting at a position can break the ordering. Options: leave out `insert(iterator, value)`, include it but ignore the position, or include it and do nothing.
- **OrderedArray inherits Array's `insert(iterator, value)`** if Array gets one. Options: override it in OrderedArray to do nothing, or allow it.
- **Singly linked list position:** inserting or removing at a position needs the previous node. Options: `insert_after(iterator, value)` / `remove_after(iterator)` (like `std::forward_list`), or the iterator also tracks the previous node.
- **Invalidation after resize (Array, Map, ordered_map):** a resize moves the data. Options:
  - Standard behavior: iterators become invalid after a resize (like `vector`).
  - Index-based: iterator stores the container and an index; survives a resize automatically.
  - Manual `update()`: iterator stores an element pointer, the container, and an index; the caller calls `update()` after a resize. Forgetting it leaves a dangling pointer.
  - Container tracks all live iterators and updates them on resize: needs a new data member and adds overhead.
  - None of these correct for shifts: after an earlier insert/remove, an index-based position points to whatever value is now there.
  - Map rehashes pairs into different buckets on resize, so any update must find the pair again by key.
- **Circular includes:** if a shared `Iterator.h` includes container headers while containers include it, compilation fails. Option: `Iterator.h` uses only forward declarations (`Node`, `dllNode`, `trNode`, `Pair`) and pointers, with each container a `friend` of its iterator.
- **Stack and Queue inherit Array's iterators,** including insert/remove at a position, which allows changing the middle of a stack or queue. Options: allow it, or hide/disable those methods in Stack and Queue.
- **Removal missing:** Tree and Map have no remove function. `remove(iterator)` (or a value-based remove) needs binary search tree deletion (node with zero, one, or two children) for Tree and bucket removal for Map.

### 5. Tree iterator

**Issue:** Tree has no iterator, and building one has two open points.

**Traversal order options:** in-order (sorted, like `std::set`), pre-order, post-order, level-order.

**Implementation options:**
1. Stack-based using the `Stack` class. If the iterator lives in a shared `Iterator.h`, this creates a circular include: `Iterator.h → Stack.h → Array.h → Iterator.h`. It can compile with careful ordering (forward-declare `Array`, define `ArrayIterator`, include Stack.h, then define `TreeIterator`), but breaks if the lines are reordered.
2. Stack-based using the `Stack` class, with `TreeIterator` placed in Tree.h, which can include Stack.h safely.
3. Stack-based with its own small built-in stack (a resizable array of node pointers inside the iterator). No include problem.
4. Not stack-based: keep a pointer to the root and find the next node by walking down from the root each step. O(height) per step, no extra structure.
5. Add a parent pointer to `trNode` so the iterator can move up the tree. Requires a new data member.

### 6. Missing data structures

**DeckQueue**

Issue: Queue.h only adds to the back and removes from the front. There is no structure designed to add and remove at both ends (front and back).

Options:
- Inherit from Array, like Queue. Adding/removing at the front shifts every element (O(n)).
- Build on DoubleLinkedList (`List`). Adding/removing at either end is O(1).
- Circular array (front and back indexes that wrap around). Both ends O(1), no shifting; needs its own resize logic.

**priorityQueue**

Issue: there is no structure that always removes the highest- (or lowest-) priority item first.

Options:
- Build on OrderedArray. Insert O(n) (shifting), remove top O(1).
- Binary heap stored in an Array. Insert and remove top O(log n).
- Unsorted Array. Insert O(1), remove top O(n) (must search for it).
- For any option: decide whether the top is the largest or the smallest value, and whether items are values or (priority, value) pairs.

**Sets**

Issue: there is no structure that stores unique values only (no duplicates) and answers "is this value present?".

Options:
- Hash set (unordered, like `std::unordered_set`): build like Map but store values only. Add, find, remove average O(1).
- Ordered set (sorted, like `std::set`): build on OrderedArray (find O(log n), insert O(n)), or on Tree / a balanced tree (O(log n) when balanced).
- For any option: decide whether adding an existing value is ignored or reported.

**Heap**

Issue: there is no binary heap as a standalone structure (also the usual base for priorityQueue).

Options:
- Binary heap stored in an Array (parent at `i`, children at `2i + 1` and `2i + 2`). Insert and remove top O(log n), read top O(1).
- Min-heap (smallest on top) or max-heap (largest on top).
- Inherit from Array (exposes all Array methods, which can break heap order) or contain an Array as a member.
- Optional: heap sort as an Array sorting method, alongside bubble and selection sort.

**Graph**

Issue: there is no structure for vertices connected by edges.

Options:
- Adjacency list (each vertex keeps a list of neighbors): memory grows with the number of edges; good for sparse graphs. Could build on Map, Array, or LinkedList.
- Adjacency matrix (2D grid of yes/no or weights): O(1) edge check; memory O(V²); good for dense graphs.
- Directed or undirected; weighted or unweighted.
- Traversals often included: breadth-first search (uses Queue) and depth-first search (uses Stack or recursion).

**Balanced trees**

Issue: Tree.h is a plain binary search tree. Inserting values in sorted order makes it a long chain, so search and insert slow to O(n).

Options:
- AVL tree: rebalances with rotations after each insert/remove; strict balance, fastest lookups.
- Red-black tree: looser balance, fewer rotations; what `std::map` and `std::set` usually use.
- Either option needs extra data in each node (height for AVL, color for red-black), so it would use a new node type or new members in `trNode`.

---

## In Progress

Untested structures (no tests in main.cpp):
- Array.h (Array)
- OrderedArray.h (OrderedArray)
- Map.h (Map)
- ordered_map.h (ordered_map)
- Stack.h (Stack)
- Queue.h (Queue)
- Linter.h (Linter)
- DoubleLinkedList.h (List)
- Tree.h (Tree)
- LinkedList.h (LinkedList): only `insert`, `print`, and `search` are used in main.cpp; `read`, `remove`, and `removeValue` are untested.

---

## Testing/QA

main.cpp now has tests for Array, OrderedArray, Map, ordered_map, Stack, Queue, Linter, LinkedList, List (DoubleLinkedList.h) and Tree. Each prints a label, the expected result and the actual result. Invalid-input cases are commented out in a block at the end of each structure's test (remove the `//` on one line to run it); section 1 has a column with the main.cpp line for each.

Observed when each commented-out case was run alone (g++ 13, C++23, Linux):
- Crash: main.cpp 244 (`Map(0)`, divide by zero), 245 (`Map(-1)`, throws `bad_array_new_length`), 467, 468, 471, 472 (LinkedList null dereference), 525 (List `read(0)` on an empty list).
- Abort with "double free or corruption" when the array is freed: 130 (`insert(9, -1)`), 131 (`swap(-1, 0)`), 134 (`remove(-1)`).
- Garbage or unpredictable values printed (undefined behavior): 126, 127, 128, 399; 125, 132, 189, 246, 247 and 328 print without crashing but read or write outside the array or overflow an `int`.
- Defined results as documented: 123, 124 (no visible failure), 129 (gap of unset values), 133 and 327 and 398 (size becomes -1), 135, 466, 469, 470, 473, 474, 526 to 531.
- Tree.h has no documented invalid inputs, so it has no commented-out block. Tree's root is private, so main.cpp checks it with `search` and a small `describe` helper that prints a node's children.

---

## Completed

- Added Tree.h (binary search tree).
- Added DoubleLinkedList.h (doubly linked list, class `List`).
- Renamed the Tree node to `trNode` (Tree.h, line 8).
- Renamed the doubly linked list node to `dllNode` (DoubleLinkedList.h, line 9).