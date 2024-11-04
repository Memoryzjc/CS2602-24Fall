#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED

class illegalSize{};
class outOfBound{};

template<typename elemType>
class linkQueue;

template<typename elemType>
class Node
{
friend class linkQueue<elemType>;
private:
    elemType data;
    Node *next;
public:
    Node() {
        this->next = nullptr;
    }
    Node(const elemType &x, Node *p=nullptr) {
        this->data = x;
        this->next = p;
    }
};

template<typename elemType>
class linkQueue
{
private:
    Node<elemType> *Front, *Rear;
public:
    linkQueue();
    bool isEmpty();
    bool isFull();
    elemType front();
    void enQueue(const elemType &x);
    void deQueue();
    ~linkQueue();
}

template<typename elemType>
linkQueue<elemType>::linkQueue() {
    this->Front = this->Rear = nullptr;
}

template<typename elemType>
bool linkQueue<elemType>::isEmpty() {
    return !this->Front;
}

template<typename elemType>
bool linkQueue<elemType>::isFull() {
    return false;
}

template<typename elemType>
elemType linkQueue<elemType>::front() {
    if (this->isEmpty()) {
        throw outOfBound();
    }

    return this->Front->data;
}

template<typename elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
    if (this->isFull()) {
        throw outOfBound();
    }

    if (!this->Rear) {
        this->Front = this->Rear = new Node<elemType>(x);
    } else {
        this->Rear->next = new Node<elemType>(x);
        this->Rear = this->Rear->next;
    }
}

template<typename elemType>
void linkQueue<elemType>::deQueue() {
    if (this->isEmpty()) {
        throw outOfBound();
    }

    Node<elemType> *tmp = this->Front;
    this->Front = this->Front->next;
    delete tmp;

    if(!this->Front) {
        this->Front = nullptr;
    }
}

template<typename elemType>
linkQueue<elemType>::~linkQueue() {
    Node<elemType> *p;
    p = this->Front;

    while(p) {
        this->Front = this->Front->next;
        delete p;
        p = this->Front;
    }
}

#endif  // LINKQUEUE_H_INCLUDED