#ifndef SOMECLASS_HPP
#define SOMECLASS_HPP

#include <string>
#include <iostream>

class SomeClass {
	private:
		std::string _name;
		int		 	_age;

	public:
		SomeClass(): _name(nullptr), _age(0) {}

		SomeClass(const std::string & name, int number)
		:
			_name(name), _age(number)
		{}

		SomeClass(const SomeClass & other) {
			// std::cout << "SomeClass copy constructor" << std::endl;
			*this = other;
		}

		SomeClass& operator=(const SomeClass & other) {
			// std::cout << "assignation overload someclass" << std::endl;
			_name = other._name;
			_age = other._age;
			return *this;
		}

		~SomeClass() {
			// std::cout << "SomeClass destructor called" << std::endl;
		}

		std::string getName() const {return _name;}
		int getAge() const {return _age;}
};

std::ostream& operator<<(std::ostream& os, const SomeClass& some) {
	os << "name: " << some.getName() << "\n" << "age: " << some.getAge();
	return os;
}

#endif