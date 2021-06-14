#include "List/List.hpp"
#include <list>
#include <vector>
#include <memory>

int	main(void) {
	List<int> list;
	// std::list<int> list;
	std::cout << list.size() << std::endl;
	list.push_back(5);
	std::cout << list.getLast() << std::endl;
	return 0;
}