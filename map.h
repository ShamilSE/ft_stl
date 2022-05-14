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

        /*
         * TODO:
         *  operator=
         *
         */

        typedef ft::pair<const Key, Tp> value_type;
        typedef Compare                 key_compare;

    public:
        explicit map(const Compare& comp = Compare(), Allocator allocator = Allocator())
            : _allocator(allocator),
              _comparator(comp),
              _size(0)
        {
            typename Allocator::template rebind<avl_tree<Key, Tp, Compare, Allocator> >::other avlTreeAllocator;
            _tree = avlTreeAllocator.allocate(1);
            new(_tree) avl_tree<Key, Tp, Compare, Allocator>;
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

            value_type& operator* () { return currentNode->pair; }

            value_type* operator->() { return &currentNode->pair; }

            void setCurrentNode(node<Key, Tp>* node) { this->currentNode = node; }

            bool isEnd;
        };

        class value_compare
        {
        public:
            key_compare    _comp;
            value_compare(const key_compare &c) : _comp(c) {}
            bool    operator ()(const value_type& lhs, const value_type& rhs) const
            {
                return _comp(lhs.first, rhs.first);
            }
        };

    private:
        bool isKeysEqual(const Key& firstKey, const Key& secondKey) const
        {
            return !_comparator(firstKey, secondKey)
                && !_comparator(secondKey, firstKey);
        }

    public:

        ft::pair<iterator, bool> insert(const value_type& value)
        {
            bool inserted = _tree->insert(value);
            iterator it = end();
            if (inserted) {
                _size++;
                it = find(value.first);
            }
            return ft::make_pair(it, inserted);
        }

        iterator find(const Key& key)
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
                    (isKeysEqual(currentNode->pair.first, key))
                    ||
                    (currentNode == _tree->getTailNode())
                   )
                {
                    iterator it = iterator(_tree);
                    it.setCurrentNode(currentNode);
                    return it;
                }
                else if (!_comparator(currentNode->pair.first, key))
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

        const iterator find(const Key& key) const
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
                        (isKeysEqual(currentNode->pair.first, key))
                        ||
                        (currentNode == _tree->getTailNode())
                        )
                {
                    iterator it = iterator(_tree);
                    it.setCurrentNode(currentNode);
                    return it;
                }
                else if (!_comparator(currentNode->pair.first, key))
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

            return element.currentNode->pair.second;
        }

        const Tp& at( const Key& key ) const
        {
            iterator element = find(key);
            if (element.currentNode == _tree->getTailNode()) throw std::out_of_range("");

            return element.currentNode->pair.second;
        }

        Tp& operator[]( const Key& key )
        {
            iterator el = find(key);
            if (el.currentNode->isTail) {
                return insert(ft::make_pair(key, Tp())).first.currentNode->pair.second;
            }
            return el.currentNode->pair.second;
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
            node<Key, Tp>* nodeToDelete = find(pos.currentNode->pair.first).currentNode;

            if (nodeToDelete == _tree->getTailNode()) { return ; }

            node<Key, Tp>* replacement = _tree->findReplacement(pos.currentNode);
            if (replacement == _tree->getTailNode()) // если не нашли замену
            {
                // уничтожить элемент
                // ссылку у родителя постовить на tail
                if (nodeToDelete->parent != _tree->getTailNode())
                {
                    if (
                        nodeToDelete->parent->l != _tree->getTailNode() &&
                        isKeysEqual(nodeToDelete->parent->l->pair.first, nodeToDelete->pair.first)
                       )
                    {
                        nodeToDelete->parent->l = _tree->getTailNode();
                    }
                    else
                    {
                        nodeToDelete->parent->r = _tree->getTailNode();
                    }
                }
                if (nodeToDelete == _tree->getHeadNode()) {
                    _tree->setHeadNode(_tree->getTailNode());
                }
                _tree->eraseNode(nodeToDelete);
                _size--;
                return ;
            }

            if (nodeToDelete->parent != _tree->getTailNode())
            {
                // if nodeToDelete is right (position) child
                if (isKeysEqual(nodeToDelete->parent->r->pair.first, nodeToDelete->pair.first))
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
            else
            {
                node<Key, Tp>* tmpHead = _tree->getHeadNode();
                if (
                        tmpHead->l != _tree->getTailNode() &&
                        isKeysEqual(tmpHead->l->pair.first, nodeToDelete->pair.first)
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

        /*
         * Exchanges the contents of the container with those of other.
         * Does not invoke any move, copy, or swap operations on individual elements.
         */
        void swap( map& other )
        {
            avl_tree<Key, Tp, Compare, Allocator>* tmp = this->_tree;;
            this->_tree = other._tree;
            other._tree = tmp;
        }

        /* Returns the function object that compares the keys,
         * which is a copy of this container's constructor argument comp.
        */
        key_compare key_comp() const
        {
            return _comparator;
        }

        /*
         * Returns a function object that compares objects of type std::map::value_type (key-value pairs)
         * by using key_comp to compare the first components of the pairs.
         */
        value_compare value_comp() const
        {
            return value_compare();
        }

        //Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
        iterator lower_bound( const Key& key )
        {
            iterator it = find(key);
            return it;
        }

        //Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
        const iterator lower_bound( const Key& key ) const
        {
            iterator it = find(key);
            return it;
        }

        //Returns an iterator pointing to the first element that is greater than key.
        iterator upper_bound( const Key& key )
        {
            iterator it = find(key);
            it++;
            return it;
        }

        //Returns an iterator pointing to the first element that is greater than key.
        const iterator upper_bound( const Key& key ) const
        {
            iterator it = find(key);
            it++;
            return it;
        }

        /*
         * Returns a range containing all elements with the given key in the container.
         * The range is defined by two iterators, one pointing to the first element that is not less than key and another pointing to the first element greater than key.
         * Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
         */
        std::pair<iterator,iterator> equal_range( const Key& key )
        {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        const std::pair<iterator,iterator> equal_range( const Key& key ) const
        {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        //iterator

        iterator begin() { return iterator(getTree()); }
        iterator end() { return iterator(_tree, true); };

    };// class map


}// namespace ft
