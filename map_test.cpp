#include <map>
#include "map.h"
#include <iostream>
#include <gtest/gtest.h>




TEST(map, iterator_test) {
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

    ft::map<int,int>::iterator ftIt = a.begin();
    std::map<int,int>::iterator stdIt = origin.begin();

    size_t i = 0;
    while (stdIt != origin.end()) {
        EXPECT_EQ(ftIt->second, stdIt->second);
        std::cout << i << " " << ftIt->second << " / " << stdIt->second << std::endl;
        ftIt++;
        stdIt++;
        i++;
    }
}
/*
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

bool atMethod()
{
    ft::map<int, int>* my_map = new ft::map<int, int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(2,2));

    try
    {
        const int key = 1;
        int a = my_map->at(key);
        std::cout << "found by at() " << a << std::endl;
    }
    catch (std::out_of_range&)
    {
        std::cout << "amogus" << std::endl;
    }

    try
    {
        [[maybe_unused]] int a = my_map->at(3);
    }
    catch (std::out_of_range&)
    {
        std::cout << "amogus" << std::endl;
    }

    return true;
}

bool countMethod()
{
    ft::map<int, int>* my_map = new ft::map<int, int>();

    my_map->insert(ft::make_pair(1,1));
    std::cout << "count() returns " << my_map->count(1) << std::endl;
    std::cout << "count() returns " << my_map->count(2) << std::endl;

    return true;
}

bool insertMethod()
{
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    ft::map<int,int>::iterator it = my_map->begin();
    std::cout << *it << std::endl;
    std::cout << "my_map.size() " << my_map->size() << std::endl;

    ft::pair<ft::map<int,int>::iterator, bool> pair = my_map->insert(ft::make_pair(2,2));
    std::cout << "inserted pair(2,2)\n" << pair.second << "\n" << *(pair.first) << std::endl;

    return true;
}

bool operatorBracketsMethodTest()
{
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    std::cout << my_map->size() << std::endl;

    (*my_map)[2];
    std::cout << my_map->size() << std::endl;

    printMap(*my_map);

    return true;
}

bool clearMethod()
{
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(5,5));
    my_map->insert(ft::make_pair(-10,-10));
    my_map->insert(ft::make_pair(-500,-500));

    my_map->clear();
    std::cout << my_map->size()  << std::endl;
    return true;
}

bool swapMethod()
{
    ft::map<int,int>* my_map = new ft::map<int,int>();
    ft::map<int,int>* my_map2 = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(2,2));
    my_map->insert(ft::make_pair(3,3));

    my_map2->insert(ft::make_pair(4,4));
    my_map2->insert(ft::make_pair(5,5));
    my_map2->insert(ft::make_pair(6,6));

    printMap(*my_map);

    my_map->swap(*my_map2);
    printMap(*my_map);

    return true;
}

bool key_compare_method()
{
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(5,5));
    std::less<int> comparator = my_map->key_comp();
    std::cout << comparator(1,12) << std::endl;
    std::cout << comparator(12,1) << std::endl;

    return true;
}
*/