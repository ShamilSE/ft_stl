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

void test2() {
    ft::list<int> list;

    list.push_front(23423);
    list.push_back(3232);
}

void test3() {
    ft::list<int> list;

    list.push_back(34);
    list.push_back(43);

    ft::list<int>::iterator pos = list.begin() + 1;

    ft::list<int>::iterator a = list.insert(pos, 41);

    ft::list<int>::iterator start = list.begin();
    ft::list<int>::iterator end = list.end();

    while (start != end) {
        std::cout << *start << std::endl;
        start++;
    }
    std::cout << *a << std::endl;
}

int	main(void) {
//    test();
//    test2();
//    test3();
//    while (1);
}
