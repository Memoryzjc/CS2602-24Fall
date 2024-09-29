#include "seqList.h"

#include <iostream>

int main()
{
    seqList<int> list;
    int i;
    
    for (i = 1; i <= 10; i++) {
        list.insert(i, i);
    }
    
    for (i = 1; i < 10; i++) {
        std::cout << list.get(i) << " ";
    }
    
    std::cout << std::endl;
    
    return 0;
}