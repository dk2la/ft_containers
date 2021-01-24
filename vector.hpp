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
		explicit vector (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _array(nullptr), _alloc(alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
		                 const allocator_type& alloc = allocator_type()): _size(n), _capacity(this->_size), _array(nullptr), _alloc(alloc) {
			this->_array = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; ++i)
				this->_alloc.contruct(this->_array + i, val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
		        const allocator_type& alloc = allocator_type()) {}

//		vector (const vector& x): _size(x._size), _capacity(x._capacity), _array(x._array), _alloc(x._alloc) {
//			this->_array = this->_alloc.allocate(this->_capacity);
//			for (size_type i = 0; i < this->_size; ++i)
//				this->_alloc.contruct(this->_array + i, val);
//		}

		//destructor:
		~vector() {
		    clear();
		    if (this->_capacity)
		        this->_alloc.deallocate(this->_array, this->_capacity);
		    this->_capacity = 0;
		}

		//operator=:
		vector& operator= (const vector& x) {
            insert(begin(), x.begin(), x.end());
            return *this;
		}

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
				for (;this->_size >= n;)
					pop_back();
			else if (n > this->_size) {
				std::cout << "HERE" << std::endl;
				for (;this->_size <= n;)
					push_back(val);
			}
		}

		size_type capacity() const { return this->_capacity; }

		bool empty() const { return (this->_size == 0); }

		void reserve (size_type n) {
			if (n > this->_capacity) {
				pointer tmp = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.construct(&tmp[i], this->_array[i]);
				this->_alloc.deallocate(this->_array, this->_capacity);
				this->_capacity = n;
				this->_array = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.construct(&_array[i], tmp[i]);
				this->_alloc.deallocate(tmp, this->_capacity);
			}
		}

		//element access:

		reference operator[] (size_type n) {
		    at(n);
		    return this->_array[n];
		}
		const_reference operator[] (size_type n) const {
		    at(n);
		    return this->_array[n];
		}

		reference at (size_type n) {
		    if (this->_size < n)
		        throw std::out_of_range("out of range");
		    return this->_array[n];
		}
		const_reference at (size_type n) const {
		    if (this->_size < n)
		        throw std::out_of_range("out of range");
		    return this->_array[n];
		}

		reference front() { return *_array; }
		const_reference front() const { return *_array; }

		reference back() { return *(this->_array + this->_size - 1); }
		const_reference back() const { return *(this->_array + this->_size - 1); }

		//Modifiters:


		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
		    clear();
		    for (; first != last; ++first)
		        push_back(*first);
		}

		void assign (size_type n, const value_type& val) {
		    clear();
		    for (; n != 0; --n)
		        push_back(val);
		}

		void push_back (const value_type& val) {
			if (this->_size + 1 >= this->_capacity) {
				reserve(this->_capacity + 15);
			}
			this->_array[_size] = val;
			this->_size++;
		}

		void pop_back() {
			this->_size--;
		}

		iterator insert (iterator position, const value_type& val) {
			difference_type it_end = end().getElement() - begin().getElement();
			difference_type it_pos = position.getElement() - begin().getElement();
			if (this->_size + 1 > this->_capacity)
			    reserve(this->_capacity + 15);
			for (difference_type i = it_end; i != it_pos; --i)
			    this->_array[i] = this->_array[i - 1];
			this->_alloc.construct(this->_array + it_pos, val);
			this->_size++;
			return iterator(this->_array + it_pos);
		}

		void insert (iterator position, size_type n, const value_type& val) {
		    size_type it_end = end().getElement() - begin().getElement();
		    size_type it_pos = position.getElement() - begin().getElement();
		    if (this->_size + n > this->_capacity)
		        reserve(this->_capacity + n + 15);
		    for (size_type i = it_end + n; i != it_pos + n; --i)
		        this->_array[i] = this->_array[i - n - 1];
		    for (size_type i = it_pos; i != it_pos + n; ++i)
		        this->_alloc.construct(this->_array + i, val);
		    this->_size += n;
		}

		template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last) {}

		iterator erase (iterator position) {
		    difference_type it_end = end().getElement() - begin().getElement();
		    difference_type it_pos = position.getElement() - begin().getElement();
		    this->_alloc.destroy(this->_array + it_pos);
		    for (difference_type i = it_pos; i != it_end; ++i)
		        this->_array[i] = this->_array[i + 1];
		    this->_size--;
		    return iterator(this->_array + it_pos);
		}
		iterator erase (iterator first, iterator last) {
			for (;first != last;) {
				erase(--last);
			}
			return last;
		}

		pointer getElement(void) { return this->_it; }

		void swap (vector& x) {
		    pointer array = x._array;
		    size_type size = x._size;
		    size_type capacity = x._capacity;
		    allocator_type alloc = x._alloc;

		    this->_array = array;
		    this->_size = size;
		    this->_capacity = capacity;
		    this->_alloc = alloc;

		    x._array = this->_array;
		    x._size = this->_size;
		    x._capacity = this->_capacity;
		    x._alloc = this->_alloc;
		}

		void clear() {
		    for (size_type i = 0; i != this->_size; ++i)
		        this->_alloc.destroy(this->_array + i);
		    this->_size = 0;
		}

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