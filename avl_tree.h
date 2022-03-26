#pragma once

#include "node.h"

template<typename T1, typename T2, typename Comp >
class avl_tree {
private:
    node<T1, T2>* head;
public:
    avl_tree()
    : head(ft::make_pair(0, 0))
    {
        std::cout << "avl constructor 1" << std::endl;
    }

    avl_tree(ft::pair<T1, T2> pair, Comp comparator)
    : head(pair)
    {
        (void)comparator;
        std::cout << "avl constructor 2" << std::endl;
    }

    node<T1, T2> getHeadNode() const {return head;}
};
