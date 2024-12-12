#include <iostream>
#include <string>
#include <stack>

using namespace std;

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(string infix) {
    string postfix = "";
    stack<char> ops;
    string num = "";
    
    for (char c : infix) {
        if (isdigit(c)) {
            num += c;
        } 
        else if (c == '.') {
            postfix += num + ".";
            num = "";
        }
        else if (c == '(') {
            ops.push(c);
        }
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                postfix += ops.top();
                ops.pop();
            }
            if (!ops.empty()) {
                ops.pop();
            }
        }
        else if (c == '@') {
            while (!ops.empty()) {
                postfix += ops.top();
                ops.pop();
            }
            postfix += "@";
        }
        else {
            while (!ops.empty() && ops.top() != '(' && 
                   getPriority(ops.top()) >= getPriority(c)) {
                postfix += ops.top();
                ops.pop();
            }
            ops.push(c);
        }
    }
    
    return postfix;
}

int main() {
    string infix;
    getline(cin, infix);
    cout << infixToPostfix(infix) << endl;
    return 0;
}