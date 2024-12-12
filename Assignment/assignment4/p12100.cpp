#include<iostream>

struct HuffmanNode 
{
    int weight;
    int parent;
    int left, right;
    HuffmanNode() : weight(-1), parent(0), left(-1), right(-1) {}
    HuffmanNode(int w) : weight(w), parent(0), left(-1), right(-1) {}
    HuffmanNode(int w, int l, int r) : weight(w), parent(0), left(l), right(r) {}
};

int minIndex(const HuffmanNode Bt[], const int size, const int m) {
    int i, minI = -1, minWeight = 10001;

    for (i = m + 1; i < size; i++) {
        if (Bt[i].parent == 0 && Bt[i].weight <= minWeight && Bt[i].weight != -1) {
            minI = i;
            minWeight = Bt[minI].weight;
        }
    }

    return minI;
}

// return the length of the Huffman code of Bt[index]
int codeLength(const HuffmanNode Bt[], const int index) {
    int length = 0;
    int i = index;

    while (Bt[i].parent != 0) {
        length++;
        i = Bt[i].parent;
    }

    return length;
}

int main() {
    int N, w, firstMin, secondMin;
    int result = 0;

    std::cin >> N;
    int size = 2 * N;

    HuffmanNode BBTree[100000];
    // read the data
    for (int i = size - 1; i >= N; i--) {
        std::cin >> w;
        BBTree[i] = HuffmanNode(w);
    }

    // build the tree
    for (int j = N - 1; j > 0; j--) {
        firstMin = minIndex(BBTree, size, j);
        BBTree[firstMin].parent = j;
        secondMin = minIndex(BBTree, size, j);
        BBTree[secondMin].parent = j;

        if (firstMin == -1 || secondMin == -1) {
            std::cout << "Error: firstMin or secondMin is -1" << std::endl;
            return 1;
        }

        BBTree[j] = HuffmanNode(BBTree[firstMin].weight + BBTree[secondMin].weight, firstMin, secondMin);
    }

    for (int i = size - 1; i >= N; i--) {
        result += BBTree[i].weight * codeLength(BBTree, i);
    }

    std::cout << result;

    return 0;
}