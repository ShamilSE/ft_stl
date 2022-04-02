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
        typedef Key     key_type;
        typedef Tp      value_type;
        typedef Compare key_compare;
        avl_tree<key_type, value_type, key_compare, Allocator>* _tree;
    private:
        Allocator                               _allocator;
        static key_compare                      _comparator;

    public:
        map(const key_compare& comp = key_compare(), Allocator allocator = Allocator())
        {
            (void)comp;
            _allocator = allocator;
            _tree = new avl_tree<Key, Tp, Compare, Allocator>;
            std::cout << "constructor for empty map" << std::endl;
        }

        ft::pair<key_type, value_type> insert(const value_type& val)
        {
            std::cout << "insert new value " << val << std::endl;
            ft::pair<Key, Tp>* new_pair = ft::make_pair(1, val, _allocator);
            _tree->insert(new_pair);
            return *new_pair;
        }

        class iterator {
            //итератор должен хранить поинтер на текущий элемент
            iterator(avl_tree<key_type, value_type , key_compare, Allocator> tree, key_compare comp = _comparator)
            {
                node<key_type, value_type> & head = tree.getHeadNode();
                // должна быть отдельный функционал для сравнения key_value двух нод
                comp(head.pair.second, head.l->pair);
            }
        };
    };// class map


}// namespace ft
