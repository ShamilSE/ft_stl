#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <memory>

namespace ft {

    template <typename T>
    struct	Node {
        Node(): next(nullptr), prev(nullptr) {}
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
            Node<T>*    _emptyNode;
            Node<T>*    _first;
            Node<T>*    _last;
            size_t      _size;

        public:
            typedef ListIterator<T> iterator;

            void initList() {
                _emptyNode = new Node<T>;
                _emptyNode->_content = _size;
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
                if (_last && _size == 1) {
                    _first->next = _last;
                    _last->prev = _first;
                }
                _emptyNode->next = _first;
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

            void push_back(const T& value) {
                Node<T>* newNode =  new Node<T>;
                newNode->_content = value;
                if (_last) {
                    _last->next = newNode;
                    newNode->prev = _last;
                    _last = newNode;
                }
                else {
                    _last = newNode;
                }
                if (_first && _size == 1) {
                    _last->prev = _first;
                    _first->next = _last;
                }
                _size++;
            }

            void pop_back() {
                if (_last) {
                    Node<T>* tmp = nullptr;
                    if (_last->prev)
                        tmp = _last->prev;
                    delete _last;
                    if (tmp)
                        _last = tmp;
                    else
                        _last = nullptr;
                    _size--;
                }
            }

            list() {
                initList();
            }
    };
}

#endif