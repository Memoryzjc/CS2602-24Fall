#include<iostream>
#include"seqStack.h"

int main() {
    seqStack<char> s;
    char ctemp;

    std::cout << "Input the elements, and press enter for ending." << std::endl;
    ctemp = std::cin.get();
    while(ctemp != '\n') {
        s.push(ctemp);
        ctemp = std::cin.get();
    }

    std::cout << "Output the elements in the stack one by one." << std::endl;
    while(!s.isEmpty()) {
        ctemp = s.top();
        s.pop();
        std::cout << ctemp << ' ';
    }

    std::cout << std::endl;
    return 0;
}