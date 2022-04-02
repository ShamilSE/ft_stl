#pragma once

#include "ft.h"
#include "avl_tree.h"
#include "node.h"
#include <iostream>

namespace ft {

    template<typename Key, typename Tp, typename Compare, typename Allocator >
    class map
    {
    public:
        avl_tree<Key, Tp, Compare, Allocator>* _tree;
    private:
        Allocator       _allocator;
        static Compare  _comparator;

    public:
        map(const Compare& comp = Compare(), Allocator allocator = Allocator())
        {
            //_comparator = comp;
            //_allocator = allocator;
            (void)comp;
            (void)allocator;
            _tree = new avl_tree<Key, Tp, Compare, Allocator>;
            std::cout << "constructor for empty map" << std::endl;
        }


        ft::pair<Key, Tp> insert(ft::pair<Key, Tp>& new_pair)
        {
            std::cout << "insert new value " << new_pair.second << std::endl;
            _tree->insert(new_pair);
            return new_pair;
        }

        class iterator {
            //итератор должен хранить поинтер на текущий элемент
            iterator(avl_tree<Key, Tp , Compare, Allocator> tree)
            {
                node<Key, Tp> & head = tree.getHeadNode();
                comp(head.pair.second, head.l->pair);
            }
        };
    };// class map


}// namespace ft
