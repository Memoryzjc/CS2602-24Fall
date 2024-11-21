#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include<iostream>
#include"seqQueue.h"

template<typename elemType>
class binarySearchTree;

template<typename elemType>
class Node
{
friend class binarySearchTree<elemType>;
private:
    elemType data;
    Node *left, *right;
    int factor;  // balance factor

public:
    Node() : left(nullptr), right(nullptr) {}
    Node(const elemType &x) : data(x), left(nullptr), right(nullptr) {}
    Node(const elemType &x, Node *l, Node *r) : data(x), left(l), right(r) {}
};


template<typename elemType>
class binarySearchTree
{
private:
    Node<elemType> *root;
    bool search(const elemType &x, Node<elemType> *t) const
    {
        if (!t) {
            return false;
        }

        if (x > t->data) {
            return search(x, t->right);
        } else if (x < t->data) {
            return search(x, t->left);
        } else {
            return true;
        }
    }
    // Note the t is passed by reference
    void insert(const elemType &x, Node<elemType> *&t)
    {
        if (!t) {
            t = new Node<elemType>;
            return;
        }

        if (x == t->data) {
            return;
        } else if (x < t->data) {
            insert(x, t->left);
        } else {
            insert(x, t->right);
        }
    }
    void remove(const elemType &x, Node<elemType> *&t)
    {
        if (!t) {
            return;
        }

        if (x < t->data) {
            remove(x, t->left);
        } else if (x > t->data) {
            remove(x, t->right);
        } else {
            if (!t->left && !t->right) {
                delete t;
                t = nullptr;
                return;
            } else if (!t->left || !t->right) {
                Node<elemType> *tmp;
                tmp = t;
                t = (t->left) ? t->left : t->right;
                delete tmp;
                return;
            } else {
                // two children
                Node<elemType> *p;
                p = t->right;

                // Choose the smallest node in the right child tree as substitute
                while (p->left) {
                    p = p->left;
                }

                t->data = p->data;
                // p is not reference, if delete p directly,
                // the parent of p will get a deleted pointer instead of nullptr
                remove(p->data, t->right);
            }
        }
    }

public:
    binarySearchTree() : root(nullptr) {}
    bool search(const elemType &x) const
    {
        if (!this->root) {
            return false;
        }

        Node<elemType> *p = this->root;
        while (p) {
            if (p->data == x) {
                return true;
            } else {
                if (p->data < x) {
                    p = p->right;
                } else {
                    p = p->left;
                }
            }
        }

        return false;
    }
    void insert(const elemType &x)
    {
        Node<elemType> *p;
        if (!this->root) {
            this->root = new Node<elemType>(x);
            return;
        }

        p = this->root;
        while (p) {
            if (x == p->data) {
                // already in the tree
                return;
            }

            if (x < p->data) {
                if (!p->left) {
                    p->left = new Node<elemType>(x);
                    return;
                }
                p = p->left;
            } else {
                if (!p->right) {
                    p->right = new Node<elemType>(x);
                    return;
                }
                p = p->right;
            }
        }
    }
    // {
    //     Node<elemType> *p, *tmp, *parent = nullptr;
    //     int flag;

    //     p = this->root;

    //     while(p) {
    //         if (x == p->data) {
    //             return;
    //         }

    //         parent = p;
    //         if (x < p->data) {
    //             flag = 0;
    //             p = p->left;
    //         } else {
    //             flag = 1;
    //             p = p->right;
    //         }
    //     }

    //     tmp = new Node<elemType>(x);
    //     if (!parent) {
    //         this->root = tmp;
    //     }

    //     if (flag == 0) {
    //         parent->left = tmp;
    //     } else {
    //         parent->right = tmp
    //     }
    // }
    void remove (const elemType &x)
    {
        if (!this->root) {
            return;
        }

        Node<elemType> *p, *parent;
        int flag;  // flag == 0: p = parent's right child; flag == 1: left child

        p = this->root;
        parent = nullptr;

        while (p) {
            if (x < p->data) {
                parent = p;
                p = p->left;
                flag = 0;
                continue;
            } else if (x > p->data) {
                parent = p;
                p = p->right;
                flag = 1;
                continue;
            } else {
                // Begin delete
                if (!p->right && !p->left) {
                    // leaf node
                    delete p;
                    
                    if (!parent) {
                        this->root = nullptr;
                        return;
                    } else {
                        if (flag == 0) {
                            parent->left = nullptr;
                        } else {
                            parent->right = nullptr;
                        }
                        return;
                    }
                } else if (!p->left || !p->right) {
                    // has one child
                    Node<elemType> *tmp = p;
                    
                    if (!parent) {
                        this->root = (p->left) ? p->left : p->right;
                    } else {
                        if (flag == 0) {
                            parent->left = (p->left) ? p->left : p->right;
                        } else {
                            parent->right = (p->right) ? p->right : p->left;
                        }
                    }

                    delete tmp;
                    return;
                } else {
                    // two children
                    Node<elemType> *q, *substitute;
                    parent = p;
                    flag = 0;
                    q = p->left;
                    
                    while(q->right) {
                        parent = q;
                        flag = 0;
                        q = q->right;
                    }
                    substitute = q;

                    // exchange the element value of p and substitute
                    elemType e = p->data;
                    p->data = substitute->data;
                    substitute->data = e;

                    // node to be deleted changes to substitute
                    p = substitute;
                }
            }
        }
    }
    void levelTraverse() const
    {
        if (!this->root) {
            return;
        }

        seqQueue<Node<elemType*>> que;
        Node<elemType> *p;
        que.enQueue(p);

        while (!que.isEmpty()) {
            p = que.front();
            que.deQueue();

            std::cout << p->data << ' ';
            if (p->left) {
                que.enQueue(p->left);
            }
            if (p->right) {
                que.enQueue(p->right);
            }
        }
    }
};

#endif // BINARYSEARCHTREE_H_INCLUDED