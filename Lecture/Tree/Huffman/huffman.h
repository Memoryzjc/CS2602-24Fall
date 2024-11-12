#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include"seqStack.h"

template<typename elemType>
struct HuffmanNode
{
    elemType data;
    double weight;
    int parent;
    int left, right;
};

/*
 * find the index of minimum value among all the nodes which parent is 0
 */
template<typename elemType>
int minIndex(HuffmanNode<elemType> Bt[], int k, int m)
{
    int i, min, minWeight = 9999;

    for (i = m - 1; i > k; i--) {
        if (Bt[i].parent == 0 && Bt[i].weight < minWeight) {
            min = i;
            minWeight = Bt[min].weight;
        }
    }

    return min;
}

template<typename elemType>
HuffmanNode<elemType> *BestBinaryTree(elemType a[], double w[], int n)
{
    HuffmanNode<elemType> *BBTree;
    int fisrt_min, second_min;
    int m = 2 * n;  // a total number of nodes is 2n and the 0-index doesn't put node
    int i, j;

    // Store the leaves in the array from back to front
    BBTree = new HuffmanNode<elemType>[m];
    for (j = 0; j < n; j++) {
        i = m - 1 - j;
        BBTree[i].data = a[j];
        BBTree[i].weight = w[j];
        BBTree[i].parent = 0;
        BBTree[i].left = 0;
        BBTree[i].right = 0;
    }
    i = n - 1;  // i is the position ready for the first new node

    while (i != 0) {
        fisrt_min = minIndex(BBTree, i, m);
        BBTree[fisrt_min].parent = i;
        second_min = minIndex(BBTree, i, m);
        BBTree[second_min].parent = i;

        BBTree[i].weight = BBTree[fisrt_min].weight + BBTree[second_min].weight;
        BBTree[i].parent = 0;
        BBTree[i].left = fisrt_min;
        BBTree[i].right = second_min;

        i--;
    }

    return BBTree;
}

// give the Huffman code of n nodes
template<typename elemType>
char **HuffmanCode(HuffmanCode<elemType> BBTree[], int n)
{
    seqStack<char> s;
    char **HFCode;  // store the Huffman Codes
    char zero = '0', one = '1';
    int m, i, j, parent, child;

    HFCode = new char*[n];
    for (i = 0; i < n; i++) {
        HFCode[i] = new char[n + 1];
    }

    m = 2 * n;
    // no node
    if (n == 0) {
        return HFCode;
    }
    // one node
    if (n == 1) {
        HFCode[0][0] = '0', HFCode[0][1] = '\0';
        return HFCode;
    }

    for (i = m - 1; i >= n; i--) {
        child = i;
        parent = BBTree[child].parent;

        while (parent != 0) {
            if (BBTree[parent].left == child) {
                s.push(zero);
            } else {
                s.push(one);
            }

            child = parent;
            parent = BBTree[parent].parent;
        }

        j = 0;
        
        while (!s.isEmpty()) {
            HFCode[m - i - 1][j] = s.top();
            s.pop();
            j++;
        }

        HFCode[m - i - 1][j] = '\0';
    }

    return HFCode;
}

#endif  // HUFFMAN_H_INCLUDED