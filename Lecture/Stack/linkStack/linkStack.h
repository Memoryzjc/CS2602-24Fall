#ifndef LINKSTACK_H_INCLUDED
#define LINKSTACK_H_INCLUDED

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
    elemType top();
    void push(const elemType &e);
    void pop();
    ~linkStack();
};

template<typename elemType>
elemType linkStack<elemType>::top() {
    if (!this->Top) {
        throw outOfBound();
    }

    return this->Top->data;
}

template<typename elemType>
void linkStack<elemType>::push(const elemType &e) {
    this->Top = new Node<elemType>(e, this->Top);
}

template<typename elemType>
void linkStack<elemType>::pop() {
    Node<elemType> *temp = this->Top;
    
    if (!this->Top) {
        throw outOfBound();
    }


    this->Top = this->Top->next;
    delete temp;
}

template<typename elemType>
linkStack<elemType>::~linkStack() {
    Node<elemType> *tmp;

    while(this->Top) {
        tmp = this->Top;
        this->Top = Top->next;
        delete tmp;
    }
}

#endif  \\ LINKSTACK_H_INCLUDED