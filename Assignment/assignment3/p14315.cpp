#include<iostream>

struct Node {
    int data;
    int left, right;
    Node() : data(-1), left(-1), right(-1) {} 
    Node(int val) : data(val), left(-1), right(-1) {}
    Node(int rootVal, int leftVal, int rightVal) : data(rootVal), left(leftVal), right(rightVal) {}
};

void postOrder(int i, Node root[]) {
    if (i == -1) {
        return;
    }

    postOrder(root[i].left, root);
    postOrder(root[i].right, root);
    std::cout << root[i].data << " ";

    return;
}

void mirror(int i, Node root[]) {
    if (i != -1) {
        int tmp;
        tmp = root[i].left;
        root[i].left = root[i].right;
        root[i].right = tmp;

        mirror(root[i].left, root);
        mirror(root[i].right, root);
    }
    return;
}

int main() {
    int row, rootVal, leftVal, rightVal, root;
    int i, j = 0, tmp;
    Node t[10001];

    std::cin >> row;

    for (i = 0; i < row; i++) {
        std::cin >> rootVal >> leftVal >> rightVal;
        if (i == 0) {
            root = rootVal;
        }
        t[rootVal] = Node(rootVal, leftVal, rightVal);
        t[leftVal] = Node(leftVal);
        t[rightVal] = Node(rightVal);
    }

    mirror(root, t);

    postOrder(root, t);

    return 0;
}