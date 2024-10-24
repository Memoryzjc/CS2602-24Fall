#include<iostream>

class illegalSize{};
class outOfBound{};

template<typename elemType>
class seqStack
{
private:
    elemType *array;  // hold the data element
    int Top;  // denote the top of the stack
    int maxSize;  // the maximum number of the data stored in stack
    void doubleSpace() { 
        elemType *tmp = array;
        array = new elemType[2 * maxSize];
        
        if (!array) {
            throw illegalSize();
        }
        
        for (int i = 0; i < maxSize; i++) {
            array[i] = tmp[i];
        }
        
        maxSize *= 2;
        delete []tmp;
    };
public:
    seqStack(int initSize = 100);  // initialize sequential stack

    bool isEmpty() {
        return Top == -1;
    }  // if the stack is empty return true and false otherwise

    bool isFull() {
        return Top == maxSize - 1;
    }  // if the stack is full return true and false otherwise
    
    elemType top();  // return the value of the top element and doesn't change the top of stack
    
    void push(const elemType &e);  // push the element e into the stack
    
    void pop();  // pop the element of the top of the stack
    
    ~seqStack() {
        delete []array;
    };  // free the dynamic array
};

template<typename elemType>
seqStack<elemType>::seqStack(int initSize)
{
    this->array = new elemType[initSize];
    if (!array) {
        throw illegalSize();
    }
    this->Top = -1;
    this->maxSize = initSize;
}

template<typename elemType>
elemType seqStack<elemType>::top() {
    if (this->isEmpty()) {
        throw outOfBound();
    }
    return this->array[this->Top];
}

template<typename elemType>
void seqStack<elemType>::push(const elemType &e) {
    if (this->isFull()) {
        this->doubleSpace();
    }
    
    this->array[++this->Top] = e;
}

template<typename elemType>
void seqStack<elemType>::pop() {
    if (this->isEmpty()) {
        throw illegalSize();
    }

    this->Top--;
}