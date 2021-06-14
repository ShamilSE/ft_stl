#ifndef NODE_HPP
#define NODE_HPP

#include <string>

template <typename T>
struct	Node {
	private:
		T const &	_content;


	public:
		Node<T>*	next;
		Node<T>*	prev;
		// constructors
		Node(T const & content): _content(content) {
			next = nullptr;
			prev = nullptr;
		}

		// getters
		T const &	getContent() {return _content;}
};

#endif