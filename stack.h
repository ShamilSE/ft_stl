# pragma once

#include <iostream>
#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
public:
	typedef				Container					container_type;
	typedef	typename	Container::value_type		value_type;
	typedef	typename	Container::size_type		size_type;
	typedef	typename	Container::reference		reference;
	typedef	typename	Container::const_reference	const_reference;

private:
	container_type	_container;

public:
	stack() {}

	stack( stack & other) {*this = other;}

	stack& operator=( stack & other) {
		this->_container = other._container;
		return *this;
	}

	~stack() {}

	/**
	 * @brief Returns reference to the top element in the stack. This is the most recently pushed element.
	 * 
	 * @return reference 
	 */
	reference top() {return _container.back();}
	const_reference top() const {_container.back();}

	bool empty() const {return _container.empty();}
	size_type size() const {return _container.size();}

	void push( const value_type& value ) {_container.push_back(value);}

	void pop() {_container.pop_back();}
};

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return lhs == rhs;}

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return lhs != rhs;}

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return lhs < rhs;}

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return lhs <= rhs;}

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return lhs > rhs;}

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return lhs >= rhs;}

}