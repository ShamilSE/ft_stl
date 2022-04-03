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
        const Compare  _comparator;

        avl_tree<Key, Tp, Compare, Allocator>* getTree() { return _tree; }

        //TODO: [] operator overloading

    public:
        map(const Compare& comp = Compare(), Allocator allocator = Allocator())
            : _tree(new avl_tree<Key, Tp, Compare, Allocator>), _allocator(allocator), _comparator(comp)
        {}

        ft::pair<Key, Tp> insert(ft::pair<Key, Tp>& new_pair)
        {
            _tree->insert(new_pair);
            return new_pair;
        }

        struct iterator {
            avl_tree<Key, Tp, Compare, Allocator>* _tree;
            node<Key, Tp>* currentNode;

            iterator(avl_tree<Key, Tp, Compare, Allocator>* tree)
            : _tree(tree), currentNode(_tree->getHeadNode())
            {}

            iterator operator++ (int) {
                currentNode = _tree->nextEl(currentNode);
                return *this;
            }

            //TODO: ++ operator overloding
            //TODO: operator ++ overloding
            //TODO: -- operator overloding
            //TODO: operator -- overloding
        };

        iterator begin() { return iterator(getTree()); }
        iterator end() { return iterator(_tree->getTailNode()); }

    };// class map


}// namespace ft
