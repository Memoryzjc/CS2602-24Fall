#include<iostream>
#include<cmath>

#define INF 2000001

struct treeNode {
    int data;
    treeNode *left, *right;
    treeNode() : data(-1), left(nullptr), right(nullptr) {}
    treeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

treeNode* buildTree(treeNode *root) {
    int data;
    std::cin >> data;

    if (data == -1) {
        return nullptr;
    } 

    root->data = data;
    treeNode *l = new treeNode(), *r = new treeNode();
    root->left = buildTree(l);
    root->right = buildTree(r);
    return root;
}

int findMinGap(treeNode *root) {
    int min, tmp1 = INF, tmp2 = INF;
    treeNode *p = nullptr, *q = nullptr;

    if (!root) {
        return INF;
    }

    if (root->left) {
        p = root->left;
    }

    if (root->right) {
        q = root->right;
    }

    if (p) {
        while (p->right) {
            p = p->right;
        }
        tmp1 = abs(root->data - p->data);
    }

    if (q) {
        while (q->left) {
            q = q->left;
        }
        tmp2 = abs(q->data - root->data);
    }

    min = std::min(tmp1, tmp2);
    return std::min(min, std::min(findMinGap(root->left), findMinGap(root->right)));
}

int main() {
    int data, result;
    treeNode *root = new treeNode();

    root = buildTree(root);

    result = findMinGap(root);
    std::cout << result;

    return 0;
}

