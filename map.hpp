#pragma once

#include <string>
#include <iostream>

namespace ft {

template<class T>
class node {
private:
	T*						_data;
	std::string				_colour;

public:
	node(T* data): _data(data) {}

};

template<class T>
class iterator {
private:
	node<T>* _node;

public:
	iterator(node<T>* node): _node(node) {}

	iterator(const iterator & other) {(void)other;}

	iterator& operator=(const iterator & other) {(void)other;}
	~iterator() {}
};

template<class T>
class reverse_iterator {
	reverse_iterator() {}
	reverse_iterator(const reverse_iterator & other) {(void)other;}
	reverse_iterator& operator=(const reverse_iterator & other) {(void)other;}
	~reverse_iterator() {}
};

template<
	class T1,
    class T2
>
struct pair {
	T1*	first;
	T2*	second;

	pair(): first(nullptr), second(nullptr) {}

	pair( const T1& x, const T2& y ) {
		*first = x;
		*second = y;
	}

	template< class U1, class U2 >
	pair( const pair<U1, U2>& p );
};

template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
		>
class map {
	/*
		Member types
	*/
	public:
		typedef 	Key									key_type;
		typedef 	T									mapped_type;
		typedef		ft::pair<const Key, T>				value_type;
		typedef		size_t								size_type;
		typedef		Allocator							allocator_type;
		typedef		value_type&							reference;
		typedef		const value_type&					const_reference;
		typedef 	typename Allocator::pointer			pointer;
		typedef 	typename Allocator::const_pointer	const_pointer;
		typedef		iterator<value_type>				iterator;
		// typedef		iterator<const value_type>					const_iterator;
		typedef 	reverse_iterator<T>					reverse_iterator;
		// typedef 	reverse_iterator<const T>			const_reverse_iterator;

	private:
		allocator_type	_allocator;
		size_type		_size;
		
	public:
	/* 
		Member functions
	*/
		map() {}

		map(const map & other) {
			*this = other;
		}

		map& operator=(const map & other) {
			(void)other;
		}

		~map() {}
		allocator_type get_allocator() const {return _allocator;}

		// element access
		T& at( const Key& key ) {
			(void)key;
		}

		const T& at( const Key& key ) const {
			(void)key;
		}

		T& operator[]( const Key& key ) {
			(void)key;
		}

		// iterators
		// iterator begin() {
		// 	return iterator(new node<T>(new pair<int, int>));
		// }
		// const_iterator begin();
		iterator end();
		// const_iterator end();
		// reverse_iterator begin();

		// reverse_iterator end();

		// capacity
		bool empty() const {return _size == 0;}

		size_type size() const {return _size;}

		size_type max_size() const;

		// modifiers
		void clear();

		ft::pair<iterator, bool> insert( const value_type& value ) {
			(void)value;
		}

		template< class InputIt >
		void insert( InputIt first, InputIt last );

		void erase( iterator pos ) {
			(void)pos;
		}

		void erase( iterator first, iterator last ) {
			(void)first;
			(void)last;
		}

		void swap( map& other ) {
			(void)other;
		}

		// lookup
		size_type count( const Key& key ) const {
			(void)key;
		}

		iterator find( const Key& key ) {
			(void)key;
		}

		// const_iterator find( const Key& key ) const {
		// 	(void)key;
		// }

		// std::pair<iterator,iterator>
		// equal_range( const Key& key ) {
		// 	(void)key;
		// }

		// std::pair<const_iterator,const_iterator>
		// equal_range( const Key& key ) const {
		// 	(void)key;
		// }

		// iterator lower_bound( const Key& key ) {(void)key;}

		// const_iterator lower_bound( const Key& key ) const {(void)key;}

		// iterator upper_bound( const Key& key ) {(void)key;}

		// const_iterator upper_bound( const Key& key ) const {(void)key;}

		//observers
		// key_compare key_comp() const;

		// map::value_compare value_comp() const;

};



}