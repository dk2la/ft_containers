#pragma once

#include <iostream>
#include <iterator>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
class vector {
		typedef T   value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	public:
		class   iterator;
		class   const_iterator;
		class   reverse_iterator;
		class   const_reverse_iterator;
		//constructor:
		explicit vector (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _array(0), _alloc(alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
		                 const allocator_type& alloc = allocator_type()) {
			this->_array = this->_alloc.allocate(n);
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
		        const allocator_type& alloc = allocator_type()) {}

		vector (const vector& x) {}

		//destructor:
		~vector() {}

		//operator=:
		vector& operator= (const vector& x);

		//Member function:
		iterator begin() { return iterator(this->_array); }
		const_iterator begin() const { return const_iterator(this->_array); }

		iterator end() { return iterator(this->_array + this->_size); }
		const_iterator end() const { return const_iterator(this->_array + this->_size); }

		reverse_iterator rbegin() { return reverse_iterator(this->_array - this->_size - 1); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_array - this->_size - 1); }

		reverse_iterator rend() { return reverse_iterator(this->_array - 1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->_array - 1); }

		//Capacity:
		size_type size() const { return this->_size; }

		size_type max_size() const {
			if (sizeof(value_type) == 1)
				return ((size_t)(-1) / sizeof(value_type) / 2);
			else
				return ((size_t)(-1) / sizeof(value_type));
		}

		void resize (size_type n, value_type val = value_type()) {
			if (n < this->_size)
				for (; this->_size != n; this->_size--)
					pop_back();
			else if (n > this->_size) {
				for (; this->_size != n; this->_size++)
					push_back(val);
			}
		}

		size_type capacity() const { return this->_capacity; }

		bool empty() const { return (this->_size == 0); }

		void reserve (size_type n) {
			if (n > this->_capacity) {
				pointer tmp = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; ++i)
					tmp[i] = this->_array[i];
				this->_alloc.deallocate(this->_array, this->_capacity);
				this->_capacity = n;
				this->_array = tmp;
			}
		}

		//element access:

		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;

		reference at (size_type n);
		const_reference at (size_type n) const;

		reference front() { return *_array; }
		const_reference front() const { return *_array; }

		reference back() { return *(this->_array - this->_size - 1); }
		const_reference back() const { return *(this->_array - this->_size - 1); }

		//Modifiters:


		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {}

		void assign (size_type n, const value_type& val) {}

		void push_back (const value_type& val) {
			if (this->_size + 1 >= this->_capacity) {
				reserve(this->_capacity + (this->_capacity / 2));
			}
			this->_array[_size] = val;
			this->_size++;
		}

		void pop_back() {
			this->_size--;
		}

		iterator insert (iterator position, const value_type& val) {}

		void insert (iterator position, size_type n, const value_type& val) {}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last) {}

		iterator erase (iterator position) {

		}
		iterator erase (iterator first, iterator last) {
			for (; first != last; ++first) {
				erase(--last);
			}
		}

		void swap (vector& x) {}

		void clear() {}

		class iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
			explicit iterator(pointer it = nullptr): _it(it) {}
			iterator(const iterator& it) { *this = it; }
			iterator&   operator=(const iterator& it) {
				this->_it = it._it;
				return *this;
			}
			~iterator() {}

			iterator& operator++() { this->_it += 1; return *this; }
			iterator& operator--() { this->_it -= 1; return *this; }

			iterator& operator++(int) {
				iterator tmp(*this);
				this->operator++();
				return tmp;
			}
			iterator& operator--(int) {
				iterator tmp(*this);
				this->operator--();
				return tmp;
			}

			iterator operator+(const difference_type second) { this->_it += second; return *this; }
			difference_type operator+(const iterator& second) { return (this->_it + second); }
			difference_type operator-(const iterator& second) { return (this->_it - second); }
			iterator operator-(const difference_type second) { this->_it -= second; return *this; }

			bool        operator<(const iterator& it) { return this->_it < it._it; }
			bool        operator>(const iterator& it) { return this->_it > it._it; }
			bool        operator<=(const iterator& it) { return this->_it <= it._it; }
			bool        operator>=(const iterator& it) { return this->_it >= it._it; }
			bool        operator==(const iterator& it) { return (this->_it == it._it); }
			bool        operator!=(const iterator& it) { return (this->_it != it._it); }

			iterator&   operator+=(const difference_type n) { this->_it += n; return *this; }
			iterator&   operator-=(const difference_type n) { this->_it -= n; return *this; }

			reference   operator*() { return *this->_it; }
			value_type& operator[](const difference_type n) {
				return *(this->_it + n);
			}
			pointer getElement() const { return this->_it; }
		private:
			pointer _it;
		};

		class const_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
			explicit const_iterator(pointer it = nullptr): _it(it) {}
			const_iterator(const const_iterator& it) { *this = it; }
			const_iterator&   operator=(const iterator& it) {
				this->_it = it.getElement();
				return *this;
			}
			~const_iterator() {}

			const_iterator& operator++() { this->_it += 1; return *this; }
			const_iterator& operator--() { this->_it -= 1; return *this; }

			const_iterator& operator++(int) {
				const_iterator tmp(*this);
				this->operator++();
				return tmp;
			}
			const_iterator& operator--(int) {
				const_iterator tmp(*this);
				this->operator--();
				return tmp;
			}

			const_iterator operator+(const difference_type second) { this->_it += second; return *this; }
			difference_type operator+(const const_iterator& second) { return (this->_it + second); }
			difference_type operator-(const const_iterator& second) { return (this->_it - second); }
			const_iterator operator-(const difference_type second) { this->_it -= second; return *this; }

			bool        operator<(const const_iterator& it) {return this->_it < it._it; }
			bool        operator>(const const_iterator& it) {return this->_it > it._it; }
			bool        operator<=(const const_iterator& it) {return this->_it <= it._it; }
			bool        operator>=(const const_iterator& it) {return this->_it >= it._it; }
			bool    operator==(const const_iterator& it) { return (this->_it == it._it); }
			bool    operator!=(const const_iterator& it) { return (this->_it != it._it); }

			const_iterator&   operator+=(const difference_type n) { this->_it += n; return *this; }
			const_iterator&   operator-=(const difference_type n) { this->_it -= n; return *this; }
			reference   operator*() { return *this->_it; }
			value_type& operator[](const difference_type n) {
				return *(this->_it + n);
			}
			pointer getElement() const { return this->_it; }
		private:
			pointer _it;
		};

		class reverse_iterator: public std::iterator<std::random_access_iterator_tag, T>{
		public:
			explicit reverse_iterator(pointer it = nullptr): _it(it) {}
			reverse_iterator(const reverse_iterator& it) { *this = it; }
			reverse_iterator&   operator=(const reverse_iterator& it) {
				this->_it = it._it;
				return *this;
			}
			~reverse_iterator() {}

			reverse_iterator&   operator++() { this->_it -= 1; return *this; }
			reverse_iterator&   operator--() { this->_it += 1; return *this; }

			reverse_iterator&   operator++(int) {
				reverse_iterator tmp(*this);
				this->operator++();
				return tmp;
			}
			reverse_iterator&   operator--(int) {
				reverse_iterator tmp(*this);
				this->operator--();
				return tmp;
			}

			reverse_iterator    operator+(const difference_type second) { this->_it -= second; return *this; }
			difference_type     operator+(const reverse_iterator& second) { return (this->_it - second); }
			difference_type     operator-(const reverse_iterator& second) { return (this->_it + second); }
			reverse_iterator    operator-(const difference_type second) { this->_it += second; return *this; }

			bool                operator<(const reverse_iterator& it) {return this->_it > it._it; }
			bool                operator>(const reverse_iterator& it) {return this->_it < it._it; }
			bool                operator<=(const reverse_iterator& it) {return this->_it >= it._it; }
			bool                operator>=(const reverse_iterator& it) {return this->_it <= it._it; }
			bool                operator==(const reverse_iterator& it) { return (this->_it == it._it); }
			bool                operator!=(const reverse_iterator& it) { return (this->_it != it._it); }

			reverse_iterator&   operator+=(const difference_type n) { this->_it -= n; return *this; }
			reverse_iterator&   operator-=(const difference_type n) { this->_it += n; return *this; }
			reference   operator*() { return *this->_it; }
			value_type&         operator[](const difference_type n) {
				return *(this->_it - n);
			}
			pointer getElement() const { return this->_it; }
		private:
			pointer _it;
		};

		class const_reverse_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
			explicit const_reverse_iterator(pointer it = nullptr): _it(it) {}
			const_reverse_iterator(const const_reverse_iterator& it) { *this = it; }
			const_reverse_iterator&   operator=(const reverse_iterator& it) {
				this->_it = it._it;
				return *this;
			}
			~const_reverse_iterator() {}

			const_reverse_iterator&   operator++() { this->_it -= 1; return *this; }
			const_reverse_iterator&   operator--() { this->_it += 1; return *this; }

			const_reverse_iterator&   operator++(int) {
				const_reverse_iterator tmp(*this);
				this->operator++();
				return tmp;
			}
			const_reverse_iterator&   operator--(int) {
				const_reverse_iterator tmp(*this);
				this->operator--();
				return tmp;
			}

			const_reverse_iterator    operator+(const difference_type second) { this->_it -= second; return *this; }
			difference_type     operator+(const reverse_iterator& second) { return (this->_it - second); }
			difference_type     operator-(const reverse_iterator& second) { return (this->_it + second); }
			const_reverse_iterator    operator-(const difference_type second) { this->_it += second; return *this; }

			bool                operator<(const reverse_iterator& it) {return this->_it > it._it; }
			bool                operator>(const reverse_iterator& it) {return this->_it < it._it; }
			bool                operator<=(const reverse_iterator& it) {return this->_it >= it._it; }
			bool                operator>=(const reverse_iterator& it) {return this->_it <= it._it; }
			bool                operator==(const reverse_iterator& it) { return (this->_it == it._it); }
			bool                operator!=(const reverse_iterator& it) { return (this->_it != it._it); }

			const_reverse_iterator&   operator+=(const difference_type n) { this->_it -= n; return *this; }
			const_reverse_iterator&   operator-=(const difference_type n) { this->_it += n; return *this; }
			reference   operator*() { return *this->_it; }
			value_type&         operator[](const difference_type n) {
				return *(this->_it - n);
			}
			pointer getElement() const { return this->_it; }
		private:
			pointer _it;
		};
	private:
		size_type       _size;
		size_type       _capacity;
		pointer         _array;
		allocator_type  _alloc;
	};

}