#pragma once

#include <string>
#include <iostream>

struct node;

namespace ft {

template<class T1, class T2>
struct pair {
	T1 first;
	T2 second;

	pair(T1 first, T2 second) {this->first = first; this->second = second;}
};

template<class T1, class T2>
pair<T1, T2> make_pair(T1 first, T2 second) {return pair<T1, T2>(first, second);}

template<class Category, class T>
struct    iterator_traits
{
	typedef T				value_type;
	typedef value_type*		pointer;
	typedef value_type&		reference;
	typedef ptrdiff_t		difference_type;
	typedef Category		iterator_category;
};


template	<   
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
	typedef 	T									Value;
	typedef		pair<const Key, T>					value_type;
	typedef		size_t								size_type;
	typedef		Allocator							allocator_type;
	typedef		value_type&							reference;
	typedef		const value_type&					const_reference;
	typedef 	typename Allocator::pointer			pointer;
	typedef 	typename Allocator::const_pointer	const_pointer;
	// typedef		iterator<value_type>				iterator;
	// typedef		iterator<const value_type>					const_iterator;
	// typedef 	reverse_iterator<T>					reverse_iterator;
	// typedef 	reverse_iterator<const T>			const_reverse_iterator;


private:
	Compare comparator; //Checks whether lhs is less than rhs. 

	int keyCmp(key_type k1, key_type k2) {comparator(k1, k2) * comparator(k2, k1) * 2;}

	// node*    find_node(node* p, key_type k) const    /*    поиск узла по ключу    */
	// {
	// 	int        compare = keyCmp(k, p->value.first);
	// 	if (compare == -1)
	// 	{
	// 		if (p->left && p->left != _beginNode)
	// 			return find_node(p->left, k);
	// 	}
	// 	else if (compare == 1)
	// 	{
	// 		if (p->right && p->right != _endNode)
	// 			return find_node(p->right, k);
	// 	}
	// 	return p;    /*    если узел с данным ключом отсутствует, то вернётся узел, ближайший по ключу    */
	// }

public:
	class iterator : public ft::iterator_traits<std::bidirectional_iterator_tag, value_type> {
		private:
			node*	_node;


		public:
			iterator() : _node(nullptr) {}
			iterator(node* ptr) : _node(ptr) {}
			~iterator() {}
			iterator(const iterator &other) { *this = other; }
	};

	struct node {
		value_type	_value;
		int			height;
		node*		left;
		node*		right;

		node(value_type pair) : _value(make_pair(pair.first, pair.second)) {
			this->right = this->left = nullptr;
			height = 0;
		}
	};

	node*	_root;


	// ft::pair<iterator, bool> insert( const value_type& value ) {
	// 	node* newNode = new node(make_pair(value));
	// 	if (_root == nullptr) {
	// 		_root = newNode;
	// 	}
	// }

	// iterator find( const Key& key ) {		
	// 	node* nodeToFind = _root;
	// 	comparator(key);
	// }

	map() : _root(nullptr) {}

	// iterator begin() {
	// 	int a = 5;
	// 	int c = 6;
	// 	_root = new node (make_pair(a,c));
	// 	iterator* it = new iterator(_root);
	// 	return *it;
	// }


};
}

