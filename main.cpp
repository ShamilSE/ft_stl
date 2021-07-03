#include "vector/vector.hpp"
#include <list>
#include <vector>
#include "SomeClass.hpp"
#include <iostream>

void push_back() {
	ft::vector<SomeClass> vector;
	SomeClass some("name", 2112);

	vector.push_back(some);
	std::cout << "hello world" << std::endl;
}

void memory_dup_check() {
	std::vector<SomeClass> vector;
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
	ft::vector<int> vector;

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	// vector.insert(vector.begin() + vector.size(), 0);
	// vector.insert(vector.begin(), 1000);

	ft::vector<int>::iterator start = vector.begin();
	ft::vector<int>::iterator end = vector.end();


	while (start != end) {
		std::cout << *start << std::endl;
		++start;
	}
}

void iterator_operator_origin() {
	std::cout << "========= origin =========" << std::endl;
	std::vector<int> vector;

	vector.push_back(1);

}

int main(void) {
//	std::cout << "======================" << std::endl;
//	std::cout << "my output" << std::endl;
//	std::cout << "======================" << std::endl;
//	memory_dup_check_my();
//	std::cout << "======================" << std::endl;
//	std::cout << "original output" << std::endl;
//	std::cout << "======================" << std::endl;
//	memory_dup_check();

//	pop_back_my();

//	index_operator_check_my();

//	simple_types_test_my();

	// iterator_test_my();
	// iterator_test_origin();

	iterator_operator_my();
	// iterator_operator_origin();
//	while(1);
	return 0;
}
