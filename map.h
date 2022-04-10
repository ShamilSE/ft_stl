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
        avl_tree<Key, Tp, Compare, Allocator>* getTree() { return _tree; }
    private:
        Allocator       _allocator;
        const Compare  _comparator;
        size_t _size;

        //TODO: [] operator overloading
        // begin() must return minimal element (not head)

    public:
        explicit map(const Compare& comp = Compare(), Allocator allocator = Allocator())
            : _tree(new avl_tree<Key, Tp, Compare, Allocator>),
            _allocator(allocator),
            _comparator(comp),
            _size(0)
        {}

        ft::pair<Key, Tp> insert(ft::pair<Key, Tp>& new_pair)
        {
            _tree->insert(new_pair);
            _size++;
            return new_pair;
        }

        size_t size() const { return _size; }
        bool empty() const { return _size == 0; }

        struct iterator {
            avl_tree<Key, Tp, Compare, Allocator>* _tree;
            node<Key, Tp>* currentNode;

            explicit iterator(avl_tree<Key, Tp, Compare, Allocator>* tree, bool isEnd = false)
            : _tree(tree), isEnd(isEnd)
            {
                if (isEnd == false) {
                    currentNode = _tree->getFirstNode();
                }
                else {
                    currentNode = _tree->getTailNode();
                }
            }

        public:
            iterator operator++ (int) {
                currentNode = _tree->nextEl(currentNode);
                return *this;
            }

            iterator operator++ () {
                currentNode = _tree->nextEl(currentNode);
                return *this;
            }

            iterator operator-- (int) {
                currentNode = _tree->prevEl(currentNode);
                return *this;
            }

            iterator operator-- () {
                currentNode = _tree->prevEl(currentNode);
                return *this;
            }

            bool operator== (const iterator& other) {
                return this->currentNode == other.currentNode;
            }

            bool operator!= (const iterator& other) {
                return this->currentNode != other.currentNode;
            }

            bool operator> (const iterator& other) {
                return this->currentNode > other.currentNode;
            }

            bool operator< (const iterator& other) {
                return this->currentNode < other.currentNode;
            }

            bool operator>= (const iterator& other) {
                return this->currentNode >= other.currentNode;
            }

            bool operator<= (const iterator& other) {
                return this->currentNode <= other.currentNode;
            }

            Tp operator* () {
                return currentNode->pair->second;
            }

            void setCurrentNode(node<Key, Tp>* node) { this->currentNode = node; }

            bool isEnd;
        };

        iterator find(const Key& key)
        {
            node<Key, Tp> *currentNode;
            if (_size == 0) {
                currentNode = _tree->getTailNode();
            }
            else {
                currentNode = _tree->getHeadNode();
            }

            while (true)
            {
                if (
                    (!_comparator(currentNode->pair->first, key) && !_comparator(key, currentNode->pair->first))
                    ||
                    (currentNode == _tree->getTailNode())
                   )
                {
                    iterator it = iterator(_tree);
                    it.setCurrentNode(currentNode);
                    return it;
                }
                else if (!_comparator(currentNode->pair->first, key))
                {
                    currentNode = _tree->prevEl(currentNode);
                }
                else
                {
                    currentNode = _tree->nextEl(currentNode);
                }
            }
        }

        void erase([[maybe_unused]] iterator pos)
        {

            _size--;
        }

        iterator begin() { return iterator(getTree()); }
        iterator end() { return iterator(_tree, true); };

    };// class map


}// namespace ft
