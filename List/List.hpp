#ifndef LIST_HPP
#define LIST_HPP

#include <string>

template <typename T>
class	List {
	private:

	public:
		List() {

		}
		List(const List & other);
		List& operator=(const List & other);
		~List() {};
};

#endif