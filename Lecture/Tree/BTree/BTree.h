#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include<iostream>
#include"seqStack.h"
#include"seqQueue.h"

template<typename elemType>
class BTree;

templaet<typename elemType>
class Node
{
friend class BTree<elemType>;
private:
    elemType data;
    Node *left, *right;
    int leftFlag;  // 用于标识是否线索，0时left为左孩子结点，1时为前驱线索
    int rightFlag;  // 用于标识是否线索，0时left为右孩子结点，1时为后继线索 
public:
    Node() 
    {
        left = nullptr;
        right = nullptr;
        leftFlag = 0;
        rightFlag = 0;
    }

    Node(const elemType &e, Node *L = nullptr, Node *R = nullptr) 
    {
        data = e;
        left = L;
        right = R;
        leftFlag = 0;
        rightFlag = 0;
    }
};

template<typename elemType>
class BTree
{
private:
    Node<elemType> *root;
    elemType stopFlag;

    // 求以t为根的二叉树的结点个数
    int Size(Node<elemType> *t)
    {
        if (!t) {
            return 0;
        }

        return 1 + this->Size(t->left) + this->Size(t->right);
    }  

    // 求以t为根的二叉树高度
    int Height(Node<elemType> *t)
    {
        int hl = this->Height(t->left), hr = this->Height(t->right);
        
        if (!t) {
            return 0;
        }

        return (hl > hr) ? hl : hr;
    }  
    
    // 删除以t为根的二叉树
    void DelTree(Node<elemType> *t)
    {
        if (!t) {
            return;
        }

        this->DelTree(t->left);
        this->DelTree(t->right);

        delete t;
    }  

    // 按前序遍历输出以t为根的二叉树的结点的数据值
    void PreOrder(Node<elemType> *t)
    {
        if (!t) {
            return;
        }
        std::cout << t->data << " ";

        this->PreOrder(t->left);
        this->PreOrder(t->right);
    }  

    // 按中序遍历输出以t为根的二叉树的结点的数据值
    void InOrder(Node<elemType> *t)
    {
        if (!t) {
            return;
        }
        
        this->InOrder(t->left);
        std::cout << t->data << " ";
        this->InOrder(t->right);
    }  

    // 按后序遍历输出以t为根的二叉树的结点的数据值
    void PostOrder(Node<elemType> *t)
    {

    }

public:
    BTree()
    {
        this->root = nullptr;
    }

    // 创建一颗二叉树，flag表示停止元素
    void createTree(const elemType &flag)
    {
        seqQueue<Node<elemType>*> que;
        elemType e, el, er;
        Node<elemType> *p, *pl, *pr;

        this->stopFlag = flag;
        std::cout << "Please input the root: ";
        std::cin >> e;

        if (e == flag) {
            this->root = nullptr;
            return;
        }

        p = new Node<elemType>(e);
        this->root = p;

        que.enQueue(p);
        while(!que.isEmpty()) {
            p = que.front();
            que.deQueue();

            std::cout << "Please input the left child and the right child of "
                      << p->data << ", using" << flag << " as no child: ";
            std::cin >> el >> er;

            if (el != flag) {
                // have left child
                pl = new Node<elemType>(el);
                p->left = pl;
                que.enQueue(pl);
            }

            if (er != flag) {
                // have right child
                pr = new Node<elemType>(er);
                p->right = pr;
                que.enQueue(pr);
            }
        }

        return;
    }

    bool isEmpty()
    {
        return this->root == nullptr;
    }

    Node<elemType>* GetRoot()
    {
        return this->root;
    }

    // 求二叉树的结点个数
    int Size()
    {
        return this->Size(this->root);
    }

    // 求二叉树的高度
    int Height()
    {
        return this->Height(this->root);
    }

    // 删除二叉树
    void DelTree()
    {
        this->DelTree(this->root);
        this->root = nullptr;
    }

    // 按前序遍历输出二叉树的结点的数据值(递归算法)
    // void PreOrder()
    // {
    //     this->PreOrder(this->root);
    // }

    // 前序遍历的非递归算法
    void PreOrder()
    {
        if (!this->root) {
            return;
        }

        Node<elemType> *p;
        seqStack<Node<elemType>*> s;
        s.push(root);

        while(!s.isEmpty()) {
            p = s.top();
            std::cout << p->data;
            s.pop();

            if (p->right) {
                s.push(p->right);
            }
            if (p->left) {
                s.push(p->left);
            }
        }

        std::cout << std::endl;
    }

    // 按中序遍历输出二叉树的结点的数据值(递归)
    void InOrder()
    {
        this->InOrder(this->root);
    }

    // 按后序遍历输出二叉树的结点的数据值
    void PostOrder()
    {

    }

    // 按层次遍历输出二叉树的结点的数据值
    void LevelOrder()
    {

    }
};

#endif // BTREE_H_INCLUDED