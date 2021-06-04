#ifndef LIST_HPP
#define LIST_HPP

#include "Link.hpp"

template <typename T>
class	List {
	private:
		Link<T>*	first;
		Link<T>*	last;

	public:
		List() {

		}
		List(const List & other);
		List& operator=(const List & other);
		~List() {};

		// void	push_back(T* element) {
		// 	first = element;
		// }
};

#endif