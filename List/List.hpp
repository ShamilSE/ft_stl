#ifndef LIST_HPP
#define LIST_HPP

#include "Node.hpp"
#include <iostream>

template <typename T>
class	List {
	private:
		size_t		_size;
		Node<T>*	_first;
		Node<T>*	_last;

	public:
		// constructors
		List() {
			_size = 0;
			_first = nullptr;
			_last = nullptr;
			std::cout << "hello world" << std::endl;
		}
		List(const List & other);
		List& operator=(const List & other);
		~List() {};

		// members
		void	push_back(T const & content) {
			Node<T> *new_node = new Node<T>(content);
			_last = new_node;
			_size++;
		}

		// getters
		size_t	size() const {return _size;}
		T const & getLast() {return _last->getContent();}
};

#endif