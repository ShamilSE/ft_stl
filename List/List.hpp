#ifndef LIST_HPP
#define LIST_HPP

#include "Node.hpp"
#include <iostream>

namespace ft
{
	template <typename T>
	class	list {
		private:
			size_t		_size;
			Node<T>*	_first;
			Node<T>*	_last;

		public:
			// constructors
			list() {
				_size = 0;
				_first = nullptr;
				_last = nullptr;
			}
			list(const list & other);
			list& operator=(const list & other);
			~list() {};

			// members
			void	push_back(T const & content) {
				Node<T> *new_node = new Node<T>(content);
				if (_last) {
					new_node->prev = _last;
					_last->next = new_node;
					if (!_first) {
						_first = _last;
					}
				}
				_last = new_node;
				new_node->next = nullptr;
				_size++;

			}

			// getters
			size_t	size() const {return _size;}
			T const & getLast() {return _last->getContent();}
			T const & getFirst() {return _first->getContent();}

			// iterator
			class iterator {
				public:
					Node<T>*	pointer;
					
					// T const & operator*() {
					// 	Node<T>* p = it->pointer;
					// 	T& a = p->getContent();
					// 	return a;
					// }
					void	operator++() {
						// pointer = 
						// return *this;
						std::cout << "hello world" << std::endl;
					}
			};

			iterator* it;
			iterator&	begin() {
				it = new iterator;
				it->pointer = _first;
				return *it;
			}
			// iterator*	end() {return _last;}
	};
}

#endif