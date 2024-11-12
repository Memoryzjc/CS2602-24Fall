#include<iostream>
#include<queue>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

void findKthElement(Node* root, int &k, int &result) {
    if (root == nullptr || k <= 0) {
        return;
    }

    findKthElement(root->right, k, result);

    k--;
    if (k == 0) {
        result = root->data;
        return;
    }

    findKthElement(root->left, k, result);
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
    std::queue<Node*> que;
    int data, nums = 7, cnt;
    std::cin >> data;

    Node *root = new Node(data);
    Node *curr;
    que.push(root);
    nums--;

    while(nums && !que.empty()) {
        curr = que.front();
        que.pop();

        std::cin >> data;
        curr->left = new Node(data);
        nums--;
        que.push(curr->left);

        std::cin >> data;
        curr->right = new Node(data);
        nums--;
        que.push(curr->right);
    }

    std::cin >> cnt;
    int result = 0;

    findKthElement(root, cnt, result);
    std::cout << result;

    delTree(root);
    return 0;
}