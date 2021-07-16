# pragma once

#include <deque>

namespace ft {

template <class T, class Container = std::deque<T> >
class stack {
    public:
        typedef   Container                  container_type;
        typedef   Container::value_type      value_type;
        typedef   Container::size_type       size_type;
        typedef   Container::reference       reference;
        typedef   Container::const_reference const_reference;
        typedef   size_t                     size_type;

    private:
        size_type  _size;
        size_type  _capacity;

    public:
        stack(): _size(0), _capacity(0) {}
        stack(const stack & other) {}

        stack& operator=(const stack & other) {
            return *this;
        }

        ~stack() {}


        reference top();
        const_reference top() const;

        bool empty() const {return _size == 0;}
        size_type size() const {return _size;}
	
        void push( const value_type& value );
		void pop();
};

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
    return lhs == rhs;
}

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
    return lhs != rhs;
}

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
    return lhs < rhs;
}

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
    return lhs <= rhs;
}

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
    return lhs > rhs;
}

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
    return lhs >= lhs;
}

}