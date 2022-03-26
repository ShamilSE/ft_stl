#pragma once

#include <iostream>

template<typename T1, typename T2>
struct node {
public:
    node* l;
    node* r;
    bool is_last;

    ft::pair<T1, T2> pair;
    node(): pair(ft::make_pair(0, 0)), is_last(true) {}
    node(ft::pair<T1, T2> b): pair(b), is_last(true) {
        std::cout << "node created" << std::endl;
    }
};
