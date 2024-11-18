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
        
    }
public:
    binarySearchTree() root(nullptr) {}
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

    }
    void remove (const elemType &x)
    {

    }
    void levelTraverse() const
    {

    }
};

#endif // BINARYSEARCHTREE_H_INCLUDED