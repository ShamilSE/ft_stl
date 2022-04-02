#pragma once

#include "node.h"

template<typename T1, typename T2, typename Comp, typename Allocator>
class avl_tree {
private:
    node<T1, T2>*   head;
    Comp            comparator;
public:
    avl_tree()
    {
        head = nullptr;
        std::cout << "avl constructor 1" << std::endl;
    }

    void insert(ft::pair<T1, T2>& new_pair)
    {
        if (head == nullptr) {
            head = new node<T1, T2>(new_pair);
        }
        else {
            const bool side = comparator(head->pair->first, new_pair.first);
            std::cout << "avl tree insert " << new_pair.second << std::endl;
            std::cout << "side is " << side << std::endl;
        }
    }

    node<T1, T2> getHeadNode() const {return head;}
};
