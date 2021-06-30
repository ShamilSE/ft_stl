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

int main(void) {
//	std::cout << "======================" << std::endl;
//	std::cout << "my output" << std::endl;
//	std::cout << "======================" << std::endl;
//	memory_dup_check_my();
//	std::cout << "======================" << std::endl;
//	std::cout << "original output" << std::endl;
//	std::cout << "======================" << std::endl;
//	memory_dup_check();


	index_operator_check_my();
//	while(1);
	return 0;
}