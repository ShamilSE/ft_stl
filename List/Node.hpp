#ifndef NODE_HPP
#define NODE_HPP

#include <string>

template <typename T>
class	Node {
	private:
		T const &	_content;

	public:
		Node(T const & content): _content(content) {}

		T const &	getContent() {return _content;}
};

#endif