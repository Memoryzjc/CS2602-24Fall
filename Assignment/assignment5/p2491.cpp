#include<iostream>
#include<queue>
#include<unordered_set>

int main() {
    int n;
    long ugly, tmp;
    std::cin >> n;
    std::priority_queue<long, std::vector<long>, std::greater<long>> uglyNums;
    std::unordered_set<long> s;

    uglyNums.push(1);
    s.insert(1);

    for (int i = 0; i < n - 1; i++) {
        ugly = uglyNums.top();
        uglyNums.pop();
        auto p = s.insert(ugly * 2);
        if (p.second) {
            uglyNums.push(ugly * 2);
        } 
        p = s.insert(ugly * 3);
        if (p.second) {
            uglyNums.push(ugly * 3);
        }
        p = s.insert(ugly * 5);
        if (p.second) {
            uglyNums.push(ugly * 5);
        }
    }

    std::cout << uglyNums.top();

    return 0;
}