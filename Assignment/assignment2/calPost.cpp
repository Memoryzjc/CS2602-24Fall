#include<iostream>

class outOfBound{};

template<typename elemType>
class linkStack;

template<typename elemType>
class Node
{
friend class linkStack<elemType>;
private:
    elemType data;
    Node *next;
public:
    Node() {
        next = nullptr;
    };
    Node(const elemType &x, Node *p = nullptr) {
        data = x;
        next = p;
    }
};

template<typename elemType>
class linkStack
{
private:
    Node<elemType> *Top;
public:
    linkStack() {
        Top = nullptr;
    }
    bool isEmpty() {
        return Top == nullptr;
    }
    bool isFull() {
        return false;
    }
    elemType top() {
        if (!this->Top) {
            throw outOfBound();
        }

        return this->Top->data;
    }
    void push(const elemType &e) {
        this->Top = new Node<elemType>(e, this->Top);
    }
    void pop() {
        Node<elemType> *temp = this->Top;
        
        if (!this->Top) {
            throw outOfBound();
        }

        this->Top = this->Top->next;
        delete temp;
    }
    ~linkStack() {
        Node<elemType> *tmp;

        while(this->Top) {
            tmp = this->Top;
            this->Top = Top->next;
            delete tmp;
        }
    }
};

int main() {
    int op1, op2, op = 0, flag = 1;
    linkStack<int> s, numStack;
    char input;

    while(std::cin.get(input) && input != '@') {
        switch(input) {
            case '.':
                op = 0;
                flag = 1;

                while(!s.isEmpty()) {
                    op += flag * s.top();
                    s.pop();
                    flag *= 10;
                }

                numStack.push(op);

                op = 0;
                flag = 1;
                break;
            case '+':
                op1 = numStack.top();
                numStack.pop();
                op2 = numStack.top();
                numStack.pop();
                op = op1 + op2;
                numStack.push(op);
                break;
            case '-':
                op1 = numStack.top();
                numStack.pop();
                op2 = numStack.top();
                numStack.pop();
                op = op2 - op1;
                numStack.push(op);
                break;
            case '*':
                op1 = numStack.top();
                numStack.pop();
                op2 = numStack.top();
                numStack.pop();
                op = op1 * op2;
                numStack.push(op);
                break;
            case '/':
                op1 = numStack.top();
                numStack.pop();
                op2 = numStack.top();
                numStack.pop();
                op = op2 / op1;
                numStack.push(op);
                break;
            default:
                s.push(input - '0');
                break;
        }
    }

    std::cout << numStack.top();

    return 0;
}