#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include<iostream>
#include"seqStack.h"
#include"seqQueue.h"

template<typename elemType>
class BTree;

template<typename elemType>
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
        if (!t) {
            return;
        }

        PostOrder(t->left);
        PostOrder(t->right);
        std::cout << t->data;
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
            std::cout << std::endl;
        }

    }

    // 按中序遍历输出二叉树的结点的数据值(递归)
    // void InOrder()
    // {
    //     this->InOrder(this->root);
    // }

    // in-order iteration
    void InOrder()
    {
        // If root == nullptr, end iteration
        if (this->root) {
            return;
        }

        seqStack<Node<elemType>*> s;  // hold the nodes 
        seqStack<int> flagStack;  // hold the flags of each corresponding node
        Node<elemType> *p;
        int flag;  // denote whether a node is pushed into s

        // push root into s
        s.push(this->root);
        flagStack.push(0);

        // main iteration
        while (!s.isEmpty()) {
            // check the top element and its flag
            flag = flagStack.top();
            flagStack.pop();

            p = s.top();
            if (flag == 1) {
                // p already pushed into s, visit and pop p
                s.pop();
                std::cout << p->data;
                // if p has right child, push it into s or continue otherwise
                if (!p->right) {
                    continue;
                } else {
                    s.push(p->right);
                    s2.push(0);
                }
            } else {
                // p not pushed into s, do not pop it and change its flag to 1
                flagStack.push(1);

                // if p has left child, push it into s and 0 into flagStack
                if (p->left) {
                    s.push(p->left);
                    flagStack.push(0);
                }
            }
            std::cout << std::endl;
        }

    }

    // 按后序遍历输出二叉树的结点的数据值
    // void PostOrder()
    // {
    //     return PostOrder(this->root);
    // }

    // Post-Order iteration
    void PostOrder() 
    {
        if (!this->root) {
            return;
        }

        seqStack<Node<elemType>*> nodeS;
        seqStack<int> flagS;
        Node<elemType> *p;
        int flag;

        // push root into node stack
        nodeS.push(this->root);
        flagS.push(0);

        while (!nodeS.isEmpty()) {
            flag = flagS.top();
            flagS.pop();
            p = nodeS.top();

            switch (flag) {
                case 0:
                    // not poped out of node stack
                    // if has left child, push its left child into node stack
                    flagS.push(1);
                    if (p->left) {
                        nodeS.push(p->left);
                        flagS.push(0);
                    }
                    break;
                case 1:
                    // poped out of s once
                    // if has right child, push its right child into node stack
                    flagS.push(2);
                    if (p->right) {
                        nodeS.push(p->right);
                        flagS.push(0);
                    }
                    break;
                case 2:
                    // poped out of node stack twice
                    /// pop and visit it
                    nodeS.pop();
                    std::cout << p->data;
                    break;
            }

            std::cout << std::endl;
        }
    }

    // 按层次遍历输出二叉树的结点的数据值
    void LevelOrder()
    {
        if (!this->root) {
            return;
        }

        seqQueue<Node<elemType>*> que;
        Node<elemType> *p;

        que.enQueue(this->root);

        while(!que.isEmpty()) {
            p = que.front();
            que.deQueue();
            std::cout << p->data;

            if (p->left) {
                que.enQueue(p->left);
            }
            if (p->right) {
                que.enQueue(p->right);
            }

            std::cout << std::endl;
        }
    }

    /* 
     * Use the series of pre and in order to build a tree
     * parameter:
     * pre[]: stores the preorder traversal sequence
     * mid[]: stroes the inorder traversal sequence
     * pl, pr: the left and right index of preorder sequence
     * ml, mr: the left and right index of inorder sequence
     * return:
     * the root
     */
    Node<elemType>* buildTree(elemType pre[], int pl, int pr, elemType mid[], int ml, int mr)
    {
        Node<elemType> *p, *leftRoot, *rightRoot;
        int i, pos, num;
        // the left and right index of preorder and inorder 
        // sequences in left child tree
        int lpl, lpr, lml, lmr;  
        // the left and right index of preorder and inorder 
        // sequences in right child tree
        int rpl, rpr, rml, rmr;

        if (pl > pr) {
            return nullptr;
        }

        p = new Node<elemType> (pre[pl]);  // find the root of child tree
        if (!this->root) {
            this->root = p;
        }

        // find the root position in mid[]
        // and the number of nodes in left child tree
        for (i = ml; i < mr; i++) {
            if (min[i] == pre[pl]) {
                break;
            }
        }
        pos = i;  // the root index in mid[]
        num = pos - ml;  // the number of nodes in left child tree

        // find the range of left child tree node's index in pre[] and mid[]
        lpl = pl + 1;
        lpr = pl + num;
        lml = ml;
        lmr = pos - 1;
        leftRoot = buildTree(pre, lpl, lpr, mid, lml, lmr);

        // find the range of right child tree node's index in pre[] and mid[]
        rpl = pl + num + 1;
        rpr = pr;
        rml = pos + 1;
        rmr = mr;
        rightRoot = buildTree(pre, rpl, rpr, mid, rml, rmr);

        p->left = leftRoot;
        p->right = rightRoot;
        return p;
    }

};

#endif // BTREE_H_INCLUDED