#include "map.h"
#include "vector.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>


int main() {
    std::cout << "main for map" << std::endl;
    ft::map<int, int> a;
    a.insert(ft::make_pair(1, 5));
    a.insert(ft::make_pair(2, 4));
    return 0;
}