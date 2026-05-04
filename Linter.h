#ifndef DATASTRUCTURE_LINTER_H
#define DATASTRUCTURE_LINTER_H

#include<iostream>
#include<string>
#include"Map.h"
#include"Stack.h"

using namespace std;

class Linter {
private:
    Map<char, char> matches;
    Stack<char> seen;

public:
    Linter(){
        matches.add('}','{');
        matches.add(']','[');
        matches.add(')','(');
    }

    bool lint(string code) {
        bool result;
        for (int i = 0; i < code.size(); i++) {
            if (code[i] == '{' || code[i] == '[' || code[i] == '('){
                this->seen.push(code[i]);
            }
            if (code[i] == '}' || code[i] == ']' || code[i] == ')'){
                result = this->matches.get(code[i]) == this->seen.read();
                this->seen.pop();
                if (!result) {
                    return false;
                }
            }
        }
        return true;
    }
};



#endif //DATASTRUCTURE_LINTER_H
