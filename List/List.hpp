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

            T& operator*() {
                if (node)
                    return node->_content;
                else {
                    Node<T>* newNode = new Node<T>;
                    newNode->_content = 0;
                    return newNode->_content;
                }
            }
    };


    template<typename T>
    class list {
        private:
            Node<T>*    _emptyNode;
            Node<T>*    _first;
            Node<T>*    _last;
            size_t      _size;

        public:
            typedef Node<T> node;
            typedef ListIterator<T> iterator;

            void initList() {
                _emptyNode = new Node<T>;
                _emptyNode->_content = 0;
                _emptyNode->next = nullptr;
                _emptyNode->prev = nullptr;
                _size = 0;
                _first = nullptr;
                _last = nullptr;
            }

            iterator begin() {return ListIterator<T>(_first);}

            void push_front(const T & val) {
                Node<T>* newNode = new Node<T>();
                newNode->_content = val;
                if (_first) {
                    _first->prev = newNode;
                    newNode->next = _first;
                    _first = newNode;
                }
                else {
                    _first = newNode;
                }
                _size++;
            }

            void pop_front() {
                if (_first) {
                    Node<T>* tmp = nullptr;
                    if (_first->next)
                        tmp = _first->next;
                    delete _first;
                    if (tmp)
                        _first = tmp;
                    else
                        _first = nullptr;
                    _size--;
                }
            }

            list() {
                initList();
            }
    };
}

#endif