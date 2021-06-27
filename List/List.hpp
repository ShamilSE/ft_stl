#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <memory>

namespace ft {

    template <typename T>
    struct	Node {
        T           _content;
        Node<T>*	next;
        Node<T>*	prev;
    };

    template <typename T>
    class ListIterator {
        private:
            Node<T>* node;

        public:
            ListIterator(Node<T>* n): node(n) {}

            T& operator*() {return node->_content;}
    };


    template<typename T>
    class list {
        private:
            Node<T>*    _first;
            Node<T>*    _last;
            size_t      _size;
            bool        _empty;

        public:
            typedef Node<T> node;
            typedef ListIterator<T> iterator;

            void initList() {
                _size = 0;
                _empty = false;
                _first = nullptr;
                _last = nullptr;
            }

            iterator begin() {return ListIterator<T>(_first);}

            void push_front(const T & val) {
                Node<T>* newNode = new Node<T>();
                newNode->_content = val;
                if (_first)
                    _first->prev = newNode;
                else
                    _first = newNode;
            }

            list() {
                initList();
            }
    };
}

#endif