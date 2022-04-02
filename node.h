#pragma once

#include <iostream>

template<typename T1, typename T2>
struct node {
public:
    node* parent;
    node* l;
    node* r;
    ft::pair<T1, T2>* pair;

    node(){

    }
    node(ft::pair<T1, T2>& pair) {
        parent = nullptr;
        l = nullptr;
        r = nullptr;
        this->pair = &pair;
        std::cout << "node created" << std::endl;
    }
};
