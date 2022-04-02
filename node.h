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
    node(ft::pair<T1, T2>& pair) {
        l = nullptr;
        r = nullptr;
        is_last = true;
        this->pair = &pair;
        std::cout << "node created" << std::endl;
    }
};
