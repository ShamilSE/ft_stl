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

    private:
        bool isKeysEqual(const Key& firstKey, const Key& secondKey)
        {
            return !_comparator(firstKey, secondKey)
                && !_comparator(secondKey, firstKey);
        }

    public:

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
                    (isKeysEqual(currentNode->pair->first, key))
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

        void erase(iterator pos)
        {
            node<Key, Tp>* currentNode = find(pos.currentNode->pair->first).currentNode;

            if (currentNode == _tree->getTailNode()) {
                return ;
            }

            node<Key, Tp>* replacement = _tree->findReplacement(pos.currentNode);
            if (replacement == _tree->getTailNode())
            {
                // уничтожить элемент
                // ссылку у родителя постовить на tail
                if (currentNode->parent != nullptr)
                {
                    if (
                        currentNode->parent->l != _tree->getTailNode() &&
                        isKeysEqual(currentNode->parent->l->pair->first, currentNode->pair->first)
                       )
                    {
                       currentNode->parent->l = _tree->getTailNode();
                    }
                    else
                    {
                        currentNode->parent->r = _tree->getTailNode();
                    }
                }
                pos.currentNode->~node();
                _size--;
                return ;
            }

            if (isKeysEqual(replacement->parent->r->pair->first, currentNode->pair->first))
            {
                if (currentNode->l != _tree->getTailNode())
                {
                    replacement->parent->r = currentNode->l;
                }
            }
            else
            {
                if (currentNode->r != _tree->getTailNode())
                {
                    replacement->parent->l = currentNode->r;
                }
            }

            // replace parent
            if (currentNode->parent != nullptr)
            {
                replacement->parent = currentNode->parent;
                if (
                        currentNode->parent->r != _tree->getTailNode() &&
                        isKeysEqual(currentNode->parent->r->pair->first, currentNode->pair->first)
                   )
                {
                    replacement->parent->r = replacement;
                }
                else
                {
                    replacement->parent->l = replacement;
                }
            }
            //

            replacement->l = currentNode->l;
            replacement->r = currentNode->r;

            pos.currentNode->~node();
            _size--;
        }

        iterator begin() { return iterator(getTree()); }
        iterator end() { return iterator(_tree, true); };

    };// class map


}// namespace ft
