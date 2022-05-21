#include <map>
#include "map.h"
#include <iostream>
#include <gtest/gtest.h>


TEST(map, iterator_test) {
    ft::map<int, int> a;
    a.insert(ft::make_pair(10, 5));
    a.insert(ft::make_pair(5, 4));
    a.insert(ft::make_pair(13, 9));
    a.insert(ft::make_pair(14, 16));
    a.insert(ft::make_pair(12, 16));

    std::map<int, int> origin;
    origin.insert(std::make_pair(10, 5));
    origin.insert(std::make_pair(5, 4));
    origin.insert(std::make_pair(13, 9));
    origin.insert(std::make_pair(14, 16));
    origin.insert(std::make_pair(12, 16));

    ft::map<int,int>::iterator ftIt = a.begin();
    std::map<int,int>::iterator stdIt = origin.begin();

    while (stdIt != origin.end()) {
        EXPECT_EQ(ftIt->second, stdIt->second);
        ftIt++;
        stdIt++;
    }
}
TEST(map, iterator_test_2) {
    ft::map<int, int> my_map;

    my_map.insert(ft::make_pair(10, 5));
    my_map.insert(ft::make_pair(12, 6));
    my_map.insert(ft::make_pair(13, 7));
    my_map.insert(ft::make_pair(14, 8));
    my_map.insert(ft::make_pair(15, 9));
    my_map.insert(ft::make_pair(5, 1000));

    EXPECT_EQ(my_map.end()->second, 0);
}


TEST(map, find_method) {
    ft::map<int, int> my_map;

    my_map.insert(ft::make_pair(1, 5));
    my_map.insert(ft::make_pair(2, 6));
    my_map.insert(ft::make_pair(3, 7));
    my_map.insert(ft::make_pair(4, 8));

    ft::map<int,int>::iterator it =  my_map.find(1);
    EXPECT_EQ(it->second, 5);
}

TEST(map, find_method_2) {
    ft::map<int, int> my_map;

    my_map.insert(ft::make_pair(1, 5));
    my_map.insert(ft::make_pair(2, 6));
    my_map.insert(ft::make_pair(3, 7));
    my_map.insert(ft::make_pair(4, 8));

    ft::map<int,int>::iterator it =  my_map.find(10);
    EXPECT_EQ(it.isEnd, true);
}

TEST(map, erase_method) {
    ft::map<int, int> my_map;

    my_map.insert(ft::make_pair(1, 5));
    my_map.insert(ft::make_pair(2, 6));
    my_map.insert(ft::make_pair(3, 7));
    my_map.insert(ft::make_pair(4, 8));

    ft::map<int, int>::iterator it = my_map.begin();
    it++;
    my_map.erase(it);

    ft::map<int,int>::iterator it2 = my_map.find(2);

    EXPECT_EQ(it2.currentNode->isTail, true);
}

TEST(map, at_method)
{
    ft::map<int, int>* my_map = new ft::map<int, int>();

    my_map->insert(ft::make_pair(1,10));
    my_map->insert(ft::make_pair(2,2));

    int a = my_map->at(1);
    EXPECT_EQ(a, 10);

    try
    {
        my_map->at(3);
    }
    catch (std::out_of_range&) {}
}

TEST(map, count_method) {

    ft::map<int, int>* my_map = new ft::map<int, int>();

    my_map->insert(ft::make_pair(1,1));
    EXPECT_EQ(my_map->count(1), 1);
    EXPECT_EQ(my_map->count(2), 0);
}

TEST(map, insert_method) {
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));

    ft::pair<ft::map<int,int>::iterator, bool> pair = my_map->insert(ft::make_pair(2,2));
    EXPECT_EQ(pair.first->second, 2);
    EXPECT_EQ(pair.second, true);
}

TEST(map, brackets) {
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    (*my_map)[2];

    EXPECT_EQ(my_map->find(2)->second, 0);
}

TEST(map, begin_iterator) {
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(5,5));
    my_map->insert(ft::make_pair(-10,-10));

    ft::map<int,int>::iterator it = my_map->begin();

    EXPECT_EQ(it->first, -10);
}

TEST(map, clear_method) {
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(5,5));
    my_map->insert(ft::make_pair(-10,-10));
    my_map->insert(ft::make_pair(-500,-500));

    my_map->clear();
    EXPECT_EQ(my_map->_tree->getHeadNode()->isTail, true);
}

TEST(map, swap_method) {
    ft::map<int,int>* my_map = new ft::map<int,int>();
    ft::map<int,int>* my_map2 = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(2,2));
    my_map->insert(ft::make_pair(3,3));

    my_map2->insert(ft::make_pair(4,4));
    my_map2->insert(ft::make_pair(5,5));
    my_map2->insert(ft::make_pair(6,6));

    my_map->swap(*my_map2);

    EXPECT_EQ(my_map->begin()->second, 4);
}


TEST(map, compare_method) {
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(5,5));
    std::less<int> comparator = my_map->key_comp();

    EXPECT_EQ(comparator(1,12), 1);
    EXPECT_EQ(comparator(12,1), 0);
}

TEST(map, element_already_inserted)
{
    ft::map<int,int>* my_map = new ft::map<int, int>();

    ft::pair<ft::map<int,int>::iterator, bool> p = my_map->insert(ft::make_pair(1,1));
    EXPECT_EQ(p.second, true);
    p = my_map->insert(ft::make_pair(1,1));
    EXPECT_EQ(p.second, false);
}

TEST(map, iterator)
{
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(2,2));

    ft::map<int,int>::iterator it = my_map->end();
    EXPECT_EQ(it->first, 0);

    it--;
    EXPECT_EQ(it->first, 2);
}

TEST(map, reverse_iterator)
{
    ft::map<int,int>* my_map = new ft::map<int,int>();

    my_map->insert(ft::make_pair(1,1));
    my_map->insert(ft::make_pair(2,2));

    ft::map<int,int>::reverse_iterator rit = my_map->rbegin();
    EXPECT_EQ(rit->first, 2);
    rit++;
    EXPECT_EQ(rit->first, 1);
}
