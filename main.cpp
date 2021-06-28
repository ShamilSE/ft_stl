#include "list/list.hpp"
#include <list>
#include <vector>
#include <memory>


int	main(void) {
    ft::list<int> list;
    list.push_front(5);
    list.push_back(10);
    list.push_back(20);
    list.push_back(25);

    ft::list<int>::iterator start = list.begin();
    ft::list<int>::iterator end = list.end();

   list.insert(end, 15);

    while (start != end) {
        std::cout << *start << std::endl;
        start++;
    }

}
