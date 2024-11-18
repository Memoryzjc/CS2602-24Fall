#include<iostream>

struct Node
{
    int data;
    int parent;
    int layer;
    Node *left;
    Node *right;
};

Node* buildTree(Node *t, int layer, int parent) {
    int data;
    std::cin >> data;
    t->data = data;
    t->parent = parent;
    t->layer = layer;

    if (data == -1) {
        t->left = nullptr;
        t->right = nullptr;
        return t;
    }

    Node *left = new Node, *right = new Node;
    layer++;
    t->left = buildTree(left, layer, t->data);
    t->right = buildTree(right, layer, t->data);
    return t;
}

Node *findNode(Node *root, int data) {
    if (root == nullptr || root->data == data) {
        return root;
    }
    
    Node *left = findNode(root->left, data);
    if (left != nullptr) {
        return left;
    }

    return findNode(root->right, data);
}

void delTree(Node *root) {
    if (!root) {
        return;
    }

    delTree(root->left);
    delTree(root->right);

    delete root;
}

int main() {
    int n, num1, num2;
    int deepth, data;
    std::cin >> n;
    
    int nums[n][2];

    for (int i = 0; i < n; i++) {
        std::cin >> num1 >> num2;
        nums[i][0] = num1;
        nums[i][1] = num2;
    }

    Node *root = new Node, *n1, *n2;
    root = buildTree(root, 0, 0);

    for (int i = 0; i < n; i++) {
        n1 = findNode(root, nums[i][0]);
        n2 = findNode(root, nums[i][1]);
        std::cout << ((n1->layer == n2->layer && n1->parent != n2->parent) ? 1 : 0 )<< std::endl;
    }

    delTree(root);

    return 0;
}