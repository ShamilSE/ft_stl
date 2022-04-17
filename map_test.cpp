#include <map>
#include "map.h"
#include <iostream>

template <typename Key, typename Value>
void printMap(ft::map<Key, Value>& my_map)
{
    for (auto it = my_map.begin(); it != my_map.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

bool iteratorTest() {
    ft::map<int, int> a;
    a.insert(ft::make_pair(1, 5));
    a.insert(ft::make_pair(5, 4));
    a.insert(ft::make_pair(3, 9));
    a.insert(ft::make_pair(4, 16));

    std::map<int, int> origin;
    origin.insert(std::make_pair(1, 5));
    origin.insert(std::make_pair(5, 4));
    origin.insert(std::make_pair(3, 9));
    origin.insert(std::make_pair(4, 16));

    return true;
}

bool iteratorTest_2() {
    ft::map<int, int> my_map;

    my_map.insert(ft::make_pair(1, 5));
    my_map.insert(ft::make_pair(2, 6));
    my_map.insert(ft::make_pair(3, 7));
    my_map.insert(ft::make_pair(4, 8));
    my_map.insert(ft::make_pair(5, 9));
    my_map.insert(ft::make_pair(-10, 1000));

    for (auto it = my_map.begin(); it != my_map.end(); it++) {
        std::cout << *it << std::endl;
    }
    return true;
}

bool findMethod() {
    ft::map<int, int> my_map;

    my_map.insert(ft::make_pair(1, 5));
    my_map.insert(ft::make_pair(2, 6));
    my_map.insert(ft::make_pair(3, 7));
    my_map.insert(ft::make_pair(4, 8));

    ft::map<int, int>::iterator it = my_map.find(4);
    std::cout << *it << std::endl;
    it = my_map.find(1);
    std::cout << *it << std::endl;
    it = my_map.find(2);
    std::cout << *it << std::endl;
    it = my_map.find(3);
    std::cout << *it << std::endl;
    return true;
}

bool eraseMethod() {
    ft::map<int, int> my_map;

    my_map.insert(ft::make_pair(1, 5));
    my_map.insert(ft::make_pair(2, 6));
    my_map.insert(ft::make_pair(3, 7));
    my_map.insert(ft::make_pair(4, 8));

    std::cout << "print map first time" << std::endl;
    printMap(my_map);
    ft::map<int, int>::iterator it = my_map.begin();
    it++;
    my_map.erase(it);
    std::cout << "print map second time" << std::endl;
    printMap(my_map);
    return false;
}

int main() {
    //iteratorTest_2();
    //findMethod();
    eraseMethod();
    return 0;
}
