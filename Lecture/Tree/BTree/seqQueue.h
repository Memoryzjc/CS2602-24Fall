#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED

class illegalSize{};
class outOfBound{};

template<typename elemType>
class seqQueue
{
private:
    elemType *array;
    int maxSize;
    int Front, Rear;
    void doubleSpace();

public:
    seqQueue(int size=10);
    bool isEmpty();
    bool isFull();
    elemType front();
    void enQueue(const elemType & x);
    void deQueue();
    ~seqQueue();
};

template<typename elemType>
void seqQueue<elemType>::doubleSpace() {
    elemType *newArray;
    int i, j;

    newArray = new elemType[2 * maxSize];
    if (!newArray) {
        throw illegalSize();
    }

    for (i = 0, j = this->Front; j != Rear; i++, j = (j + 1) % this->maxSize) {
        newArray[i] = this->array[j];
    }

    delete []array;
    this->array = newArray;

    this->Front = 0;
    this->Rear = j;
    this->maxSize *= 2;
}

template<typename elemType>
seqQueue<elemType>::seqQueue(int size) {
    this->array = new elemType[size];
    if (!this->array) {
        throw illegalSize();
    }

    this->Front = 0;
    this->Rear = 0;
    this->maxSize = size;
}

template<typename elemType>
bool seqQueue<elemType>::isEmpty() {
    return this->Front == this->Rear;
}

template<typename elemType>
bool seqQueue<elemType>::isFull() {
    return this->Front == (this->Rear + 1) % this->maxSize;
}

template<typename elemType>
elemType seqQueue<elemType>::front() {
    // must check whether the queue is empty
    if (this->isEmpty()) {
        throw outOfBound();
    }

    return this->array[this->Front];
}

template<typename elemType>
void seqQueue<elemType>::enQueue(const elemType &x) {
    // check is full or not
    if (this->isFull()) {
        this->doubleSpace();
    }

    this->array[this->Rear] = x;
    this->Rear = (this->Rear + 1) % this->maxSize;  // for circularity
}

template<typename elemType>
void seqQueue<elemType>::deQueue() {
    // check is empty or not
    if (this->isEmpty()) {
        throw outOfBound();
    }

    this->Front = (this->Front + 1) % this->maxSize;
}

template<typename elemType>
seqQueue<elemType>::~seqQueue() {
    delete []array;
}

#endif  // SEQQUEUE_H_INCLUDED