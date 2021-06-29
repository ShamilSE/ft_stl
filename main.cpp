#include "list/list.hpp"
#include <list>
#include <vector>
#include "SomeClass.hpp"
#include <iostream>


int	main(void) {
    ft::list<int> list;

    list.push_front(5);
    list.push_back(50);
    list.push_front(0);
    list.push_back(150);
    list.push_back(500);
    list.push_front(-200);
    list.push_front(-250);
    list.push_front(-300);

    ft::list<int>::iterator start = list.begin();
    ft::list<int>::iterator end = list.end();

    while (start != end) {
        std::cout << *start << std::endl;
        start++;
    }

}
