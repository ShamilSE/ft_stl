#pragma once

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
			typedef Allocator allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

		private:
			size_t		_size;
			size_t		_capacity;
			pointer		_array;
			allocator_type	_allocator;

		public:
			vector(): _size(0), _capacity(0) {
				_array = _allocator.allocate(0);
			}

			vector(const vector<T> & other) {*this = other;}

			vector &operator=(const vector<T> &) {}

			~vector() {
//				clear();
			}

			size_t size() const {return _size;}
			bool empty() const {return _size == 0;}
			size_t max_size() const {return _capacity;} // should max_size return _capacity or not?
			allocator_type get_allocator() const {return _allocator;}
			reference operator[](size_t pos) {return _array[pos];}
			const_reference operator[]( size_t pos ) const {return _array[pos];}

			void push_back( const T& value ) {
				T* content = new T(value);
				if (_capacity >= _size + 1)
					_array[_size++] = *content;
				else {
					pointer new_array = _allocator.allocate((_size + 1) * 2);
					size_t index = 0;
					if (_size) {
						while (index < _size) {
							new_array[index] = _array[index];
							index++;
						}
					}
					else
						new_array[index++] = *content;
					_allocator.deallocate(_array, _capacity);
					if (_size) {
						size_t index = 0;
						while (_size > index) {
							_allocator.destroy(_array + index);
							index++;
						}
					}
					_array = new_array;
					_capacity = (_size + 1) * 2;
					_size = index;
				}
			}

//			void clear() {
//				for (size_t index = 0; index < _size; index++)
//					_allocator.destroy(_array + index);
//				_allocator.deallocate(_array, _capacity);
//				_size = 0;
//			}

		};
}
