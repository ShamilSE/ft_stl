#pragma once

#include <iostream>

template<typename T1, typename T2>
struct node {
public:
    node* l;
    node* r;
    bool is_last;
    ft::pair<T1, T2>* pair;

    node(){

    }
    node(ft::pair<T1, T2> b): pair(b), is_last(true) {
        l = nullptr;
        r = nullptr;
        std::cout << "node created" << std::endl;
    }
};
