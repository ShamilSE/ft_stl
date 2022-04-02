#pragma once

#include "node.h"

template<typename T1, typename T2, typename Comp, typename Allocator>
class avl_tree {
private:
    node<T1, T2>*   head;
    Allocator       allocator;
    Comp            comparator;
public:
    avl_tree()
    {
        head = new node<T1, T2>;
        std::cout << "avl constructor 1" << std::endl;
    }

    avl_tree(ft::pair<T1, T2> pair, Comp comparator)
    {
        allocator.allocate(1);
        head(pair);
        this->comparator = comparator;
        std::cout << "avl constructor 2" << std::endl;
    }

    void insert(ft::pair<T1, T2> new_pair)
    {
        if (head == nullptr) {
            head = node<T1, T2>(new_pair);
        }
        else {
            comparator(head->pair->first, new_pair.first);
        }
    }

    node<T1, T2> getHeadNode() const {return head;}
};
