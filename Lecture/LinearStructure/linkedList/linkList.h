#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>

class outOfBound{};

template<typename elemType>
class linkList;

template<typename elemType>
class node 
{
    friend class linkList<elemType>;

    private:
    elemType data;
    node *next;

    public:
    node():next(nullptr) {};
    node(const elemType &e, node *n = nullptr):data(e), next(n) {};
};

template<typename elemType>
class linkList
{
    private:
    node<elemType> *head;

    public:
    linkList() {
        head = new node<elemType>;
    };

    bool isEmpty() const {
        return head->next == nullptr;
    };

    bool isFull() const {
        return false;
    };

    int length() const {
        node<elemType> *p = head->next;
        int count = 0;

        while (p) {
            p = p->next;
            count++;
        }

        return count;
    };

    elemType get(int i) const {
        if (i < 1) {
            throw outOfBound();
        }

        node<elemType> *p = head->next;
        int count = 1;

        while (p != nullptr && count < i) {
            p = p->next;
            count++;
        }

        if (p == nullptr) {
            throw outOfBound();
        }

        return p->data;
    };

    int find(const elemType &e) const {
        node<elemType> *p = head->next;
        int count = 1;

        while (p != nullptr && p->data != e) {
            p = p->next;
            count++;
        }

        if (p == nullptr) {
            return 0;
        }

        return count;
    };

    void insert(int i, const elemType &e) {
        node<elemType> *p = head;
        int count = 0;

        if (i < 1) {
            return;
        }

        while (p != nullptr && count < i - 1) {
            p = p->next;
            count++;
        }

        if (p == nullptr) {
            return;
        }

        p->next = new node<elemType>(e, p->next);
    };

    void remove(int i, elemType &e) {
        if (i < 1) {
            return;
        }

        node<elemType> *p = head;
        int count = 0;

        while (p && count < i - 1) {
            p = p->next;
            count++;
        }

        if (!p) {
            return;
        }

        node<elemType> *q = p->next;

        if (!q) {
            return;
        }

        e = q->data;
        p->next = q->next;
        delete q;
    };

    void clear() {
        node<elemType> *p = head->next;
        node<elemType> *q;

        while (p != nullptr) {
            q = p->next;
            delete p;
            p = q;
        }

        head->next = nullptr;
    };

    void reverse() const {
        node<elemType> *p, *q;
        p = head->next;
        head->next = nullptr;

        while(p) {
            q = p->next;
            p->next = head->next;
            head->next = p;
            p = q;
        }
    }

    ~linkList() {
        clear();
        delete head;
    };
};


#endif // LINKLIST_H