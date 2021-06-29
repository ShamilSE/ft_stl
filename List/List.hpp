#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <memory>

namespace ft {

    template <typename T>
    struct	Node {
        Node(T* content): _content(*content), next(nullptr), prev(nullptr) {}

        ~Node() {
            delete _content;
            std::cout << "delete node" << std::endl;
        }

        T&    _content;
        Node<T>*	next;
        Node<T>*	prev;
    };

    template <typename T>
    class ListIterator {
        public:
            Node<T>* node;
            explicit ListIterator(Node<T>* n): node(n) {}

            T& operator*() {return node->_content;}

            ListIterator operator++() {
                if (node->next)
                    node = node->next;
                return *this;
            }

            ListIterator operator++(int) {
                if (node->next)
                    node = node->next;
                return *this;
            }

            ListIterator operator--() {
                if (node->prev)
                    node = node->prev;
                return *this;
            }

            ListIterator operator--(int) {
                if (node->prev)
                    node = node->prev;
                return *this;
            }

            bool operator==(const ListIterator<T> & iterator) {return iterator.node == node;}

            bool operator!=(const ListIterator<T> & iterator) {return iterator.node != node;}

            bool operator<(const ListIterator<T> & iterator) {return iterator.node < node;}

            bool operator<=(const ListIterator<T> & iterator) {return iterator.node <= node;}

            bool operator>(const ListIterator<T> & iterator) {return iterator.node > node;}

            bool operator>=(const ListIterator<T> & iterator) {return iterator.node >= node;}

            ListIterator<T> operator+(int n) {
                for (int index = 0; index < n; index++)
                    node = node->next;
                return *this;
            }

            ListIterator<T> operator-(int n) {
                for (int index = 0; index < n; index++)
                    node = node->prev;
                return *this;
            }
    };


    template<typename T>
    class list {
        private:
            Node<T>*    _emptyNode;
            Node<T>*    _first;
            Node<T>*    _last;
            size_t      _size;

            void initList() {
                _size = 0;
                _emptyNode = new Node<T>(nullptr);
                _first = nullptr;
                _last = nullptr;
            }

        public:
            typedef ListIterator<T> iterator;

            size_t size() const {return _size;}
            iterator begin() {return ListIterator<T>(_first);}
            iterator end() {return ListIterator<T>(_emptyNode);}

            void push_front(const T & val) {
                T* content = new T(val);
                Node<T>* newNode = new Node<T>(content);
                if (_first) {
                    if (_size == 1 && !_last)
                        _last = _first;
                    _first->prev = newNode;
                    newNode->next = _first;
                    _first = newNode;
                }
                else
                    _first = newNode;
                if (_last && _size == 1) {
                    _first->next = _last;
                    _last->prev = _first;
                }
                _emptyNode->prev = _first;
                _emptyNode->next = _last;
                _first->prev = _emptyNode;
                if (_last)
                    _last->next = _emptyNode;
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

            void push_back(const T& val) {
                T* content = new T(val);
                Node<T>* newNode = new Node<T>(content);
                if (_last) {
                    if (_size == 1 && !_first)
                        _first = _last;
                    _last->next = newNode;
                    newNode->prev = newNode;
                    _last = newNode;
                }
                else
                    _last = newNode;
                if (_first && _size == 1) {
                    _last->prev = _first;
                    _first->next = _last;
                }
                _emptyNode->prev = _first;
                _emptyNode->next = _last;
                _last->next = _emptyNode;
                if (_first)
                    _first->prev = _emptyNode;
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

            iterator insert( iterator pos, const T& value ) {
                Node<T>* newNode = new Node<T>;
                newNode->_content = value;

                list<T>::iterator prev = pos - 1;
                list<T>::iterator next = pos + 1;

                prev.node->next = newNode;
                next.node->prev = newNode;

                newNode->prev = prev.node;
                newNode->next = next.node;

                return --pos;
            }

            iterator erase(iterator pos) {
                Node<T>* node = pos.node;
                iterator next_element = ++pos;

                node->prev->next = node->next;
                node->next->prev = node->prev;

                delete node;
                node = nullptr;
                return next_element;
            }

            iterator erase( iterator first, iterator last ) {
                list<T>::iterator iterator;
                while (first != last)
                    iterator = erase(first++);
                return iterator;
            }

            void clear() {
                list<T>::iterator start = begin();
                list<T>::iterator end = end();
                erase(start, end);
            }

            list() {
                initList();
            }
            ~list() {
                std::cout << "list destructor called" << std::endl;
            }
    };
}

#endif