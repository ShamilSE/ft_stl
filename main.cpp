#include "list/list.hpp"
#include <list>
#include <vector>
#include <memory>

int	main(void) {
	ft::list<int> list;

	list.push_back(5);
	list.push_back(10);
	ft::list<int>::iterator it = list.begin();
	// std::cout << *it << std::endl;
	++it;
	return 0;
}