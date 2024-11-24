#include<iostream>
#include<queue>
#include<vector>
#include<cmath>

struct Node {
    int val;
    bool flag;
    Node *left, *right;
    Node *path;
    Node() : val(0), flag(false), left(nullptr), right(nullptr), path(nullptr) {}
    Node(int data) : val(data), flag(false), left(nullptr), right(nullptr), path(nullptr) {}
};

Node* search(int data, Node* root) {
    if (!root || root->val == data) {
        return root;
    }

    Node *left = search(data, root->left);
    if (left) {
        return left;
    }
    return search(data, root->right);
}

bool isAccessible(Node *root, int checkVal) {
    std::queue<Node*> que;

    Node *p = root;
    que.push(p);

    while(!que.empty()) {
        p = que.front();
        que.pop();

        if (p->val == checkVal) {
            return true;
        }

        p->flag = true;  // already been checked

        if (p->left && !p->left->flag) {
            que.push(p->left);
        }

        if (p->right && !p->right->flag) {
            que.push(p->right);
        }

        if (p->path && !p->path->flag) {
            que.push(p->path);
        }
    }

    return false;
       
}

void resetFlag(Node* root) {
    if (!root) {
        return;
    }

    root->flag = false;
    resetFlag(root->left);
    resetFlag(root->right);
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
    int tNum, levelNum, data, pNum, pathNum, fromNum, toNum;
    int checkNum, checkVal;
    Node* forestRoot[10];
    std::queue<Node*> que;
    Node *current = new Node();

    std::cin >> tNum;

    // build forest
    for (int i = 0; i < 10; i++) {
        if (i >= tNum) {
            forestRoot[i] = nullptr;
            continue;
        }

        std::cin >> levelNum;
        pNum = std::pow(2, levelNum) - 1;

        std::cin >> data;
        Node *root = new Node(data);
        que.push(root);
        pNum--;

        while (pNum) {
            current = que.front();
            que.pop();
            
            std::cin >> data;
            Node *l = new Node(data);
            pNum--;

            std::cin >> data;
            Node *r = new Node(data);
            pNum--;

            current->left = l;
            current->right = r;

            que.push(l);
            que.push(r);
        }

        while(!que.empty()) {
            que.pop();
        }

        forestRoot[i] = root;
    }

    // add path
    std::cin >> pathNum;
    Node *from, *to;
    while(pathNum) {
        std::cin >> fromNum >> toNum;
        for (auto & tree : forestRoot) {
            from = search(fromNum, tree);
            if (from) {
                break;
            }
        }

        for (auto & tree : forestRoot) {
            to = search(toNum, tree);
            if (to) {
                break;
            }
        }

        if (!from || !to) {
            std::cout << "Cannot find the node.";
        } else {
            from->path = to;
        }

        pathNum--;
    }

    std::cin >> checkNum;
    for (int i = 0; i < checkNum; i++) {
        std::cin >> checkVal;
        if (isAccessible(forestRoot[0], checkVal)) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }

        for (auto &tree : forestRoot) {
            resetFlag(tree);
        }
    }

    for (auto &tree : forestRoot) {
        delTree(tree);
    }
    
    return 0; 
}