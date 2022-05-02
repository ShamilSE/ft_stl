#pragma once

#include "ft.h"
#include "avl_tree.h"
#include "node.h"
#include <iostream>
#include <stdexcept>

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
        // memory allocation using allocator

    public:
        explicit map(const Compare& comp = Compare(), Allocator allocator = Allocator())
            : _allocator(allocator),
              _comparator(comp),
              _size(0)
        {
            typename Allocator::template rebind<avl_tree<Key, Tp, Compare, Allocator>>::other avlTreeAllocator;
            _tree = avlTreeAllocator.allocate(1);
            new(_tree) avl_tree<Key, Tp, Compare, Allocator>;
        }

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
        bool isKeysEqual(const Key& firstKey, const Key& secondKey) const
        {
            return !_comparator(firstKey, secondKey)
                && !_comparator(secondKey, firstKey);
        }

    public:

        iterator find(const Key& key) const
        {
            node<Key, Tp> *currentNode;
            if (_size == 0) {
                iterator it = iterator(_tree, true);
                return it;
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
                    if (currentNode == _tree->getTailNode()) return iterator(_tree, true);
                }
            }
        }

        size_t max_size() { return _tree->max_size(); }

        Allocator get_allocator() const { return _allocator; }

        Tp& at( const Key& key )
        {
            iterator element = find(key);
            if (element.currentNode == _tree->getTailNode()) throw std::out_of_range("");

            return element.currentNode->pair->second;
        }

        const Tp& at( const Key& key ) const
        {
            iterator element = find(key);
            if (element.currentNode == _tree->getTailNode()) throw std::out_of_range("");

            return element.currentNode->pair->second;
        }

        Tp& operator[]( const Key& key )
        {
            iterator el = find(key);
            if (el.currentNode != _tree->getTailNode()) return el.currentNode->pair->second;
            return insert(ft::make_pair(key, Tp())).second;
        }

        size_t count( const Key& key ) const
        {
            if (find(key).isEnd) return 0;
            return 1;
        }

        void clear()
        {
            while (_size != 0)
            {
                erase(begin());
            }
        }

        void erase(iterator pos)
        {
            node<Key, Tp>* nodeToDelete = find(pos.currentNode->pair->first).currentNode;

            if (nodeToDelete == _tree->getTailNode()) { return ; }

            node<Key, Tp>* replacement = _tree->findReplacement(pos.currentNode);
            if (replacement == _tree->getTailNode())
            {
                // уничтожить элемент
                // ссылку у родителя постовить на tail
                if (nodeToDelete->parent != _tree->getTailNode())
                {
                    if (
                        nodeToDelete->parent->l != _tree->getTailNode() &&
                        isKeysEqual(nodeToDelete->parent->l->pair->first, nodeToDelete->pair->first)
                       )
                    {
                        nodeToDelete->parent->l = _tree->getTailNode();
                    }
                    else
                    {
                        nodeToDelete->parent->r = _tree->getTailNode();
                    }
                }
                _tree->eraseNode(nodeToDelete);
                _size--;
                return ;
            }

            if (nodeToDelete->parent != _tree->getTailNode())
            {
                // if nodeToDelete is right (position) child
                if (isKeysEqual(nodeToDelete->parent->r->pair->first, nodeToDelete->pair->first))
                {
                    nodeToDelete->parent->r = replacement;
                    replacement->parent = nodeToDelete->parent;
                }
                else
                {
                    nodeToDelete->parent->l = replacement;
                    replacement->parent = nodeToDelete->parent;
                }
                _tree->eraseNode(nodeToDelete);
                _size--;
            }

            if (nodeToDelete->parent == _tree->getTailNode())
            {
                node<Key, Tp>* tmpHead = _tree->getHeadNode();
                if (
                        tmpHead->l != _tree->getTailNode() &&
                        isKeysEqual(tmpHead->l->pair->first, nodeToDelete->pair->first)
                   )
                {
                    replacement->r = tmpHead->r;
                    tmpHead->r->parent = replacement;
                }
                else
                {
                    replacement->l = tmpHead->l;
                    tmpHead->r->parent = replacement;
                }
                _tree->eraseNode(tmpHead);
                _tree->setHeadNode(replacement);
                _size--;
            }

        }

        iterator begin() { return iterator(getTree()); }
        iterator end() { return iterator(_tree, true); };

    };// class map


}// namespace ft
