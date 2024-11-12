#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

class illegalSize{};
class outOfBound{};

template<typename elemType>
class priorityQueue
{
private:
    elemType *array;
    int maxSize, currentLen;
    void doubleSpace()
    {
        elemType *tmp = this->array;
        this->array = new elemType[2 * maxSize];

        if (!this->array) {
            throw illegalSize();
        }

        for (int i = 0; i < maxSize; i++) {
            this->array[i] = tmp[i];
        }
        
        maxSize *= 2;
        delete []tmp;
    }

    void adjust(int hole)
    {
        int minChild;
        elemType x = this->array[hole];

        while(true) {
            // the left child of hole
            minChild = 2 * hole;
            if (minChild > currentLen) {
                break;
            }

            if (minChild + 1 <= currentLen) {
                if (this->array[minChild + 1] < this->array[minChild]) {
                    minChild++; // the right child is smallest
                }
            }

            if (x < this->array[minChild]) {
                break;
            }

            this->array[hole] = array[minChild];
            hole = minChild;  // continue adjusting downwards
        }

        this->array[hole] = x;

    }

    void build(int r)
    {
        if (r > currentLen / 2) {
            return;
        }

        build(2 * r);
        build(2 * r + 1);
        adjust(r);
    }

public:
    priorityQueue(int size=10) 
    {
        this->array = new elemType[size];

        if (!this->array) {
            throw illegalSize();
        }

        this->maxSize = size;
        currentLen = 0;
    }

    priorityQueue(elemType a[], int n)
    {
        if (n < 1) {
            throw illegalSize();
        }

        this->array = new elemType[n + 10];

        if (!this->array) {
            throw illegalSize();
        }

        this->maxSize = n + 10;
        this->currentLen = n;
        // for (int i = 1; i <= n; i++) {
        //     this->array[i] = a[i - 1];
        // }

        // // 
        // for (int i = n / 2; i >= 1; i--) {
        //     adjust(i);
        // }
        for (int i = 0; i < n; i++) 
        {
            this->array[i + 1] = a[i];
        }
        build(1);
    }

    bool isEmpty()
    {
        return currentLen == 0;
    }

    bool isFull() 
    {
        return currentLen == maxSize - 1;
    }

    elemType front() const
    {
        if (isEmpty()) {
            throw outOfBound();
        }

        return this->array[1];
    }

    void enQueue(const elemType &x)
    {
        if (isFull()) {
            doubleSpace();
        }
        
        int hole;
        currentLen++;

        for (hole = currentLen; hole > 1 && x < this->array[hole / 2]; hole /= 2) {
            this->array[hole] = this->array[hole / 2];
        }
        this->array[hole] = x;
    }

    void deQueue()
    {
        if (isEmpty()) {
            throw outOfBound();
        }

        this->array[1] = array[currentLen];
        currentLen--;
        adjust(1);
    }

    ~priorityQueue()
    {
        delete []array;
    }
}