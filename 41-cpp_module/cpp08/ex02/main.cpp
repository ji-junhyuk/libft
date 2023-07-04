#include "MutantStack.h"
#include <iostream>

int main(void) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    // 1 3 4 737
    mstack.push(3);
    mstack.push(4);
    mstack.push(737);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    while (it != ite) {
        std::cout << *it << ' ';
        ++it;
    }
    std::cout << std::endl;
}
