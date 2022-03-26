#include "stack.h"
#include <stack>
#include <iostream>

void insert_test_my() {
	ft::stack<int> s;

	s.push(5);
	s.push(4);
	std::cout << s.size() << std::endl;
	std::cout << s.empty() << std::endl;
	// s.pop();
	std::cout << s.size() << std::endl;
	std::cout << s.top() << std::endl;
}

void copy_constructor_test_my() {
	ft::stack<int> s;

	s.push(10);

	ft::stack<int> a(s);

	std::cout << a.size() << std::endl;
}

int main() {
	// insert_test_my();

	copy_constructor_test_my();
	// while (1);
}