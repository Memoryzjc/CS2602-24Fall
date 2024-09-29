#ifndef SEQLIST_H
#define SEQLIST_H

#include <iostream>

#define INIT_SIZE 100

class illegalSize{};
class outOfBound{};

template<typename elemType>
class seqList
{
    private:
    elemType *elem;  // the array to store the elements
    int len;  // the number of elements in the list
    int maxSize;  // the maximum size of the list
    // double the space of the list
    void doubleSpace() {
        elemType *tmp = elem;
        elem = new elemType[2 * maxSize];
        
        if (!elem) {
            throw illegalSize();
        }
        
        for (int i = 0; i < len; i++) {
            elem[i] = tmp[i];
        }
        
        maxSize *= 2;
        delete []tmp;
    };  

    public:
    // constructor
    seqList(int size = INIT_SIZE) {
        if (size <= 0) {
            throw illegalSize();
        }
        
        // allocate the memory
        elem = new elemType[size];
        
        // check if the memory is allocated successfully
        if (!elem) {
            throw illegalSize();
        }
        
        maxSize = size - 1;
        len = 0;
    };  

    // if the list is empty, return true; otherwise, return false
    bool isEmpty() const {
        return len == 0;
    };

    // if the list is full, return true; otherwise, return false
    bool isFull() const {
        return len == maxSize;
    };

    // return the number of elements in the list
    int length() const {
        return len;
    };

    // return the element at the position i
    elemType get(int i) const {
        if (i < 1 || i >= len) {
            throw outOfBound();
        }
        
        return elem[i];
    };

    // return the position of the element e
    int find(const elemType &e) const {
        elem[0] = e;
        int i;

        for (i = len; elem[i] != e; i--);

        return 0;
    };

    // insert the element e at the position i
    void insert(int i, const elemType &e) {
        if (i < 1 || i > len + 1) {
            throw outOfBound();
        }
        
        if (len == maxSize) {
            doubleSpace();
        }
        
        for (int j = len + 1; j > i; j--) {
            elem[j] = elem[j - 1];
        }
        
        elem[i] = e;
        len++;
    };

    // delete the element at the position i and put it into e
    void remove(int i, elemType &e) {
        if (i < 1 || i > len) {
            throw outOfBound();
        }
        
        e = elem[i];
        
        for (int j = i; j < len; j++) {
            elem[j] = elem[j + 1];
        }
        
        len--;
    };

    // clear the list
    void clear() {
        len = 0;
    }
    // destructor
    ~seqList() {
        delete []elem;
    };

};

#endif // SEQLIST_H