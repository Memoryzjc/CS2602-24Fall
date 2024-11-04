#include<iostream>

class illegalSize{};
class outOfBound{};

template<typename elemType>
class seqStack
{
private:
    elemType *array;  // hold the data element
    int Top;  // denote the top of the stack
    int maxSize;  // the maximum number of the data stored in stack
    void doubleSpace() 
    { 
        elemType *tmp = array;
        array = new elemType[2 * maxSize];
        
        if (!array) {
            throw illegalSize();
        }
        
        for (int i = 0; i < maxSize; i++) {
            array[i] = tmp[i];
        }
        
        maxSize *= 2;
        delete []tmp;
    };
public:
    // initialize sequential stack
    seqStack(int initSize = 1000)
    {
        this->array = new elemType[initSize];
        if (!array) {
            throw illegalSize();
        }
        this->Top = -1;
        this->maxSize = initSize;
    }

    // if the stack is empty return true and false otherwise
    bool isEmpty() 
    {
        return Top == -1;
    }  

    // if the stack is full return true and false otherwise
    bool isFull() 
    {
        return Top == maxSize - 1;
    }  
    
    // return the value of the top element and doesn't change the top of stack
    elemType top() 
    {
        if (this->isEmpty()) {
            throw outOfBound();
        }
        return this->array[this->Top];
    }
    
    // push the element e into the stack
    void push(const elemType &e)
    {
        if (this->isFull()) {
            this->doubleSpace();
        }
        
        this->array[++this->Top] = e;
    } 
    
    // pop the element of the top of the stack
    void pop()
    {
        if (this->isEmpty()) {
            throw illegalSize();
        }

        this->Top--;
    }
    
    // free the dynamic array
    ~seqStack() 
    {
        delete []array;
    };  
};

bool isLegal(int nums[], int totalNum) {
    seqStack<int> s;  // hold the number to be checked
    int checkNum = 1;  // denote the correct number in every step
    int outNum;  // denote the number out of s

    if (totalNum == 1 && nums[0] != 1) {
        return false;
    }

    s.push(nums[0]);  // push the first number into s
    for (int i = 1; i < totalNum; i++) {
        if (nums[i] > nums[i - 1]) {
            // if nums[i] > nums[i - 1], pop all the element in s
            // and check whether each element is equal to checkNum
            while (!s.isEmpty()) {
                outNum = s.top();
                s.pop();

                if (outNum != checkNum) {
                    return false;
                }

                // add 1 to checkNum for next check
                checkNum++;
            }
        }

        s.push(nums[i]);
    }

    // Check remaining elements in stack
    while (!s.isEmpty()) {
        outNum = s.top();
        s.pop();
        if (outNum != checkNum) {
            return false;
        }

        checkNum++;
    }

    return true;
}

int main() {
    int T, totalNum;
    std::cin >> T;
    bool result[T];

    for (int i = 0; i < T; i++) {
        std::cin >> totalNum;
        int nums[totalNum];

        for (int j = 0; j < totalNum; j++) {
            std::cin >> nums[j];
        }

        if (isLegal(nums, totalNum)) {
            result[i] = true;
        } else {
            result[i] = false;
        }

    }

    for (int i = 0; i < T; i++) {
        if (result[i]) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }

    return 0;
}