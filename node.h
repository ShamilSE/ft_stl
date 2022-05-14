#pragma once

#include <iostream>

template<typename T1, typename T2>
struct node {
public:
    bool isTail;
    node* parent;
    node* l;
    node* r;
    ft::pair<const T1, T2> pair;

    node(node* tailNode, bool isTail = false, ft::pair<T1, T2> pair = ft::make_pair(T1(), T2())) : pair(pair)
    {
        parent = tailNode;
        l = tailNode;
        r  = tailNode;
        this->isTail = isTail;
    }

    node(const ft::pair<T1, T2>& pair, node* tailNode, bool isTail = false) : pair(pair) {
        parent = tailNode;
        l = tailNode;
        r = tailNode;
        this->isTail = isTail;
    }

    ~node() {}
};
