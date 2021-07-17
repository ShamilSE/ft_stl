#pragma once

#include <memory>
#include <iostream>
#include <exception>
#include <string>
#include <type_traits>

namespace ft {

	template<typename T>
	class reverseVectorIterator {
		private:
			T* _ptr;

		public:
			typedef reverseVectorIterator<T>	r_iterator;

			reverseVectorIterator() {}
			reverseVectorIterator(T* _array): _ptr(_array) {}

			T& operator*() {return *_ptr;}
			r_iterator operator++() {_ptr -= 1; return *this;}
			r_iterator operator++(int) {_ptr -= 1; return *this;}
			r_iterator operator--() {_ptr += 1; return *this;}
			r_iterator operator--(int) {_ptr += 1; return *this;}
			r_iterator operator+(int n) {_ptr -= n; return *this;}
			r_iterator operator-(int n) {_ptr += n; return *this;}

			bool operator>(const reverseVectorIterator& other) {return _ptr > other._ptr;}
			bool operator>=(const reverseVectorIterator& other) {return _ptr >= other._ptr;}
			bool operator<(const reverseVectorIterator& other) {return _ptr < other._ptr;}
			bool operator<=(const reverseVectorIterator& other) {return _ptr <= other._ptr;}
			bool operator==(const reverseVectorIterator& other) {return _ptr == other._ptr;}
			bool operator!=(const reverseVectorIterator& other) {return _ptr != other._ptr;}
	};

	template<typename T>
	class vectorIterator {
		private:
			T*	_ptr;

		public:
			typedef vectorIterator<T>	iterator;

			vectorIterator(T* _array): _ptr(_array) {}

			vectorIterator() {}
			T& operator*() {return *_ptr;}
			iterator operator++(int) {_ptr += 1; return *this;}
			iterator operator++() {_ptr += 1; return *this;}
			iterator operator--() {_ptr -= 1; return *this;}
			iterator operator--(int) {_ptr -= 1; return *this;}
			iterator operator+(int n) {_ptr += n; return *this;}
			iterator operator-(int n) {_ptr -= n; return *this;}

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
			typedef T											value_type;
			typedef const value_type							const_value_type;
			typedef vectorIterator<value_type>					iterator;
			typedef vectorIterator<const_value_type>			const_iterator;
			typedef reverseVectorIterator<value_type>			reverse_iterator;
			typedef reverseVectorIterator<const_value_type>		const_reverse_iterator;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;

		private:
			size_type	_size;
			size_type	_capacity;
			pointer		_array;
			allocator_type	_allocator;

		public:
			vector(): _size(0), _capacity(0) {
				_array = _allocator.allocate(0);
			}

			explicit vector( const Allocator& alloc ): _size(0), _capacity(0) {
				_allocator = alloc;
				_array = _allocator.allocate(0);
			}

			explicit vector( size_type count,
				const T& value = T(),
				const Allocator& alloc = Allocator())
				:
					_size(0),
					_capacity(0)
				{
					_allocator = alloc;
					_array = _allocator.allocate(count * 1.25);
					for (size_type index = 0; index < count; index++)
						insert(begin() + index, value);
				}

			/**
			 * @brief range constructor
			 * 
			 * @tparam InputIt 
			 * @param first 
			 * @param last 
			 * @param alloc 
			 */
            template <class InputIt>
            vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
					typename std::enable_if<!std::is_integral<InputIt>::value >::type* = 0)
					:
						_size(0),
						_capacity(0)
					{
						_allocator = alloc;
						_allocator.allocate(0);
						assign(first, last);
					}

			vector(const vector<T> & other) {
				if ((*this) != other)
					*this = other;
			}

			vector &operator=( vector<T> & other) {
				this->_allocator = other._allocator;
				assign(other.begin(), other.end());
				return *this;
			}

			~vector() {
				clear();
				_allocator.deallocate(_array, _capacity);
			}

			class tooMuchMemoryRequested : public std::exception {
				const char* what() const throw() {
					return "too much memory requested";
				}
			};

			class indexOutOfRangeException : public std::exception {
				const char* what() const throw() {
					return "index out of range";
				}
			};

			size_type size() const {return _size;}
			bool empty() const {return _size == 0;}
			size_type max_size() const {return allocator_type().max_size();}
			size_type capacity() const {return _capacity;}

			allocator_type get_allocator() const {return _allocator;}
			T*	data() {return _array;}


			iterator begin() {return iterator(_array);}
			const_iterator cbegin() const {return const_iterator(_array);}
			iterator end() {return iterator(_array + _size);}
			const_iterator cend() const {return const_iterator(_array + _size);}
			reverse_iterator rbegin() {return reverse_iterator(_array + _size - 1);}
			reverse_iterator rend() {return reverse_iterator(_array - 1);}
			const_reverse_iterator crbegin() const {return const_reverse_iterator(_array + _size -1);}
			const_reverse_iterator crend() const {return const_reverse_iterator(_array -1);}


			size_type getDistance(iterator start, iterator end) {
				size_type counter = 0;

				while (start != end) {
					++start;
					counter++;
				}
				return counter;
			}

			/**
			 * @brief insert value in specified pos
			 * 
			 * @param pos 
			 * @param value 
			 * @return iterator 
			 */
			iterator insert(iterator pos, const T& value) {
				size_type distance = getDistance(begin(), pos);
				if (_capacity < _size + 1)
					reserve((_size + 1) * 1.25);
				if (_size) {
					iterator newPos = begin() + distance;
					std::memmove(
						newPos.getPointer() + 1,
						newPos.getPointer(),
						sizeof(value_type) * (end().getPointer() - newPos.getPointer())
					);
				}
				_allocator.construct((begin() + distance).getPointer(), value);
				_size++;
				return begin();
			}

			/**
			 * @brief inserts values in range(first, last) to pos
			 * 
			 * @tparam InputIt 
			 * @param pos 
			 * @param first 
			 * @param last 
			 */
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last) {
				for (; first != last; pos++, first++)
					pos = insert(pos, *first);
			}

			void push_back(const T& value) {
				insert(end(), value);
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

			void printAll() {
				iterator start = begin();
				iterator finish = end();

				while (start != finish) {
					std::cout << *start << std::endl;
					++start;
				}
			}

			void clear() {
				while (_size)
					pop_back();
			}

			reference at(size_type pos) {
				if (pos >= 0 && pos < _size)
					return _array[pos];
				throw indexOutOfRangeException();
			}

			const_reference at( size_type pos ) const {
				if (pos >= 0 && pos < _size)
					return _array[pos];
				throw indexOutOfRangeException();
			}

			reference operator[](size_type pos) {return _array[pos];}
			const_reference operator[](size_type pos) const {return _array[pos];}

			reference front() {return *(begin());}
			const_reference front() const {return *(begin());}

			/**
			 * @brief get last element value
			 * 
			 * @return reference 
			 */
			reference back() {return *(end() - 1);}
			const_reference back() const {return *(end() -1);}

			iterator erase( iterator pos ) {
				size_type distance = getDistance(pos, end());
				_allocator.destroy(pos.getPointer());
				_size--;
				std::memmove(pos.getPointer(), pos.getPointer() + 1, sizeof(value_type) * distance);
				return pos;
			}

			/**
			 * @brief erase elements from first to last
			 * 
			 * @param first 
			 * @param last 
			 * @return iterator to next to deleted element
			 */
			iterator erase( iterator first, iterator last ) {
				size_type distance = getDistance(first, last);
				iterator it = first;
				while (distance--)
					it = erase(it);
				return it;
			}

			/**
			 * @brief exchange contents of two vectors
			 * @param other 
			 */
			void swap( vector& other ) {
				if (this->capacity() < other.size())
					this->resize(other.size() * 1.3);
				if (other.capacity() < this->size())
					other.resize(this->size() * 1.3);
				
				pointer tmp = _allocator.allocate(other.size());
				
				size_type index;
				for (index = 0; this->_size > index; index++)
					tmp[index] = other._array[index];

				for (size_type i = 0; i < this->_size; i++)
					other._array[i] = this->_array[i];

				for (size_type i = 0; i < index; i++)
					this->_array[i] = tmp[i];
				_allocator.deallocate(tmp, index);
			}
		
			void assign( size_type count, const T& value ) {
				clear();
				for (size_type index = 0; index < count; index++)
					insert(_array + index, value);
			}

			template< class InputIt >
			void assign( InputIt first, InputIt last ) {
				clear();
				insert(begin(), first, last);
			}
		};

		template< class T, class Alloc >
		bool operator==( const ft::vector<T,Alloc>& lhs,
			const ft::vector<T,Alloc>& rhs ) {return lhs.data() == rhs.data();}

		template< class T, class Alloc >
		bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ) {return lhs.data() != rhs.data();}

		template< class T, class Alloc >
		bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs ) {return lhs.data() < rhs.data();}

		template< class T, class Alloc >
		bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ) {return lhs.data() <= rhs.data();}

		template< class T, class Alloc >
		bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs ) {return lhs.data() > rhs.data();}

		template< class T, class Alloc >
		bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ) {return lhs.data() >= rhs.data();}

		template< class T, class Alloc >
		void swap( std::vector<T,Alloc>& lhs,
           std::vector<T,Alloc>& rhs ) {lhs.swap(rhs);}
}
