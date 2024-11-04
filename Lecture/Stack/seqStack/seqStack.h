#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED

class illegalSize{};
class outOfBound{};

template<typename elemType>
class seqStack
{
private:
    elemType *array;  // hold the data element
    int Top;  // denote the top of the stack
    int maxSize;  // the maximum number of the data stored in stack
    void doubleSpace() 
    { 
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
    // initialize sequential stack
    seqStack(int initSize = 100)
    {
        this->array = new elemType[initSize];
        if (!array) {
            throw illegalSize();
        }
        this->Top = -1;
        this->maxSize = initSize;
    }

    // if the stack is empty return true and false otherwise
    bool isEmpty() 
    {
        return Top == -1;
    }  

    // if the stack is full return true and false otherwise
    bool isFull() 
    {
        return Top == maxSize - 1;
    }  
    
    // return the value of the top element and doesn't change the top of stack
    elemType top() 
    {
        if (this->isEmpty()) {
            throw outOfBound();
        }
        return this->array[this->Top];
    }
    
    // push the element e into the stack
    void push(const elemType &e)
    {
        if (this->isFull()) {
            this->doubleSpace();
        }
        
        this->array[++this->Top] = e;
    } 
    
    // pop the element of the top of the stack
    void pop()
    {
        if (this->isEmpty()) {
            throw illegalSize();
        }

        this->Top--;
    }
    
    // free the dynamic array
    ~seqStack() 
    {
        delete []array;
    };  
};

#endif  // SEQSTACK_H_INCLUDED