#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

struct Node {
    int data;
    bool flag;  // denote whether the node is null
    Node *l;
    Node *r;
    Node() : data(-1), flag(false), l(nullptr), r(nullptr) {}
    Node(int d) : data(d), flag(false), l(nullptr), r(nullptr) {}
    Node(bool f) : data(-1), flag(f), l(nullptr), r(nullptr) {}  
};

// 递归计算二叉树的最大深度
int height(Node* root) {
    if (!root || root->flag) {
        return 0;  // 空树深度为0
    }
    int leftH = height(root->l);
    int rightH = height(root->r);
    return std::max(leftH, rightH) + 1;  // 返回较大的深度加1
}

// 删除二叉树的内存
void delTree(Node* root) {
    if (!root) {
        return;
    }
    delTree(root->l);
    delTree(root->r);
    delete root;
}

int main() {
    int nums, data;
    std::string val;
    std::cin >> nums;
    std::cin.ignore();  // 处理数字后的一行换行符

    if (nums <= 0) {
        std::cout << 0 << std::endl;  // 如果节点数为0，直接输出0
        return 0;
    }

    // 读取根节点
    std::getline(std::cin, val);
    if (val == "null") {
        std::cout << 0 << std::endl;  // 如果根节点是null，输出0
        return 0;
    }

    // 创建根节点
    Node* root = new Node(std::stoi(val));
    Node* p;
    std::queue<Node*> que;
    que.push(root);
    nums--;

    // 构建二叉树
    while (nums > 0 && !que.empty()) {
        p = que.front();
        que.pop();

        // 处理左子节点
        std::getline(std::cin, val);
        if (val != "null") {
            data = std::stoi(val);
            p->l = new Node(data);
        } else {
            p->l = new Node(true);
        }
        que.push(p->l);
        nums--;

        // 处理右子节点
        if (nums > 0) {
            std::getline(std::cin, val);
            if (val != "null") {
                data = std::stoi(val);
                p->r = new Node(data);
            } else {
                p->r = new Node(true);
            }
            que.push(p->r);
            nums--;
        }
    }

    // 计算最大深度
    int result = height(root);
    std::cout << result << std::endl;

    // 释放内存
    delTree(root);

    return 0;
}
