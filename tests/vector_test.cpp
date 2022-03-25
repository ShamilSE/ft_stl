#include "../vector.h"
#include "vector_test.h"
#include "../SomeClass.hpp"

#include <list>
#include <vector>
#include <stack>
#include <iostream>

void push_back() {
	ft::vector<SomeClass> vector;
	SomeClass some("name", 2112);

	vector.push_back(some);
	std::cout << "hello world" << std::endl;
}

void index_operator_check_my() {
	ft::vector<SomeClass> vector;
	SomeClass some("shamil22", 21), some2("timur", 18), some3("denis", 26);

	vector.push_back(some);
	vector.push_back(some2);
	vector.push_back(some3);
}

void pop_back_my() {
	ft::vector<SomeClass> vector;
	SomeClass* some = new SomeClass("shamil22", 21);

	vector.push_back(*some);
//	vector.push_back(some2);

	vector.pop_back();
	delete some;
};

void simple_types_test_my() {
	ft::vector<SomeClass> vector;
	SomeClass some("shamil22", 21), some2("denis", 26), some3("timur", 23);

	vector.push_back(some);
	vector.push_back(some2);
	vector.push_back(some3);
	int i = 0;
	while (i < 3) {
		std::cout << vector[i].getName() << std::endl;
		i++;
	}
//	vector.pop_back();
}

void iterator_test_my() {
	std::cout << "============= MY ITERATOR TEST =============" << std::endl;
	ft::vector<int> vector;

	vector.push_back(122);
	vector.push_back(237);
	ft::vector<int>::iterator start = vector.begin();
	ft::vector<int>::iterator end = vector.end();

	std::cout << *start << std::endl;
	std::cout << *end << std::endl;
}

void iterator_test_origin() {
	std::cout << "============= ORIGIN ITERATOR TEST =============" << std::endl;
	std::vector<int> vector;

	vector.push_back(122);
	vector.push_back(237);
	std::vector<int>::iterator start = vector.begin();
	std::vector<int>::iterator end = vector.end();

	std::cout << *start << std::endl;
	std::cout << *end << std::endl;
}

void iterator_operator_my() {
	std::cout << "========= my ==========" << std::endl;
	ft::vector<SomeClass> vector;

	SomeClass some("shamil", 22);

	vector.push_back(some);

	// vector.printAll();
	std::cout << vector[0].getName() << std::endl;
}

void iterator_operator_origin() {
	std::cout << "========= origin =========" << std::endl;
	std::vector<int> vector;

	vector.push_back(1);

}

void reverse_iterator_my() {
	std::cout << "========= my ==========" << std::endl;
	ft::vector<int> vector;

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);
	vector.push_back(6);
	vector.push_back(7);
	vector.push_back(8);
	vector.push_back(9);
	vector.push_back(10);

	ft::vector<int>::reverse_iterator rstart = vector.rbegin();
	ft::vector<int>::reverse_iterator rend = vector.rend();

	while (rstart != rend) {
		std::cout << *rstart << std::endl;
		rstart++;
	}
	std::cout << *(rstart - 4) << std::endl;
	std::cout << "memory allocated: " << vector.capacity() << std::endl;
	int index = 5;
	std::cout << "element at index " << index << " is " << vector.at(index) << std::endl;
}

void reverse_iterator_origin() {
	std::cout << "========= origin =========" << std::endl;
	std::vector<int> vector;

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);
	vector.push_back(6);
	vector.push_back(7);
	vector.push_back(8);
	vector.push_back(9);
	vector.push_back(10);

	std::vector<int>::reverse_iterator rstart = vector.rbegin();
	std::vector<int>::reverse_iterator rend = vector.rend();

	while (rstart != rend) {
		std::cout << *rstart << std::endl;
		rstart++;
	}
	std::cout << *(rstart - 4) << std::endl;
	std::cout << "memory allocated: " << vector.capacity() << std::endl;
	int index = 5;
	std::cout << "element at index " << index << " is " << vector.at(index) << std::endl;
}

void erase_method_my() {
	std::cout << "========= my =========" << std::endl;
	ft::vector<int> vector;

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);

	// vector.printAll();
	vector.erase(vector.begin(), vector.begin() + 3);
	// std::cout << "=====================" << std::endl;
	vector.printAll();


}

void erase_method_origin() {
	std::cout << "========= origin =========" << std::endl;
	std::vector<int> vector;

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);

	// vector.printAll();
	vector.erase(vector.begin(), vector.begin() + 3);
	// std::cout << "=====================" << std::endl;
	std::vector<int>::iterator start = vector.begin();
	while (start != vector.end()) {
		std::cout << *start << std::endl;
		start++;
	}
}

void swap_method_my() {
	ft::vector<int> vector;
	ft::vector<int> vector2;

	vector.push_back(1);
	vector.push_back(3);
	vector.push_back(5);

	vector2.push_back(2);
	vector2.push_back(4);
	vector2.push_back(6);

	vector.printAll();
	std::cout << "===========" << std::endl;
	vector.swap(vector2);
	vector.printAll();

}


void vector_test() {


	pop_back_my();

	index_operator_check_my();

	simple_types_test_my();

	iterator_test_my();
	iterator_test_origin();

	iterator_operator_my();
	iterator_operator_origin();

	reverse_iterator_my();
	reverse_iterator_origin();

	erase_method_my();
	erase_method_origin();

	swap_method_my();

}
