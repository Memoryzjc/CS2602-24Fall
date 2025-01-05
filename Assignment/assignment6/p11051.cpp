#include<iostream>

struct Node {
    int data;
    Node *next;
    Node() : data(-1), next(nullptr) {}
    Node(int d) : data(d), next(nullptr) {}
};

int main() {
    int n, data, m, checkNum, result = 0;
    std::cin >> n;
    Node *head = new Node();
    Node *p = head, *q;

    while (n > 0) {
        std::cin >> data;
        Node *r = new Node(data);
        p->next = r;
        p = p->next;
        n--;
    }

    std::cin >> m;

    while (m > 0) {
        std::cin >> checkNum;
        q = head;
        p = head->next;

        while (p) {
            result++;
            if (p->data == checkNum) {
                q->next = p->next;
                p->next = head->next;
                head->next = p;
                break;
            } else {
                q = p;
                p = p->next;
            }
        }
        m--;
    }

    p = head;
    while (p) {
        q = p;
        p = p->next;
        delete q;
    }

    std::cout << result;

    return 0;
}