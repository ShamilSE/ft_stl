#include "List/List.hpp"
#include <list>
#include <vector>
#include <memory>

int	main(void) {
	List<int> list;
	// std::list<int> list;
	std::cout << list.size() << std::endl;
	list.push_back(5);
	list.push_back(10);
	std::cout << list.getLast() << std::endl;
	std::cout << list.size() << std::endl;
	std::cout << list.getFirst() << std::endl;

	return 0;
}