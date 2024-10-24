#include<iostream>

class FreeList;

class MemoryBlock {
friend class FreeList;
private:
    int start{-1};
    int size{-1};
    MemoryBlock* next;

public:
    MemoryBlock():next(nullptr) {};
    MemoryBlock(const int & start, const int & size, MemoryBlock* next) {
        this->start = start;
        this->size = size;
        this->next = next;
    };
};

class FreeList {
private:
    MemoryBlock* head;

public:
    FreeList() {
        head = new MemoryBlock();
    };

    void insert(int index, const int& start, const int& size) {
        MemoryBlock* p = this->head;
        int j = 0;

        // find the i-th position
        while(p && j < index - 1) {
            p = p->next;
            j++;
        } 

        // insert the new block
        p->next = new MemoryBlock(start, size, p->next);
    }

    void allocate(const int& request_size) {
        MemoryBlock* p = this->head;

        while(p->next) {
            if (request_size < p->next->size) {
                p->next->start += request_size;
                p->next->size -= request_size;
                return;
            } else if (request_size == p->next->size) {
                MemoryBlock* temp = p->next;
                p->next = temp->next;
                delete temp;
                return;
            } else {
                p = p->next;
            }
        } 
    };

    void release(const int& start, const int& size) {
        MemoryBlock *p = this->head, *q = p->next, *temp; 

        while (q) {
            if (start == q->start) {
                q->size += size;
                break;
            } else if (start > p->start && start < q->start) {
                p->next = new MemoryBlock(start, size, q);
                break;
            } else {
                p = p->next;
                q = q->next;
            }
        }

        if (!q) {
            p->next = new MemoryBlock(start, size, q);
        }

        // check whether two memory block can be merged
        p = this->head;
        while (p->next) {
            if (p->next->start == p->start + p->size) {
                p->size += p->next->size;
                temp = p->next;
                p->next = temp->next;
                delete temp;
                return;
            } else {
                p = p->next;
            }
        }

        return;
    };

    void printFlist() {
        MemoryBlock *p = this->head->next;

        while(p) {
            std::cout << '(' << p->start << ',' << p->size << ") ";
            p = p->next;
        }

        return;
    }

    ~FreeList() {
        MemoryBlock *p = this->head->next, *q;
        
        while(p) {
            q = p->next;
            delete p;
            p = q;
        }
    };
};

int main() {
    int length;
    FreeList fList;
    std::cin >> length;

    int start[length], size[length];

    for (int i = 0; i < length; i++) {
        std::cin >> start[i];
    }
    for (int i = 0; i < length; i++) {
        std::cin >> size[i];
    }

    for (int j = length - 1; j >= 0; j--) {
        fList.insert(1, start[j], size[j]);
    }

    int opNum, op, op1, op2;
    std::cin >> opNum;

    for (int i = 0; i < opNum; i++) {
        std::cin >> op;
        switch (op) {
            case 1:
                std::cin >> op1;
                fList.allocate(op1);
                break;
            case 2:
                std::cin >> op1 >> op2;
                fList.release(op1, op2);
                break;
        }
    }

    // output
    fList.printFlist();
    return 0;
}