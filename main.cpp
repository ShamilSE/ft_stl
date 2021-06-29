#include "list/list.hpp"
#include <list>
#include <vector>
#include "SomeClass.hpp"
#include <iostream>


void test() {
    ft::list<SomeClass> list;
    SomeClass some("asg" , 123), some2("asf", 23);


    list.push_front(some);
    list.push_front(some2);
}

int	main(void) {
    test();
//    while (1);
}
