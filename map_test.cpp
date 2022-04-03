#include "map.h"
#include <iostream>

int main() {
    ft::map<int, int> a;
    a.insert(ft::make_pair(1, 5));
    a.insert(ft::make_pair(5, 4));
    a.insert(ft::make_pair(3, 9));
    a.insert(ft::make_pair(4, 16));

    std::cout << "going forward" << std::endl;
    for (auto it = a.begin(); it.currentNode != a.getTree()->getTailNode(); it++) {
        std::cout << it.currentNode->pair->first << std::endl;
    }
    std::cout << "going backward" << std::endl;

    return 0;
}
