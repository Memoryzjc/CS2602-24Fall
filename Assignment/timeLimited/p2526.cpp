#include <iostream>
#include <queue>
#include <string>

struct Node {
    int data;
    Node *l;
    Node *r;
    Node() : data(-1), l(nullptr), r(nullptr) {}
    Node(int d) : data(d), l(nullptr), r(nullptr) {}
};

int height(Node *root) {
    if (!root) {
        return 0;
    }

    int leftH = height(root->l);
    int rightH = height(root->r);
    return (leftH > rightH) ? leftH + 1 : rightH + 1;
}

void delTree(Node *root) {
    if (!root) {
        return;
    }

    delTree(root->l);
    delTree(root->r);
    delete root;
}

int main() {
    int nums;
    std::string val;
    std::cin >> nums;
    std::cin.ignore();

    if (nums <= 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::getline(std::cin, val);
    if (val == "null") {
        std::cout << 0 << std::endl;
        return 0;
    }

    Node *root = new Node(std::stoi(val));
    Node *p;
    std::queue<Node*> que;
    que.push(root);
    nums--;

    while (nums && !que.empty()) {
        p = que.front();
        que.pop();

        std::getline(std::cin, val);
        if (val != "null") {
            Node *l = new Node(std::stoi(val));
            que.push(l);
            p->l = l;
        } else {
            p->l = nullptr;
        }
        nums--;

        if (nums) {
            std::getline(std::cin, val);
            if (val != "null") {
                Node *r = new Node(std::stoi(val));
                que.push(r);
                p->r = r;
            } else {
                p->r = nullptr;
            }
            nums--;
        }
    }

    int result = height(root);
    std::cout << result << std::endl;

    delTree(root);

    return 0;
}