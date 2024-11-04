#include<iostream>
#include"seqQueue.h"

int main() {
    seqQueue<int> que;
    int i, x;

    for (i = 0; i < 15; i++) {
        que.enQueue(i);
    }

    while(!que.isEmpty()) {
        x = que.front();
        que.deQueue();
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}