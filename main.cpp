#include <iostream>
#include <sstream>
#include <string>
#include <optional>
#include <cmath>
#include "Array.h"
#include "OrderedArray.h"
#include "Map.h"
#include "Ordered_map.h"
#include "Stack.h"
#include "Queue.h"
#include "Linter.h"
#include "LinkedList.h"
#include "DoubleLinkedList.h"
#include "Tree.h"

using namespace std;

// ---------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------

// Prints a label, what we expect, and what we actually got
template <typename T>
void show(const string& label, const string& expected, T&& got) {
    ostringstream out;
    out << boolalpha << got;
    cout << "  " << label << "\n"
         << "      expected: " << expected << "\n"
         << "      got:      " << out.str() << endl;
}

void section(const string& title) {
    cout << "\n===== " << title << " =====" << endl;
}

// Tree keeps its root private, so it cannot be walked from here.
// This describes one node (found with search) and the values of its children.
template <typename T>
string describe(Tree<T>& tree, type_identity_t<T> value) {
    ostringstream out;
    trNode<T>* node = tree.search(value);
    if (node == nullptr) {
        out << value << ": not found";
        return out.str();
    }
    out << value << ": left=";
    if (node->left != nullptr) out << node->left->value; else out << "none";
    out << " right=";
    if (node->right != nullptr) out << node->right->value; else out << "none";
    return out.str();
}

int main() {

    // ===============================================================
    // Array.h - topic: exam scores
    // ===============================================================
    section("Array (exam scores)");
    {
        Array<int> scores;
        scores.add(90);
        scores.add(75);
        scores.add(88);
        show("add(90), add(75), add(88)", "[ 90 75 88 ]", scores);
        show("length()", "3", scores.length());
        show("len()", "3", scores.len());
        show("read(1)", "75", scores.read(1));
        show("findMax()", "90", scores.findMax());
        show("findMin()", "75", scores.findMin());

        scores.insert(60);
        show("insert(60) at the end", "[ 90 75 88 60 ]", scores);
        scores.insert(100, 0);
        show("insert(100, 0)", "[ 100 90 75 88 60 ]", scores);
        scores.swap(0, 4);
        show("swap(0, 4)", "[ 60 90 75 88 100 ]", scores);

        Array<int> retake;
        retake.add(1);
        Array<int>::swap(scores, 0, retake, 0);
        show("static swap(scores, 0, retake, 0) - scores", "[ 1 90 75 88 100 ]", scores);
        show("static swap(scores, 0, retake, 0) - retake", "[ 60 ]", retake);

        scores.remove();
        show("remove() removes the last", "[ 1 90 75 88 ]", scores);
        scores.remove(0);
        show("remove(0)", "[ 90 75 88 ]", scores);
        show("find(88)", "2", scores.find(88));
        show("find(5) not present", "-1", scores.find(5));

        scores.bubbleSort();
        show("bubbleSort()", "[ 75 88 90 ]", scores);
        scores.simpleSwap(0, 2);
        show("simpleSwap(0, 2)", "[ 90 88 75 ]", scores);
        scores.selectionSort();
        show("selectionSort()", "[ 75 88 90 ]", scores);

        show("scores + retake (Array + Array)", "[ 75 88 90 60 ]", scores + retake);
        scores + 95;
        show("scores + 95 (adds to scores)", "[ 75 88 90 95 ]", scores);

        Array<int> copy(scores);
        copy.add(1);
        show("copy constructor, add(1) to the copy - copy", "[ 75 88 90 95 1 ]", copy);
        show("copy constructor - original unchanged", "[ 75 88 90 95 ]", scores);
        Array<int> assigned;
        assigned = scores;
        assigned.remove(0);
        show("copy assignment, remove(0) from the copy - copy", "[ 88 90 95 ]", assigned);
        show("copy assignment - original unchanged", "[ 75 88 90 95 ]", scores);

        Array<int> tiny(2, 2.0);
        tiny.add(1);
        tiny.add(2);
        tiny.add(3);
        show("Array(2, 2.0) then 3 adds (forces resize)", "[ 1 2 3 ]", tiny);
        tiny.resize();
        show("resize() keeps the values", "[ 1 2 3 ]", tiny);

        cout << "\n  -- invalid inputs (commented out, remove the // to run one) --" << endl;
        // ---- INVALID INPUTS START ----
        // { Array<int> a(0, 2.0); a.add(1); cout << "  Array(0, 2.0) then add(1)\n      expected: writes past the end of the array (undefined)\n      got len:  " << a.len() << endl; }
        // { Array<int> a(2, 1.0); a.add(1); a.add(2); a.add(3); cout << "  Array(2, 1.0) then 3 adds\n      expected: third add writes past the end of the array (undefined)\n      got:      " << a << endl; }
        // { Array<int> a; a.add(10); cout << "  read(-1)\n      expected: reads outside the array (undefined)\n      got:      " << a.read(-1) << endl; }
        // { Array<int> a; a.add(10); cout << "  read(5) with size 1\n      expected: reads outside the stored values (undefined)\n      got:      " << a.read(5) << endl; }
        // { Array<int> a; cout << "  findMax() on empty array\n      expected: uninitialized data[0]\n      got:      " << a.findMax() << endl; }
        // { Array<int> a; cout << "  findMin() on empty array\n      expected: uninitialized data[0]\n      got:      " << a.findMin() << endl; }
        // { Array<int> a; a.add(1); a.insert(9, 3); cout << "  insert(9, 3) with size 1\n      expected: gap of unset values between 1 and 9\n      got:      " << a << endl; }
        // { Array<int> a; a.add(1); a.insert(9, -1); cout << "  insert(9, -1)\n      expected: writes before the start of the array (undefined)\n      got len:  " << a.len() << endl; }
        // { Array<int> a; a.add(1); a.swap(-1, 0); cout << "  swap(-1, 0)\n      expected: reads/writes before the start of the array (undefined)\n      got:      " << a << endl; }
        // { Array<int> a, b; a.add(1); b.add(2); Array<int>::swap(a, 50, b, 0); cout << "  static swap(a, 50, b, 0)\n      expected: reads/writes outside the array (undefined)\n      got b:    " << b << endl; }
        // { Array<int> a; a.remove(); cout << "  remove() on empty array\n      expected: size becomes -1\n      got len:  " << a.len() << endl; }
        // { Array<int> a; a.add(1); a.add(2); a.add(3); a.remove(-1); cout << "  remove(-1)\n      expected: writes before the start of the array (undefined)\n      got:      " << a << endl; }
        // { Array<int> a; a.add(1); a.add(2); a.add(3); a.remove(10); cout << "  remove(10) with size 3\n      expected: silently removes the last element\n      got:      " << a << endl; }
        // ---- INVALID INPUTS END ----
    }

    // ===============================================================
    // OrderedArray.h - topic: game leaderboard
    // ===============================================================
    section("OrderedArray (game leaderboard)");
    {
        OrderedArray<int> board;
        board.insert(50);
        board.insert(90);
        board.insert(70);
        show("insert(50), insert(90), insert(70) stays sorted", "[ 50 70 90 ]", board);
        show("find(70) (binary search)", "1", board.find(70));
        show("find(10) not present", "-1", board.find(10));
        show("findMax()", "90", board.findMax());
        show("Array::findMax() through the base class", "90", board.Array<int>::findMax());
        board.insert(80, 0);
        show("insert(80, 0) - the index 0 is ignored, 80 is sorted in", "[ 50 70 80 90 ]", board);

        // inherited methods
        show("length() (inherited)", "4", board.length());
        show("len() (inherited)", "4", board.len());
        show("read(2) (inherited)", "80", board.read(2));
        show("findMin() (inherited)", "50", board.findMin());
        board.swap(0, 3);
        show("swap(0, 3) (inherited)", "[ 90 70 80 50 ]", board);
        board.simpleSwap(0, 3);
        show("simpleSwap(0, 3) (inherited)", "[ 50 70 80 90 ]", board);
        OrderedArray<int> other;
        other.insert(1);
        Array<int>::swap(board, 0, other, 0);
        show("static swap(board, 0, other, 0) - board", "[ 1 70 80 90 ]", board);
        show("static swap(board, 0, other, 0) - other", "[ 50 ]", other);
        board.remove();
        show("remove() (inherited)", "[ 1 70 80 ]", board);
        board.remove(0);
        show("remove(0) (inherited)", "[ 70 80 ]", board);
        board.add(60);
        show("add(60) (inherited) is NOT sorted in", "[ 70 80 60 ]", board);
        board.bubbleSort();
        show("bubbleSort() (inherited)", "[ 60 70 80 ]", board);
        board.add(10);
        board.selectionSort();
        show("add(10), selectionSort() (inherited)", "[ 10 60 70 80 ]", board);
        board + 65;
        show("board + 65 (inherited, uses the sorted insert)", "[ 10 60 65 70 80 ]", board);
        show("board + other (inherited, plain concatenation)", "[ 10 60 65 70 80 50 ]", board + other);
        board.resize();
        show("resize() (inherited) keeps the values", "[ 10 60 65 70 80 ]", board);

        cout << "\n  -- invalid inputs (commented out, remove the // to run one) --" << endl;
        // ---- INVALID INPUTS START ----
        // { OrderedArray<int> a; cout << "  findMax() on empty array\n      expected: reads data[-1] (undefined)\n      got:      " << a.findMax() << endl; }
        // ---- INVALID INPUTS END ----
    }

    // ===============================================================
    // Map.h - topic: phone book
    // ===============================================================
    section("Map (phone book)");
    {
        Map<string, string> phoneBook;
        phoneBook.add("Alice", "555-0101");
        phoneBook.add("Bob", "555-0102");
        phoneBook.add("Carol", "555-0103");
        show("get(\"Alice\")", "555-0101", phoneBook.get("Alice").value_or("none"));
        show("get(\"Zed\") not present", "none", phoneBook.get("Zed").value_or("none"));
        show("isKey(\"Bob\")", "true", phoneBook.isKey("Bob"));
        show("isKey(\"Zed\")", "false", phoneBook.isKey("Zed"));
        phoneBook.add("Alice", "555-9999");
        show("add(\"Alice\", ...) again updates the value", "555-9999", phoneBook.get("Alice").value_or("none"));
        show("size after the update", "3", phoneBook.size);
        cout << "  display() - expected: 10 rows (index : pairs), 3 pairs in total" << endl;
        phoneBook.display();

        // other key types use different hash functions (capacity is 10)
        Map<int, string> byNumber;
        show("hash(-3) int", "7", byNumber.hash(-3));
        Map<char, int> byLetter;
        show("hash('A') char", "5", byLetter.hash('A'));
        Map<double, string> byPrice;
        show("hash(1.5) double", "0", byPrice.hash(1.5));

        // growing past 70% full triggers a resize
        phoneBook.add("Dave", "555-0104");
        phoneBook.add("Erin", "555-0105");
        phoneBook.add("Frank", "555-0106");
        phoneBook.add("Grace", "555-0107");
        show("capacity before the 8th add", "10", phoneBook.capacity);
        phoneBook.add("Heidi", "555-0108");
        show("capacity after the 8th add (resize)", "20", phoneBook.capacity);
        show("size", "8", phoneBook.size);
        show("get(\"Heidi\") after resize", "555-0108", phoneBook.get("Heidi").value_or("none"));
        show("get(\"Alice\") after resize", "555-9999", phoneBook.get("Alice").value_or("none"));

        Map<string, string> copy(phoneBook);
        copy.add("Zed", "555-0000");
        show("copy constructor, add to the copy - isKey(\"Zed\") on copy", "true", copy.isKey("Zed"));
        show("copy constructor - isKey(\"Zed\") on original", "false", phoneBook.isKey("Zed"));
        Map<string, string> assigned;
        assigned = phoneBook;
        assigned.add("Yan", "555-0001");
        show("copy assignment, add to the copy - isKey(\"Yan\") on copy", "true", assigned.isKey("Yan"));
        show("copy assignment - isKey(\"Yan\") on original", "false", phoneBook.isKey("Yan"));

        cout << "\n  -- invalid inputs (commented out, remove the // to run one) --" << endl;
        // ---- INVALID INPUTS START ----
        // { Map<string, string> m(0); m.add("a", "b"); cout << "  Map(0) then add\n      expected: division by zero in the hash function (crash)\n      got size: " << m.size << endl; }
        // { Map<string, string> m(-1); cout << "  Map(-1)\n      expected: new[] with a negative size\n      got size: " << m.size << endl; }
        // { Map<double, string> m; cout << "  hash(1e10) double\n      expected: integer overflow (undefined)\n      got:      " << m.hash(1e10) << endl; }
        // { Map<double, string> m; cout << "  hash(NaN) double\n      expected: integer overflow (undefined)\n      got:      " << m.hash(nan("")) << endl; }
        // ---- INVALID INPUTS END ----
    }

    // ===============================================================
    // Ordered_map.h - topic: grocery prices
    // ===============================================================
    section("ordered_map (grocery prices)");
    {
        ordered_map<string, double> prices;
        prices.add("pear", 1.2);
        prices.add("apple", 0.5);
        prices.add("mango", 2.0);
        cout << "  display() - expected: (apple,0.5) (mango,2) (pear,1.2)" << endl;
        cout << "      got:      ";
        prices.display();
        show("get(\"mango\")", "2", prices.get("mango").value());
        show("get(\"kiwi\") not present", "none", prices.get("kiwi").has_value() ? "found" : "none");
        show("isKey(\"pear\")", "true", prices.isKey("pear"));
        show("isKey(\"kiwi\")", "false", prices.isKey("kiwi"));
        prices.add("apple", 0.75);
        show("add(\"apple\", 0.75) again updates the value", "0.75", prices.get("apple").value());
        show("size stays 3 after the update", "3", prices.store.len());
    }

    // ===============================================================
    // Stack.h - topic: browser history
    // ===============================================================
    section("Stack (browser history)");
    {
        Stack<string> history;
        history.push("home.com");
        history.push("news.com");
        history.push("mail.com");
        show("push 3 pages", "[ home.com news.com mail.com ]", history);
        show("read() shows the top", "mail.com", history.read());
        history.pop();
        show("pop() removes the top", "[ home.com news.com ]", history);
        show("read() after pop", "news.com", history.read());

        // inherited methods
        show("len() (inherited)", "2", history.len());
        show("length() (inherited)", "2", history.length());
        show("Array::read(0) (inherited, bottom of the stack)", "home.com", history.Array<string>::read(0));
        history.add("shop.com");
        show("add() (inherited)", "[ home.com news.com shop.com ]", history);
        history.insert("tv.com");
        show("insert(value) (inherited)", "[ home.com news.com shop.com tv.com ]", history);
        history.insert("bank.com", 1);
        show("insert(value, 1) (inherited, middle of the stack)", "[ home.com bank.com news.com shop.com tv.com ]", history);
        show("find(\"news.com\") (inherited)", "2", history.find("news.com"));
        show("find(\"x.com\") (inherited)", "-1", history.find("x.com"));
        show("findMax() (inherited)", "tv.com", history.findMax());
        show("findMin() (inherited)", "bank.com", history.findMin());
        history.swap(0, 4);
        show("swap(0, 4) (inherited)", "[ tv.com bank.com news.com shop.com home.com ]", history);
        history.simpleSwap(0, 4);
        show("simpleSwap(0, 4) (inherited)", "[ home.com bank.com news.com shop.com tv.com ]", history);
        Stack<string> other;
        other.push("x.com");
        Array<string>::swap(history, 0, other, 0);
        show("static swap(history, 0, other, 0) - history", "[ x.com bank.com news.com shop.com tv.com ]", history);
        show("static swap(history, 0, other, 0) - other", "[ home.com ]", other);
        history.bubbleSort();
        show("bubbleSort() (inherited)", "[ bank.com news.com shop.com tv.com x.com ]", history);
        history.swap(0, 4);
        history.selectionSort();
        show("swap(0, 4), selectionSort() (inherited)", "[ bank.com news.com shop.com tv.com x.com ]", history);
        history.remove(1);
        show("remove(1) (inherited)", "[ bank.com shop.com tv.com x.com ]", history);
        history.remove();
        show("remove() (inherited)", "[ bank.com shop.com tv.com ]", history);
        show("history + other (inherited)", "[ bank.com shop.com tv.com home.com ]", history + other);
        history + string("last.com");
        show("history + \"last.com\" (inherited)", "[ bank.com shop.com tv.com last.com ]", history);
        history.resize();
        show("resize() (inherited) keeps the values", "[ bank.com shop.com tv.com last.com ]", history);

        cout << "\n  -- invalid inputs (commented out, remove the // to run one) --" << endl;
        // ---- INVALID INPUTS START ----
        // { Stack<int> s; s.pop(); cout << "  pop() on empty stack\n      expected: size becomes -1\n      got len:  " << s.len() << endl; }
        // { Stack<int> s; cout << "  read() on empty stack\n      expected: reads data[-1] (undefined)\n      got:      " << s.read() << endl; }
        // ---- INVALID INPUTS END ----
    }

    // ===============================================================
    // Queue.h - topic: code review queue (uses Linter)
    // ===============================================================
    section("Queue (code review queue, checked with Linter)");
    {
        Queue<string> reviews;
        reviews.enqueue("int main() { return 0; }");
        reviews.enqueue("if (x > 0 { y = 1; }");
        reviews.enqueue("int a[3] = {1, 2, 3};");
        show("len() after 3 enqueues", "3", reviews.len());
        show("read() shows the front", "int main() { return 0; }", reviews.read());

        Linter linter;
        string expectedResult[3] = {"true", "false", "true"};
        int next = 0;
        while (reviews.len() > 0) {
            string code = reviews.read();
            show("dequeue and lint: " + code, expectedResult[next], linter.lint(code));
            reviews.dequeue();
            next++;
        }
        show("len() after all reviews are done", "0", reviews.len());

        // inherited methods
        reviews.enqueue("b.cpp");
        reviews.enqueue("c.cpp");
        reviews.enqueue("a.cpp");
        show("enqueue 3 files", "[ b.cpp c.cpp a.cpp ]", reviews);
        show("length() (inherited)", "3", reviews.length());
        show("Array::read(2) (inherited)", "a.cpp", reviews.Array<string>::read(2));
        reviews.add("d.cpp");
        show("add() (inherited)", "[ b.cpp c.cpp a.cpp d.cpp ]", reviews);
        reviews.insert("e.cpp");
        show("insert(value) (inherited)", "[ b.cpp c.cpp a.cpp d.cpp e.cpp ]", reviews);
        reviews.insert("f.cpp", 1);
        show("insert(value, 1) (inherited, middle of the queue)", "[ b.cpp f.cpp c.cpp a.cpp d.cpp e.cpp ]", reviews);
        show("find(\"a.cpp\") (inherited)", "3", reviews.find("a.cpp"));
        show("find(\"z.cpp\") (inherited)", "-1", reviews.find("z.cpp"));
        show("findMax() (inherited)", "f.cpp", reviews.findMax());
        show("findMin() (inherited)", "a.cpp", reviews.findMin());
        reviews.swap(0, 5);
        show("swap(0, 5) (inherited)", "[ e.cpp f.cpp c.cpp a.cpp d.cpp b.cpp ]", reviews);
        reviews.simpleSwap(0, 5);
        show("simpleSwap(0, 5) (inherited)", "[ b.cpp f.cpp c.cpp a.cpp d.cpp e.cpp ]", reviews);
        Queue<string> other;
        other.enqueue("x.cpp");
        Array<string>::swap(reviews, 0, other, 0);
        show("static swap(reviews, 0, other, 0) - reviews", "[ x.cpp f.cpp c.cpp a.cpp d.cpp e.cpp ]", reviews);
        show("static swap(reviews, 0, other, 0) - other", "[ b.cpp ]", other);
        reviews.bubbleSort();
        show("bubbleSort() (inherited)", "[ a.cpp c.cpp d.cpp e.cpp f.cpp x.cpp ]", reviews);
        reviews.swap(0, 5);
        reviews.selectionSort();
        show("swap(0, 5), selectionSort() (inherited)", "[ a.cpp c.cpp d.cpp e.cpp f.cpp x.cpp ]", reviews);
        reviews.remove(1);
        show("remove(1) (inherited)", "[ a.cpp d.cpp e.cpp f.cpp x.cpp ]", reviews);
        reviews.remove();
        show("remove() (inherited)", "[ a.cpp d.cpp e.cpp f.cpp ]", reviews);
        show("reviews + other (inherited)", "[ a.cpp d.cpp e.cpp f.cpp b.cpp ]", reviews + other);
        reviews + string("g.cpp");
        show("reviews + \"g.cpp\" (inherited)", "[ a.cpp d.cpp e.cpp f.cpp g.cpp ]", reviews);
        reviews.resize();
        show("resize() (inherited) keeps the values", "[ a.cpp d.cpp e.cpp f.cpp g.cpp ]", reviews);

        cout << "\n  -- invalid inputs (commented out, remove the // to run one) --" << endl;
        // ---- INVALID INPUTS START ----
        // { Queue<int> q; q.dequeue(); cout << "  dequeue() on empty queue\n      expected: size becomes -1\n      got len:  " << q.len() << endl; }
        // { Queue<int> q; cout << "  read() on empty queue\n      expected: uninitialized data[0]\n      got:      " << q.read() << endl; }
        // ---- INVALID INPUTS END ----
    }

    // ===============================================================
    // Linter.h - topic: checking brackets in code
    // ===============================================================
    section("Linter (checking brackets in code)");
    {
        Linter linter;
        show("lint \"{[()]}\" nested and closed", "true", linter.lint("{[()]}"));
        show("lint \"([)]\" wrong closing order", "false", linter.lint("([)]"));
        show("lint \"(((\" never closed", "false", linter.lint("((("));
        show("lint \"}\" closing with nothing open", "false", linter.lint("}"));
        show("lint \"\" empty text", "true", linter.lint(""));
        show("lint \"int a[2] = {1, 2};\" real code", "true", linter.lint("int a[2] = {1, 2};"));
        show("lint \"()\" after a failed call (state is cleared)", "true", linter.lint("()"));
    }

    // ===============================================================
    // LinkedList.h - topic: sports
    // ===============================================================
    section("LinkedList (sports)");
    {
        LinkedList<string> sports;
        sports.insert("football", 0);
        sports.insert("soccer", 1);
        sports.insert("baseball", 2);
        sports.insert("basketball", 3);
        sports.insert("lacrosse", 4);
        sports.insert("golf", 5);
        sports.insert("bowling", 6);
        cout << "  print() - expected: [ football soccer baseball basketball lacrosse golf bowling  ]" << endl;
        cout << "      got:      ";
        sports.print();
        show("search(\"baseball\")", "baseball", sports.search("baseball")->value);
        show("search(\"curling\") not present", "true", sports.search("curling") == nullptr);
        show("read(2)", "baseball", sports.read(2));

        sports.insert("tennis", 2);
        cout << "  insert(\"tennis\", 2) - expected: [ football soccer tennis baseball basketball lacrosse golf bowling  ]" << endl;
        cout << "      got:      ";
        sports.print();
        sports.remove(1);
        cout << "  remove(1) - expected: [ football tennis baseball basketball lacrosse golf bowling  ]" << endl;
        cout << "      got:      ";
        sports.print();
        sports.remove(0);
        cout << "  remove(0) - expected: [ tennis baseball basketball lacrosse golf bowling  ]" << endl;
        cout << "      got:      ";
        sports.print();
        sports.removeValue("golf");
        cout << "  removeValue(\"golf\") - expected: [ tennis baseball basketball lacrosse bowling  ]" << endl;
        cout << "      got:      ";
        sports.print();
        sports.removeValue("curling");
        cout << "  removeValue(\"curling\") not present - expected: [ tennis baseball basketball lacrosse bowling  ]" << endl;
        cout << "      got:      ";
        sports.print();

        LinkedList<string> single("hockey");
        cout << "  LinkedList(\"hockey\") constructor - expected: [ hockey  ]" << endl;
        cout << "      got:      ";
        single.print();

        cout << "\n  -- invalid inputs (commented out, remove the // to run one) --" << endl;
        // ---- INVALID INPUTS START ----
        // { LinkedList<string> t; t.insert("a", 0); t.insert("b", 1); cout << "  read(-1)\n      expected: returns the head value (a)\n      got:      " << t.read(-1) << endl; }
        // { LinkedList<string> t; t.insert("a", 0); cout << "  read(5) with 1 element\n      expected: null pointer dereference (crash)\n      got:      " << t.read(5) << endl; }
        // { LinkedList<string> t; cout << "  read(0) on empty list\n      expected: null pointer dereference (crash)\n      got:      " << t.read(0) << endl; }
        // { LinkedList<string> t; t.insert("a", 0); t.insert("b", 1); t.insert("front", -5); cout << "  insert(\"front\", -5)\n      expected: inserted at the front [ front a b  ]\n      got:      "; t.print(); }
        // { LinkedList<string> t; t.insert("a", 0); t.insert("b", 1); t.insert("end", 99); cout << "  insert(\"end\", 99)\n      expected: appended at the end [ a b end  ]\n      got:      "; t.print(); }
        // { LinkedList<string> t; t.remove(0); cout << "  remove(0) on empty list\n      expected: null pointer dereference (crash)\n      got:      "; t.print(); }
        // { LinkedList<string> t; t.insert("a", 0); t.remove(5); cout << "  remove(5) with 1 element\n      expected: null pointer dereference (crash)\n      got:      "; t.print(); }
        // { LinkedList<string> t; t.insert("a", 0); t.insert("b", 1); t.insert("c", 2); t.remove(-1); cout << "  remove(-1)\n      expected: ignored, list unchanged [ a b c  ]\n      got:      "; t.print(); }
        // { LinkedList<string> t; t.insert("a", 0); t.insert("b", 1); t.insert("c", 2); t.remove(-2); cout << "  remove(-2)\n      expected: removes the second node [ a c  ]\n      got:      "; t.print(); }
        // ---- INVALID INPUTS END ----
    }

    // ===============================================================
    // DoubleLinkedList.h (class List) - topic: music playlist
    // ===============================================================
    section("List / DoubleLinkedList (music playlist)");
    {
        List<string> playlist;
        playlist.insert("Imagine");
        playlist.insert("Hello");
        playlist.insert("Respect");
        cout << "  insert(value) x3 - expected: [ Imagine Hello Respect  ]" << endl;
        cout << "      got:      ";
        playlist.print();
        playlist.insert("Yesterday", 1);
        cout << "  insert(\"Yesterday\", 1) - expected: [ Imagine Yesterday Hello Respect  ]" << endl;
        cout << "      got:      ";
        playlist.print();
        playlist.insert("Intro", 0);
        cout << "  insert(\"Intro\", 0) - expected: [ Intro Imagine Yesterday Hello Respect  ]" << endl;
        cout << "      got:      ";
        playlist.print();
        show("read(2)", "Yesterday", playlist.read(2));
        show("search(\"Hello\")", "Hello", playlist.search("Hello")->value);
        show("search(\"Missing\") not present", "true", playlist.search("Missing") == nullptr);

        playlist.remove(0);
        cout << "  remove(0) head - expected: [ Imagine Yesterday Hello Respect  ]" << endl;
        cout << "      got:      ";
        playlist.print();
        playlist.remove(3);
        cout << "  remove(3) tail - expected: [ Imagine Yesterday Hello  ]" << endl;
        cout << "      got:      ";
        playlist.print();
        playlist.remove(1);
        cout << "  remove(1) middle - expected: [ Imagine Hello  ]" << endl;
        cout << "      got:      ";
        playlist.print();
        playlist.removeValue("Hello");
        cout << "  removeValue(\"Hello\") - expected: [ Imagine  ]" << endl;
        cout << "      got:      ";
        playlist.print();
        playlist.removeValue("Nope");
        cout << "  removeValue(\"Nope\") not present - expected: [ Imagine  ]" << endl;
        cout << "      got:      ";
        playlist.print();

        cout << "\n  -- invalid inputs (commented out, remove the // to run one) --" << endl;
        // ---- INVALID INPUTS START ----
        // { List<string> t; cout << "  read(0) on empty list\n      expected: null pointer dereference (crash)\n      got:      " << t.read(0) << endl; }
        // { List<string> t; t.insert("a"); t.insert("b"); cout << "  read(-1)\n      expected: returns the head value (a)\n      got:      " << t.read(-1) << endl; }
        // { List<string> t; t.insert("a"); t.insert("b"); cout << "  read(99)\n      expected: returns an empty string (TYPE())\n      got:      \"" << t.read(99) << "\"" << endl; }
        // { List<string> t; t.insert("a"); t.insert("b"); t.insert("front", -3); cout << "  insert(\"front\", -3)\n      expected: inserted at the front [ front a b  ]\n      got:      "; t.print(); }
        // { List<string> t; t.insert("a"); t.insert("b"); t.insert("back", 99); cout << "  insert(\"back\", 99)\n      expected: appended at the back [ a b back  ]\n      got:      "; t.print(); }
        // { List<string> t; t.insert("a"); t.insert("b"); t.insert("c"); t.remove(-5); cout << "  remove(-5)\n      expected: removes the head [ b c  ]\n      got:      "; t.print(); }
        // { List<string> t; t.insert("a"); t.insert("b"); t.insert("c"); t.remove(99); cout << "  remove(99)\n      expected: removes the tail [ a b  ]\n      got:      "; t.print(); }
        // ---- INVALID INPUTS END ----
    }

    //
    // =============================================================== Tree.h - topic: contact names in alphabetical order ===============================================================
    section("Tree (contact names in alphabetical order)");
    {
        Tree<string> names;
        names.insert("Mia");
        names.insert("Liam");
        names.insert("Zoe");
        names.insert("Ava");
        names.insert("Noah");
        show("search + children of Mia (root)", "Mia: left=Liam right=Zoe", describe(names, "Mia"));
        show("search + children of Liam", "Liam: left=Ava right=none", describe(names, "Liam"));
        show("search + children of Zoe", "Zoe: left=Noah right=none", describe(names, "Zoe"));
        show("search + children of Ava", "Ava: left=none right=none", describe(names, "Ava"));
        show("search for \"Bob\" not present", "Bob: not found", describe(names, "Bob"));
        names.insert("Ava");
        show("insert a duplicate \"Ava\" - it goes to the right of the first Ava", "Ava: left=none right=Ava", describe(names, "Ava"));

        Tree<string> empty;
        show("search on an empty tree", "Mia: not found", describe(empty, "Mia"));
    }

    return 0;
}