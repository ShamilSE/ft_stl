#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>

namespace ft {

		template<typename T>
		class vectorIterator {
		public:
			T &item;
		};

	template<typename T, typename Allocator = std::allocator<T> >
	class vector {

		public:
			typedef typename std::allocator<T>  allocator;
			typedef vectorIterator<T>  iterator;
			typedef typename std::allocator<T>::pointer   pointer;

		private:
			size_t		_size;
			size_t		_capacity;
			pointer		array;
			Allocator	_allocator;

		public:
			vector() {
				_array = _allocator.allocate(0);
				std::cout << "vector constructed" << std::endl;
			}

			vector(const vector<T> &);

			vector &operator=(const vector<T> &);

			~vector() {
				std::cout << "vector destructed" << std::endl;
			}
		};
}

#endif