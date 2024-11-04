#include<iostream>
#include<vector>

// class illegalSize{};
// class outOfBound{};

// template<typename elemType>
// class linkQueue;

// template<typename elemType>
// class Node
// {
// friend class linkQueue<elemType>;
// private:
//     elemType data;
//     Node *next;
// public:
//     Node() {
//         this->next = nullptr;
//     }
//     Node(const elemType &x, Node *p=nullptr) {
//         this->data = x;
//         this->next = p;
//     }
// };

// template<typename elemType>
// class linkQueue
// {
// private:
//     Node<elemType> *Front, *Rear;
// public:
//     linkQueue() {
//         this->Front = this->Rear = nullptr;
//     }
//     bool isEmpty() {
//         return !this->Front;
//     }
//     bool isFull() {
//         return false;
//     }
//     elemType front() {
//         if (this->isEmpty()) {
//             throw outOfBound();
//         }

//         return this->Front->data;
//     }
//     void enQueue(const elemType &x) {
//         if (this->isFull()) {
//         throw outOfBound();
//         }

//         if (!this->Rear) {
//             this->Front = this->Rear = new Node<elemType>(x);
//         } else {
//             this->Rear->next = new Node<elemType>(x);
//             this->Rear = this->Rear->next;
//         }
//     }
//     void deQueue() {
//         if (this->isEmpty()) {
//             throw outOfBound();
//         }

//         Node<elemType> *tmp = this->Front;
//         this->Front = this->Front->next;
//         delete tmp;

//         if(!this->Front) {
//             this->Front = nullptr;
//         }
//     }
//     ~linkQueue() {
//         Node<elemType> *p;
//         p = this->Front;

//         while(p) {
//             this->Front = this->Front->next;
//             delete p;
//             p = this->Front;
//         }
//     }
// };

struct child {
    int time;  // denote the gaming time of a child
    int index;  // denote the index of a child
    int turn;  // turn = (time + maxTime - 1) / maxTime
};

int main() {
    int kidNum, maxTime, res, maxTurn = 100000000;
    std::cin >> kidNum >> maxTime;

    std::vector<child> kids;
    child kid, inGameKid;

    for (int i = 0; i < kidNum; i++) {
        std::cin >> kid.time;
        kid.index = i;
        kid.turn = (kid.time + maxTime - 1) / maxTime;
        // maxTurn = (maxTurn > kid.turn) ? maxTurn : kid.turn;
        kids.push_back(kid);
    }

    std::vector<std::vector<child>> buckets(maxTurn + 1);

    for (int i = 0; i < kidNum; i++) {
        kid = kids[i];
        buckets[kid.turn].push_back(kid);
    }

    for (auto & bucket : buckets) {
        if (!bucket.empty()) {
            for (auto kid : bucket) {
                std::cout << kid.index << " ";
            }
        }
    }

    // linkQueue<child> allKids;
    // linkQueue<int> result;
    // child kid, inGameKid;
    // for (int i = 0; i < kidNum; i++) {
    //     std::cin >> kid.time;
    //     kid.index = i;
    //     kid.index = (kid.time + maxTime - 1) / maxTime;
    //     allKids.enQueue(kid);
    // }

    // while(!allKids.isEmpty()) {
    //     inGameKid = allKids.front();
    //     allKids.deQueue();

    //     if (allKids.isEmpty()) {
    //         result.enQueue(inGameKid.index);
    //         break;
    //     }

    //     inGameKid.time -= maxTime;

    //     if (inGameKid.time <= 0) {
    //         result.enQueue(inGameKid.index);
    //     } else {
    //         allKids.enQueue(inGameKid);
    //     }
    // }

    // while(!result.isEmpty()) {
    //     res = result.front();
    //     result.deQueue();
    //     std::cout << res << " ";
    // }
    return 0;
}