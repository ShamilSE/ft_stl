#include "list/list.hpp"
#include <list>
#include <vector>
#include <memory>

int	main(void) {
    ft::list<int> list;
    list.push_front(5);

    ft::list<int>::iterator start = list.begin();
    (void)start;
    std::cout << *start << std::endl;
}