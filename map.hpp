#pragma once

#include <string>
#include <iostream>

namespace ft {

	template<class T>
	class iterator {
		iterator() {}
		iterator(const iterator & other) {}
		iterator& operator=(const iterator & other) {}
		~iterator() {}
	};

	template<class T>
	class reverse_iterator {
		reverse_iterator() {}
		reverse_iterator(const reverse_iterator & other) {}
		reverse_iterator& operator=(const reverse_iterator & other) {}
		~reverse_iterator() {}
	};

	template<
			class Key,
			class T,
			class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T> >
			>
	class map {
		/*
			Member types
		*/
		public:
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef	std::pair<const Key, T>				value_type;
			typedef size_t								size_type;
			typedef Allocator							allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef Allocator::pointer					pointer;
			typedef Allocator::const_pointer			const_pointer;
			typedef iterator<T>							itearator;
			typedef iterator<const T>					const_iterator;
			typedef reverse_iterator<T>					reverse_iterator;
			typedef reverse_iterator<const T>			const_reverse_iterator;

		private:
			allocator_type	_allocator;

		public:
		/* 
			Member functions
		*/
			map() {}
			map& operator=(const map & other) {}
			~map() {}
			allocator_type get_allocator() const {return _allocator;}

			// element access
			T& at( const Key& key );
			const T& at( const Key& key ) const;

			T& operator[]( const Key& key );

			// capacity
			bool empty() const;

			size_type size() const;

			size_type max_size() const;

			// modifiers
			void clear();

			iterator insert( iterator hint, const value_type& value );

			void erase( iterator pos );

			void erase( iterator first, iterator last );

			void swap( map& other );

			// lookup
			size_type count( const Key& key ) const;

			iterator find( const Key& key );

			const_iterator find( const Key& key ) const;

			std::pair<iterator,iterator>
			equal_range( const Key& key );

			std::pair<const_iterator,const_iterator>
			equal_range( const Key& key ) const;

			iterator lower_bound( const Key& key );

			const_iterator lower_bound( const Key& key ) const;

			iterator upper_bound( const Key& key );

			const_iterator upper_bound( const Key& key ) const;

			//observers
			key_compare key_comp() const;

			std::map::value_compare value_comp() const;

	};



}