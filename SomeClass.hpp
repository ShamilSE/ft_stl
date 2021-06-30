#ifndef SOMECLASS_HPP
#define SOMECLASS_HPP

#include <string>
#include <iostream>

class SomeClass {
	private:
		std::string name;
		int		 number;

	public:
		SomeClass(): name(nullptr), number(0) {}

		SomeClass(const std::string & name, int number) {
			this->name = name;
			this->number = number;
		}

		SomeClass(const SomeClass & other) {
			std::cout << "SomeClass copy constructor" << std::endl;
			*this = other;
		}

		SomeClass& operator=(const SomeClass & other) {
			std::cout << "assignation overload someclass" << std::endl;
			name = other.name;
			number = other.number;
			return *this;
		}

		~SomeClass() {
			std::cout << "SomeClass destructor called" << std::endl;
		}

		std::string getName() const {return name;}
};

#endif