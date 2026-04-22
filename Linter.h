#ifndef DATASTRUCTURE_LINTER_H
#define DATASTRUCTURE_LINTER_H
#include<iostream>
#include<string>
#include"Map.h"
#include "Stack.h"

using namespace std;

class Linter {
    Map<char, char> matches;
    Stack<char> seen;

public:
    Linter() {
        matches.add('}','{');
        matches.add(']','[');
        matches.add(')','(');
        matches.add('"','"');
    }

    bool lint(string code) {
        for (int i = 0; i < code.size(); i++) {
            if (code[i] == '{' || code[i] == '[' || code[i] == '(' || code [i] == '"') {
                this->seen.push(code[i]);
            }
            else if (code[i] == '}' || code[i] == ']' || code[i] == ')' || code[i] == '"') {
            }
        }
    }
};



#endif //DATASTRUCTURE_LINTER_H
