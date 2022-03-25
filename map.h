#pragma once

#include "ft.hpp"

enum Compare
{
	EQUAL,
	LESS,
	GREATER
};

template <class Key,
		  class T,
		  class Compare,
		  class Allocator>
class ft::map {
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<const Key, T> value_type;
	typedef value_type *pointer;
	typedef value_type &reference;
	typedef const value_type *const_pointer;
	typedef const value_type &const_reference;
	typedef ptrdiff_t difference_type;

private:
	struct node {
		value_type	value;
		size_t		height;
		node		*left;
		node		*right;
		node		*parent;
		bool		isBegin;
		bool		isEnd;

		node()
			: height(0),
			  left(nullptr), right(nullptr), parent(nullptr),
			  isBegin(1), isEnd(1) {}
		node(const_reference val)
			: value(ft::make_pair(val.first, val.second)),
			  height(1),
			  left(nullptr), right(nullptr), parent(nullptr),
			  isBegin(0), isEnd(0) {}
	};

	node*	_root;
	node*	_firstNode;
	node*	_lastNode;
	size_t	_treeSize;
	Compare	_comparator;

	int keyCmp(const key_type &key1, const key_type &key2) const {
		return _comparator(key1, key2) + _comparator(key2, key1) * 2;
	}

	int valueCmp(const_reference val1, const_reference val2) const {
		return keyCmp(val1.first, val2.first);
	}

	size_t height(node *p) {
		return p ? p->height : 0;
	}

	int bfactor(node *p) {return height(p->right) - height(p->left);}

	void fixheight(node *p) {
		size_t hl = height(p->left);
		size_t hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node*	rotateright(node* p) {
		node *q = p->left;

		p->left = q->right;
		q->right = p;

		q->parent = p->parent;
		p->parent = q;
		if (q->right->left)
			q->right->left->parent = p;

		fixheight(p);
		fixheight(q);
		return q;
	}

	node*	rotateleft(node* q) {
		node *p = q->right;
		q->right = p->left;
		p->left = q;

		p->parent = q->parent;
		q->parent = p;
		if (p->left->right)
			p->left->right->parent = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node*	balance(node *p) {
		node* tmp = p->parent; /*    запоминаем родителя данного узла    */
		fixheight(p);		   /*    корректировка высоты данного поддерева    */
		if (bfactor(p) == 2) {  /*    правое поддерево от 'p' выше левого    */
			if (bfactor(p->right) < 0) /*    требуется поворот правого поддерева от 'p'    */
				p->right = rotateright(p->right);
			if (!tmp)						   /*    т.е. 'p' - корень всего дерева    */
				return _root = rotateleft(p); /*    балансировка корня всего дерева    */
											   /*    балансировка поддерева с корнем 'p'    */
			if (tmp->left == p)
				return (tmp->left = rotateleft(p));
			else
				return (tmp->right = rotateleft(p));
		}
		if (bfactor(p) == -2) { /*    левое поддерево от 'p' выше правого    */
			if (bfactor(p->left) > 0) /*    требуется поворот левого поддерева от 'p'    */
				p->left = rotateleft(p->left);
			if (!tmp)							/*    т.е. 'p' - корень всего дерева    */
				return _root = rotateright(p); /*    балансировка корня всего дерева    */
												/*    балансировка поддерева с корнем 'p'    */
			if (tmp->right == p)
				return (tmp->right = rotateright(p));
			else
				return (tmp->left = rotateright(p));
		}
		return p; /*    балансировка не потребовалась    */
	}

	node*	findmin(node *p) { return p->left ? findmin(p->left) : p; }
	node*	findmax(node *p){ return p->right ? findmax(p->right) : p; }

	node*	getNodeByKey(node *p, key_type k) const {
		int compare = keyCmp(k, p->value.first);
		if (compare == LESS)
		{
			if (p->left && p->left != _firstNode)
				return getNodeByKey(p->left, k);
		}
		else if (compare == GREATER)
		{
			if (p->right && p->right != _lastNode)
				return getNodeByKey(p->right, k);
		}
		return p;
	}

	void delete_root(node *p) { /*    очистка дерева    */
		if (p->left != nullptr)
			delete_root(p->left);
		if (p->right != nullptr)
			delete_root(p->right);
		delete p;
	}

	void balanceAllNodes(node *node) {
		for (; node != nullptr; node = node->parent)
			node = balance(node);
	}

public:
	/*    ITERATORS    */
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;

	class iterator : public ft::iterator_traits<std::bidirectional_iterator_tag, value_type> {
	private:
		node*	_node;

		node*	findmin(node* p) { return p->left ? findmin(p->left) : p; }
		node*	findmax(node* p) { return p->right ? findmax(p->right) : p; }

	public:
		iterator() : _node(nullptr) {}
		iterator(node *ptr) : _node(ptr) {}
		~iterator() {}
		iterator(const iterator &other) { *this = other; }

		node *getNode() const { return _node; }

		iterator &operator=(const iterator &other) {
			_node = other._node;
			return *this;
		}

		bool operator==(const iterator &other) { return this->_node == other._node; }
		bool operator!=(const iterator &other) { return this->_node != other._node; }
		bool operator==(const const_iterator &other) { return this->_node == other.getNode(); }
		bool operator!=(const const_iterator &other) { return this->_node != other.getNode(); }

		reference operator*() { return _node->value; }
		pointer operator->() { return &_node->value; }

		iterator &operator++() {
			if (_node->isBegin)
				_node = _node->parent;
			else if (_node->right)
				_node = findmin(_node->right);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first < _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		iterator &operator--() {
			if (_node->isEnd)
				_node = _node->parent;
			else if (_node->left)
				_node = findmax(_node->left);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first > _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		iterator operator++(int) {
			iterator tmp(_node);
			operator++();
			return tmp;
		}

		iterator operator--(int) {
			iterator tmp(_node);
			operator--();
			return tmp;
		}
	};

	// Iterators
	class const_iterator : public ft::iterator_traits<std::bidirectional_iterator_tag, value_type>
	{
	private:
		node *_node;

		node *findmin(node *p) { return p->left ? findmin(p->left) : p; }
		node *findmax(node *p) { return p->right ? findmax(p->right) : p; }

	public:
		const_iterator() : _node(nullptr) {}
		const_iterator(node *ptr) : _node(ptr) {}
		~const_iterator() {}
		const_iterator(const const_iterator &other) { *this = other; }
		const_iterator(const iterator &other) { *this = other; }

		node *getNode() const { return _node; }

		const_iterator &operator=(const const_iterator &other)
		{
			_node = other._node;
			return *this;
		}

		const_iterator &operator=(const iterator &other)
		{
			_node = other.getNode();
			return *this;
		}

		bool operator==(const const_iterator &other) { return this->_node == other._node; }
		bool operator!=(const const_iterator &other) { return this->_node != other._node; }
		bool operator==(const iterator &other) { return this->_node == other.getNode(); }
		bool operator!=(const iterator &other) { return this->_node != other.getNode(); }

		const_reference operator*() const { return _node->value; }
		const_pointer operator->() const { return &_node->value; }

		const_iterator &operator++()
		{
			if (_node->isBegin)
				_node = _node->parent;
			else if (_node->right)
				_node = findmin(_node->right);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first < _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		const_iterator &operator--()
		{
			if (_node->isEnd)
				_node = _node->parent;
			else if (_node->left)
				_node = findmax(_node->left);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first > _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator tmp(_node);
			operator++();
			return tmp;
		}

		const_iterator operator--(int)
		{
			const_iterator tmp(_node);
			operator--();
			return tmp;
		}
	};

	class reverse_iterator : public ft::reverse_iterator<iterator>
	{
	private:
		node *_node;

		node *findmin(node *p) { return p->left ? findmin(p->left) : p; }
		node *findmax(node *p) { return p->right ? findmax(p->right) : p; }

	public:
		reverse_iterator() : _node(nullptr) {}
		reverse_iterator(node *ptr) : _node(ptr) {}
		~reverse_iterator() {}
		reverse_iterator(const reverse_iterator &other) { *this = other; }

		node *getNode() const { return _node; }

		reverse_iterator &operator=(const reverse_iterator &other)
		{
			_node = other._node;
			return *this;
		}

		bool operator==(const reverse_iterator &other) { return this->_node == other._node; }
		bool operator!=(const reverse_iterator &other) { return this->_node != other._node; }
		bool operator==(const const_reverse_iterator &other) { return this->_node == other.getNode(); }
		bool operator!=(const const_reverse_iterator &other) { return this->_node != other.getNode(); }

		reference operator*() { return _node->value; }
		pointer operator->() { return &_node->value; }

		reverse_iterator &operator++()
		{
			if (_node->isEnd)
				_node = _node->parent;
			else if (_node->left)
				_node = findmax(_node->left);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first > _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		reverse_iterator &operator--()
		{
			if (_node->isBegin)
				_node = _node->parent;
			else if (_node->right)
				_node = findmin(_node->right);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first < _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(_node);
			operator++();
			return tmp;
			;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(_node);
			operator--();
			return tmp;
		}
	};

	class const_reverse_iterator : public ft::reverse_iterator<const_iterator>
	{
	private:
		node *_node;

		node *findmin(node *p) { return p->left ? findmin(p->left) : p; }
		node *findmax(node *p) { return p->right ? findmax(p->right) : p; }

	public:
		const_reverse_iterator() : _node(nullptr) {}
		const_reverse_iterator(node *ptr) : _node(ptr) {}
		~const_reverse_iterator() {}
		const_reverse_iterator(const const_reverse_iterator &other) { *this = other; }
		const_reverse_iterator(const reverse_iterator &other) { *this = other; }

		node *getNode() const { return _node; }

		const_reverse_iterator &operator=(const const_reverse_iterator &other)
		{
			_node = other._node;
			return *this;
		}

		const_reverse_iterator &operator=(const reverse_iterator &other)
		{
			_node = other.getNode();
			return *this;
		}

		bool operator==(const const_reverse_iterator &other) { return this->_node == other._node; }
		bool operator!=(const const_reverse_iterator &other) { return this->_node != other._node; }
		bool operator==(const reverse_iterator &other) { return this->_node == other.getNode(); }
		bool operator!=(const reverse_iterator &other) { return this->_node != other.getNode(); }

		const_reference operator*() { return _node->value; }
		const_pointer operator->() { return &_node->value; }

		const_reverse_iterator &operator++()
		{
			if (_node->isEnd)
				_node = _node->parent;
			else if (_node->left)
				_node = findmax(_node->left);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first > _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		const_reverse_iterator &operator--()
		{
			if (_node->isBegin)
				_node = _node->parent;
			else if (_node->right)
				_node = findmin(_node->right);
			else
			{
				node *tmp = _node->parent;
				while (tmp && tmp->value.first < _node->value.first)
					tmp = tmp->parent;
				_node = tmp;
			}
			return *this;
		}

		const_reverse_iterator operator++(int)
		{
			const_reverse_iterator tmp(_node);
			operator++();
			return tmp;
		}

		const_reverse_iterator operator--(int)
		{
			const_reverse_iterator tmp(_node);
			operator--();
			return tmp;
		}
	};

	map() : _root(new node()), _treeSize(0) { _firstNode = _lastNode = _root; }

	template <class _InputIt>
	map(_InputIt first, _InputIt last) : _root(new node()), _treeSize(0)
	{
		_firstNode = _lastNode = _root;
		insert(first, last);
	}

	map(const map &other) : _root(new node()), _treeSize(0)
	{
		_firstNode = _lastNode = _root;
		*this = other;
	}

	~map() { delete_root(_root); }

	// Member functioins
	iterator begin() { return _treeSize ? ++iterator(_firstNode) : iterator(_firstNode); }
	iterator end() { return iterator(_lastNode); }
	const_iterator begin() const { return _treeSize ? ++const_iterator(_firstNode) : const_iterator(_firstNode); }
	const_iterator end() const { return const_iterator(_lastNode); }

	const_iterator cbegin() const { return _treeSize ? ++const_iterator(_firstNode) : const_iterator(_firstNode); }
	const_iterator cend() const { return const_iterator(_lastNode); }

	reverse_iterator rbegin() { return --reverse_iterator(_lastNode); }
	reverse_iterator rend() { return reverse_iterator(_firstNode); }
	const_reverse_iterator rbegin() const { return --const_reverse_iterator(_lastNode); }
	const_reverse_iterator rend() const { return const_reverse_iterator(_firstNode); }

	const_reverse_iterator crbegin() const { return --const_reverse_iterator(_lastNode); }
	const_reverse_iterator crend() const { return const_reverse_iterator(_firstNode); }

	size_t size() const {return _treeSize;}

	void delete_tree(node* p) {
		if (p->left != nullptr)
			delete_tree(p->left);
		if (p->right != nullptr)
			delete_tree(p->right);

		delete p;
	}

	void clear() {
		if (_treeSize) {
			delete_tree(_root);
			_root = _firstNode = _lastNode = new node();
			_treeSize = 0;
		}
	}

	ft::pair<iterator, bool>    insert(const_reference value) {
		node* newNode = getNodeByKey(_root, value.first);
		if (_treeSize && valueCmp(value, newNode->value) == EQUAL) // if oldNode->key == newNode->key
			return ft::make_pair(iterator(newNode), false);
		if (!_treeSize) { // _root = newNode
			newNode = new node (value);
			newNode->right = _root;
			newNode->left = new node();
			newNode->right->isBegin = 0;
			newNode->left->isEnd = 0;
			newNode->left->parent = newNode->right->parent = newNode;
			_firstNode = newNode->left;
			_root = newNode;
		}
		else { // newNode is new parent
			if (valueCmp(value, newNode->value) == LESS) {
				if (newNode->left) {
					node    *tmp = new node(value);
					tmp->left = newNode->left;
					tmp->left->parent = tmp;
					tmp->parent = newNode;
					newNode->left = tmp;
				}
				else { // left insert
					newNode->left = new node(value);
					newNode->left->parent = newNode;
				}
				newNode = newNode->left;
			}
			else if (valueCmp(value, newNode->value) == GREATER) { // right insert
				if (newNode->right) {
					node* tmp = new node(value);
					tmp->right = newNode->right;
					tmp->right->parent = tmp;
					tmp->parent = newNode;
					newNode->right = tmp;
				}
				else {
					newNode->right = new node(value);
					newNode->right->parent = newNode;
				}
				newNode = newNode->right;
			}
			balanceAllNodes(newNode);
		}
		_treeSize++;
		return ft::make_pair(iterator(newNode), true);
	}

	void    erase(iterator pos) {
		node*	rm = pos.getNode();
		node*	l = rm->left;
		node*	r = rm->right;
		node*	parent = rm->parent;
		if (rm == _firstNode->parent) {
			if (_treeSize == 1) {
				clear();
				_firstNode = _lastNode = _root = new node();
				return ;
			}
			if (r) {
				node    *newBegin = findmin(r);
				if (parent)
					parent->left = r;
				else
					_root = newBegin;
				r->parent = parent;
				newBegin->left = _firstNode;
				_firstNode->parent = newBegin;
			}
			else {
				parent->left = _firstNode;
				_firstNode->parent = parent;
			}
			if (parent)
				balanceAllNodes(parent);
			delete rm;
			_treeSize--;
			return ;
		}
		if (rm == _lastNode->parent) {
			if (l) {
				node    *newEnd = findmax(l);
				if (parent)
					parent->right = l;
				else
					_root = newEnd;
				l->parent = parent;
				newEnd->right = _lastNode;
				_lastNode->parent = newEnd;
			}
			else {
				_lastNode->parent = parent;
				parent->right = _lastNode;
			}
			if (parent)
				balanceAllNodes(parent);
			delete rm;
			_treeSize--;
			return ;
		}
		if (l) {
			node    *replacement = findmax(l);
			if (replacement->parent == rm) {
				replacement->parent = parent;
				replacement->right = r;
				if (r)
					r->parent = replacement;
				if (parent) {
					if (parent->left == rm)
						parent->left = replacement;
					else
						parent->right = replacement;
				}
				else
					_root = replacement;
				balanceAllNodes(replacement);
				delete rm;
				_treeSize--;
				return ;
			}
			replacement->parent->right = replacement->left;
			if (replacement->left)
				replacement->left->parent = replacement->parent;
			replacement->left = l;
			l->parent = replacement;
			replacement->right = r;
			if (r)
				r->parent = replacement;
			replacement->parent = parent;
			if (parent) {
				if (parent->left == rm)
					parent->left = replacement;
				else
					parent->right = replacement;
			}
			else
				_root = replacement;
			balanceAllNodes(replacement);
		}
		else {
			if (parent->left == rm) {
				if ((parent->left = r))
					parent->left->parent = parent;
			}
			else if (parent->right == rm) {
				if ((parent->right = r))
					parent->right->parent = parent;
			}
			balanceAllNodes(parent);
		}
		delete rm;
		_treeSize--;
		return ;
	}

	T& operator[](const Key& key) {
		ft::pair<iterator, bool>    res = insert(ft::make_pair(key, T()));
		return (*res.first).second;
	}

};
