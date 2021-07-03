#pragma once

#include <memory>
#include <iostream>
#include <exception>

namespace ft {

	template<typename T>
	class vectorIterator {
		private:
			T*	_ptr;

		public:
			typedef vectorIterator<T>	iterator;

			vectorIterator(T* _array): _ptr(_array) {}

			T& operator*() {return *_ptr;}
			// iterator& opeartor++(int) {_ptr += 1; return *this;}
			iterator operator++() {_ptr += 1; return *this;}
			iterator operator+(int n) {_ptr += n; return *this;}
			iterator operator-(int n) {_ptr -= n; return *this;}
			// void opeartor--() {_ptr -= _size;}
			// void operator--(int) {_ptr -= _size;}
			bool operator>(const vectorIterator& other) {return _ptr > other._ptr;}
			bool operator>=(const vectorIterator& other) {return _ptr >= other._ptr;}
			bool operator<(const vectorIterator& other) {return _ptr < other._ptr;}
			bool operator<=(const vectorIterator& other) {return _ptr <= other._ptr;}
			bool operator==(const vectorIterator& other) {return _ptr == other._ptr;}
			bool operator!=(const vectorIterator& other) {return _ptr != other._ptr;}

			T* getPointer() {return _ptr;}
	};

	template<typename T, typename Allocator = std::allocator<T> >
	class vector {


		public:
			typedef vectorIterator<T>							iterator;
			typedef Allocator allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef size_t size_type;

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
				clear();
			}

			class tooMuchMemoryRequested : public std::exception {
				const char* what() const throw() {
					return "too much memory requested";
				}
			};

			size_t size() const {return _size;}
			bool empty() const {return _size == 0;}
			size_t max_size() const {return allocator_type().max_size();}

			allocator_type get_allocator() const {return _allocator;}

			reference operator[](size_t pos) {return _array[pos];}
			const_reference operator[]( size_t pos ) const {return _array[pos];}

			iterator begin() {return vectorIterator<T>(_array);}
			iterator end() {return vectorIterator<T>(_array + _size);} // TODO: end iterator should point to next to last el

			iterator insert(iterator pos, const T& value) {
				(void)pos;
				(void)value;
				// if (_size + 1 > _capacity)
				// 	reserve((_size + 1) * 1.3);
				
				return begin();
			}

			void push_back(const T& value) {
				insert(begin() + _size, value);
			}

			void resize( size_t count, T value = T() ) {
				while (count < _size)
					pop_back();
				while (count > _size)
					push_back(value);
			}

			void reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw tooMuchMemoryRequested();
				if (new_cap > _capacity) {
					pointer newArray = _allocator.allocate(new_cap);
					for (size_type index = 0; index < _size; index++) {
						_allocator.construct(newArray + index, *(_array + index));
						_allocator.destroy(_array + index);
					}
					_allocator.deallocate(_array, _capacity);
					_capacity = new_cap;
					_array = newArray;
				}
			}

			void pop_back() {
				if (_size)
					_allocator.destroy(_array + --_size);
			}

			void clear() {
				while (_size)
					pop_back();
			}

		};
}
