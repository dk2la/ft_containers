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

		template<bool Cond, class B = void>
		struct enable_if {};
		template<class B>
		struct enable_if<true, B> { typedef B type; };
	public:
		class   iterator;
		class   const_iterator;
		class   reverse_iterator;
		class   const_reverse_iterator;
		//constructor:
		explicit vector (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _array(nullptr), _alloc(alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
		                 const allocator_type& alloc = allocator_type()): _size(n), _capacity(_size), _array(nullptr), _alloc(alloc) {
			_array = _alloc.allocate(this->_capacity);
			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(_array + i, val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0):
				_size(0), _capacity(0), _array(nullptr), _alloc(alloc) {
			_array = _alloc.allocate(_capacity);
			for (; first != last; ++first)
				push_back(*first);
		}

		/* copy constructor */
		vector (const vector& x): _size(x._size), _capacity(x._capacity), _array(x._array), _alloc(x._alloc) {
			_array = _alloc.allocate(_capacity);
			for (size_type i = 0; i < this->_size; ++i)
				this->_alloc.construct(this->_array + i, *(x._array + i));
		}

		//destructor:
		~vector() {
//		    clear();
//		    if (_capacity)
//		    	_alloc.deallocate(_array, _capacity);
//		    this->_capacity = 0;
		}

		//operator=:
		vector& operator=(const vector& x) { // TODO добавить изменение array
			clear();
			insert(begin(), x.begin(), x.end());
            return *this;
		}

		//Member function:
		iterator begin() { return iterator(this->_array); }
		const_iterator begin() const { return const_iterator(this->_array); }

		iterator end() { return iterator(this->_array + this->_size); }
		const_iterator end() const { return const_iterator(this->_array + this->_size); }

		reverse_iterator rbegin() { return reverse_iterator(this->_array + this->_size - 1); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_array + this->_size - 1); }

		reverse_iterator rend() { return reverse_iterator(this->_array - 1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->_array - 1); }

		/* Capacity */
		size_type size() const { return this->_size; }

		size_type max_size() const {
			if (sizeof(value_type) == 1)
				return ((size_t)(-1) / sizeof(value_type) / 2);
			else
				return ((size_t)(-1) / sizeof(value_type));
		}

		void resize (size_type n, value_type val = value_type()) {
			if (n < _size)
				while (_size != n)
					pop_back();
			else if (n > _size) {
				while (_size != n)
					push_back(val);
			}
		}

		size_type capacity() const { return this->_capacity; }

		bool empty() const { return (this->_size == 0); }

		void reserve (size_type n) {
			if (_capacity > n)
				return ;
			else {
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&tmp[i], _array[i]);
				for (size_type i = 0; i != _size; ++i)
					_alloc.destroy(_array + i);
				if (_capacity)
					_alloc.deallocate(_array, _capacity);
				_capacity = n;
				_array = tmp;
			}
		}

		//element access:
		reference operator[] (size_type n) {
		    return _array[n];
		}
		const_reference operator[] (size_type n) const {
		    return _array[n];
		}

		reference at (size_type n) {
		    if (_size <= n)
		        throw std::out_of_range("out of range");
		    else
		    	return _array[n];
		}
		const_reference at (size_type n) const {
		    if (_size <= n)
		        throw std::out_of_range("out of range");
		    else
		    	return _array[n];
		}

		reference front() { return *_array; }
		const_reference front() const { return *_array; }

		reference back() { return *(this->_array + this->_size - 1); }
		const_reference back() const { return *(this->_array + this->_size - 1); }

		//Modifiters:
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
					 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
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
			if (_capacity != 0) {
				if (_size == _capacity)
					reserve(_capacity + _size);
				_alloc.construct(_array + _size, val);
				++_size;
			}
			else {
				_size = 1;
				_capacity = 1;
				_array = _alloc.allocate(this->_capacity);
				for (size_type i = 0; i < _size; ++i)
					this->_alloc.construct(_array + i, val);
			}
		}

		void pop_back() {
			_alloc.destroy(_array + --_size);

		}

		iterator insert (iterator position, const value_type& val) {
			difference_type end_position = end().getElement() - begin().getElement();
			difference_type current_position = position.getElement() - begin().getElement();
			if (_size + 1 > _capacity)
			    reserve(this->_capacity + 15);
			for (difference_type i = end_position; i != current_position; --i)
			    _array[i] = _array[i - 1];
			_alloc.construct(_array + current_position, val);
			_size++;
			return iterator(_array + current_position);
		}

		void insert (iterator position, size_type n, const value_type& val) { // TODO переписать, не добавляется одно значение
			difference_type end_position = end().getElement() - begin().getElement();
			difference_type current_position = position.getElement() - begin().getElement();
		    if (_size + n > _capacity)
		        reserve(_capacity + n + 15);
		    for (size_type i = end_position + n ; i >= current_position + n; --i)
		    	_array[i] = _array[i - n];
		    for (size_type i = current_position; i != current_position + n; ++i)
		        _alloc.construct(_array + i, val);
		    _size += n;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
					 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			size_type n = static_cast<size_type>(last.operator->() - first.operator->());
			difference_type end_position = end().getElement() - begin().getElement();
			difference_type current_position = position.getElement() - begin().getElement();
			if (_size + n > _capacity)
				reserve(_capacity + n + 15);
			for (size_type i = end_position + n; i >= current_position + n; --i)
				_array[i] = _array[i - n];
			for (size_type i = current_position; i != current_position + n; ++i, ++first)
				_alloc.construct(_array + i, *first);
			_size += n;
		}

		iterator erase (iterator position) {
		    difference_type it_end = end().getElement() - begin().getElement();
		    difference_type it_pos = position.getElement() - begin().getElement();
		    _alloc.destroy(_array + it_pos);
		    for (difference_type i = it_pos; i != it_end; ++i)
		        _array[i] = _array[i + 1];
		    _size--;
		    return iterator(_array + it_pos);
		}
		iterator erase (iterator first, iterator last) {
			while (first != last) {
				erase(last);
				--last;
			}
			return last;
		}

		pointer getElement(void) { return _array; }

		void swap (vector& x) { // TODO свапает неправильно значения
		    pointer array = x._array;
		    size_type size = x._size;
		    size_type capacity = x._capacity;
		    allocator_type alloc = x._alloc;

		    x._array = _array;
			x._size = _size;
			x._capacity = _capacity;
			x._alloc = _alloc;


		    _array = array;
		    _size = size;
		    _capacity = capacity;
		    _alloc = alloc;
		}

		void clear() {
		    for (size_type i = 0; i != _size; ++i)
		        _alloc.destroy(_array + i);
		    _size = 0;
		}

	class iterator: public std::iterator<std::random_access_iterator_tag, value_type> {
	private:
		pointer _it;
	public:
		explicit iterator(pointer it = nullptr) : _it(it) {};
		~iterator() {};
		iterator & operator=(const iterator &it) {
			this->_it = it._it;
			return *this;
		}
		iterator(const iterator &it) { *this = it; }
		iterator & operator++() { this->_it = _it + 1; return *this; };
		iterator operator++(int) {
			iterator tmp(_it);
			this->_it = _it + 1;
			return tmp;
		};
		iterator & operator--() { this->_it = _it - 1; return *this; };
		iterator operator--(int) {
			iterator tmp(_it);
			this->_it = this->_it - 1;
			return tmp;
		};

		iterator operator+(difference_type val) const { return iterator(_it + val); };
		iterator operator-(difference_type val) const { return iterator(_it - val); };
		difference_type operator+(iterator &it) const { return _it + it._it; }
		difference_type operator-(iterator &it) const { return _it - it._it; }
		iterator &operator+=(difference_type val) { _it += val; return *this; };
		iterator &operator-=(difference_type val) { _it -= val; return *this; };
		const_reference operator[](const_reference ref) { return _it[ref]; };
		reference operator*() { return *this->_it; }
		pointer operator->() { return this->_it; }

		bool operator==(const iterator &other) const { return _it == other.getElement(); };
		bool operator!=(const iterator &other) const { return _it != other.getElement(); };
		bool operator<=(const iterator &other) const { return _it <= other.getElement(); };
		bool operator>=(const iterator &other) const { return _it >= other.getElement(); };
		bool operator<(const iterator &other) const { return _it < other.getElement(); };
		bool operator>(const iterator &other) const { return _it > other.getElement(); };

		bool operator==(const const_iterator &other) const { return _it == other.getElement(); };
		bool operator!=(const const_iterator &other) const { return _it != other.getElement(); };
		bool operator<=(const const_iterator &other) const { return _it <= other.getElement(); };
		bool operator>=(const const_iterator &other) const { return this->_it >= other.getElement(); };
		bool operator<(const const_iterator &other) const { return _it < other.getElement(); };
		bool operator>(const const_iterator &other) const { return _it > other.getElement(); };
		pointer getElement() const { return _it; }
	};

	/* const iterator */
	class const_iterator: public std::iterator<std::random_access_iterator_tag, value_type const > {
	private:
		pointer _it;
	public:
		explicit const_iterator(pointer it = nullptr) : _it(it) {};
		~const_iterator() {};
		const_iterator & operator=(const_iterator const &it) {
			this->_it = it._it;
			return *this;
		}
		const_iterator & operator=(iterator const &it) {
			this->_it = it.getElement();
			return *this;
		}
		const_iterator(const_iterator const &it) { *this = it; }
		const_iterator(iterator const &it) { *this = it; }
		const_iterator & operator++() { this->_it = _it + 1; return *this; };
		const_iterator operator++(int) {
			const_iterator tmp(_it);
			this->_it = _it + 1;
			return tmp;
		};
		const_iterator & operator--() { this->_it = _it - 1; return *this; };
		const_iterator operator--(int) {
			iterator tmp(_it);
			this->_it = this->_it - 1;
			return tmp;
		};

		const_iterator operator+(difference_type val) const { return const_iterator(_it + val); };
		const_iterator operator-(difference_type val) const { return const_iterator(_it - val); };
		const_iterator &operator+=(difference_type val) { _it += val; return *this; };
		const_iterator &operator-=(difference_type val) { _it -= val; return *this; };
		difference_type operator+(iterator it) const { return _it - it._it; }
		difference_type operator-(iterator it) const { return _it - it._it; }
		const_reference operator[](const_reference ref) { return _it[ref]; };
		const_reference operator*() { return *this->_it; }
		const_pointer operator->() { return this->_it; }

		bool operator==(iterator const &other) const { return _it == other.getElement(); };
		bool operator!=(iterator const &other) const { return _it != other.getElement(); };
		bool operator<=(iterator const &other) const { return _it <= other.getElement(); };
		bool operator>=(iterator const &other) const { return _it >= other.getElement(); };
		bool operator<(iterator const &other) const { return _it < other.getElement(); };
		bool operator>(iterator const &other) const { return _it > other.getElement(); };

		bool operator==(const const_iterator &other) const { return _it == other.getElement(); };
		bool operator!=(const const_iterator &other) const { return _it != other.getElement(); };
		bool operator<=(const const_iterator &other) const { return _it <= other.getElement(); };
		bool operator>=(const const_iterator &other) const { return _it >= other.getElement(); };
		bool operator<(const const_iterator &other) const { return _it < other.getElement(); };
		bool operator>(const const_iterator &other) const { return _it > other.getElement(); };
		const_pointer getElement() const { return this->_it; }
	};

	/* reverse iterator */
	class reverse_iterator: public std::reverse_iterator<iterator> {
	private:
		pointer _it;
	public:
		explicit reverse_iterator(pointer it = nullptr) : _it(it) {};
		~reverse_iterator() {};
		reverse_iterator & operator=(const iterator &it) {
			this->_it = it._it;
			return *this;
		}
		reverse_iterator(reverse_iterator const &it) { *this = it; }
		reverse_iterator & operator++() { this->_it = _it - 1; return *this; };
		reverse_iterator operator++(int) {
			reverse_iterator tmp(_it);
			this->_it = _it - 1;
			return tmp;
		};
		reverse_iterator & operator--() { this->_it = _it + 1; return *this; };
		reverse_iterator operator--(int) {
			reverse_iterator tmp(_it);
			this->_it = this->_it + 1;
			return tmp;
		};

		reverse_iterator operator+(difference_type val) const { return reverse_iterator(_it - val); };
		reverse_iterator operator-(difference_type val) const { return reverse_iterator(_it + val); };
		difference_type operator+(reverse_iterator &it) const { return _it - it._it; }
		difference_type operator-(reverse_iterator &it) const { return _it + it._it; }
		reverse_iterator &operator+=(difference_type val) { _it -= val; return *this; };
		reverse_iterator &operator-=(difference_type val) { _it += val; return *this; };
		const_reference operator[](const_reference ref) const { return *(_it - ref); };
		reference operator*() { return *this->_it; }
		pointer operator->() { return this->_it; }

		bool operator==(const reverse_iterator &other) const { return _it == other.getElement(); };
		bool operator!=(const reverse_iterator &other) const { return _it != other.getElement(); };
		bool operator<=(const reverse_iterator &other) const { return _it >= other.getElement(); };
		bool operator>=(const reverse_iterator &other) const { return _it <= other.getElement(); };
		bool operator<(const reverse_iterator &other) const { return _it > other.getElement(); };
		bool operator>(const reverse_iterator &other) const { return _it < other.getElement(); };

		bool operator==(const const_reverse_iterator &other) const { return _it == other.getElement(); };
		bool operator!=(const const_reverse_iterator &other) const { return _it != other.getElement(); };
		bool operator<=(const const_reverse_iterator &other) const { return _it >= other.getElement(); };
		bool operator>=(const const_reverse_iterator &other) const { return _it <= other.getElement(); };
		bool operator<(const const_reverse_iterator &other) const { return _it > other.getElement(); };
		bool operator>(const const_reverse_iterator &other) const { return _it < other.getElement(); };
		pointer getElement() const { return this->_it; }
	};

	/* const reverse iterator */
	class const_reverse_iterator: public std::reverse_iterator<const_iterator> {
	private:
		pointer _it;
	public:
		explicit const_reverse_iterator(pointer it = nullptr) : _it(it) {};
		~const_reverse_iterator() {};
		const_reverse_iterator & operator=(const const_reverse_iterator &it) {
			this->_it = it._it;
			return *this;
		}
		const_reverse_iterator & operator=(const reverse_iterator &it) {
			this->_it = it.getElement();
			return *this;
		}
		const_reverse_iterator(reverse_iterator const &it) { *this = it; }
		const_reverse_iterator(const_reverse_iterator const &it) { *this = it; }
		const_reverse_iterator & operator++() { this->_it = _it - 1; return *this; };
		reverse_iterator operator++(int) {
			reverse_iterator tmp(_it);
			this->_it = _it - 1;
			return tmp;
		};
		const_reverse_iterator & operator--() { this->_it = _it + 1; return *this; };
		const_reverse_iterator operator--(int) {
			const_reverse_iterator tmp(_it);
			this->_it = this->_it + 1;
			return tmp;
		};

		const_reverse_iterator operator+(difference_type val) const { return const_reverse_iterator(_it - val); };
		const_reverse_iterator operator-(difference_type val) const { return const_reverse_iterator(_it + val); };
		difference_type operator+(const_reverse_iterator &it) const { return _it - it._it; }
		difference_type operator-(const_reverse_iterator &it) const { return _it + it._it; }
		const_reverse_iterator &operator+=(difference_type val) { _it -= val; return *this; };
		const_reverse_iterator &operator-=(difference_type val) { _it += val; return *this; };
		const_reference operator[](const_reference ref) { return *(_it - ref); };
		const_reference operator*() { return *this->_it; }
		const_pointer operator->() { return this->_it; }

		bool operator==(const reverse_iterator &other) const { return _it == other.getElement(); };
		bool operator!=(const reverse_iterator &other) const { return _it != other.getElement(); };
		bool operator<=(const reverse_iterator &other) const { return _it >= other.getElement(); };
		bool operator>=(const reverse_iterator &other) const { return _it <= other.getElement(); };
		bool operator<(const reverse_iterator &other) const { return _it > other.getElement(); };
		bool operator>(const reverse_iterator &other) const { return _it < other.getElement(); };

		bool operator==(const const_reverse_iterator &other) const { return _it == other.getElement(); };
		bool operator!=(const const_reverse_iterator &other) const { return _it != other.getElement(); };
		bool operator<=(const const_reverse_iterator &other) const { return _it >= other.getElement(); };
		bool operator>=(const const_reverse_iterator &other) const { return _it <= other.getElement(); };
		bool operator<(const const_reverse_iterator &other) const { return _it > other.getElement(); };
		bool operator>(const const_reverse_iterator &other) const { return _it < other.getElement(); };
		const_pointer getElement() const { return this->_it; }
	};
	private:
		size_type       _size;
		size_type       _capacity;
		pointer         _array;
		allocator_type  _alloc;
	};
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator lhs_it_begin = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lhs_it_end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_begin = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_end = rhs.end();
		if (lhs.size() != rhs.size())
			return false;
		while (lhs_it_begin != lhs_it_end) {
			if (*lhs_it_begin != *rhs_it_begin)
				return false;
			lhs_it_begin++;
			rhs_it_begin++;
		}
		return true;
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator lhs_it_begin = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lhs_it_end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_begin = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_end = rhs.end();

		if (lhs.size() != rhs.size())
			return true;
		while (lhs_it_begin != lhs_it_end) {
			if (*lhs_it_begin != *rhs_it_begin)
				return true;
			lhs_it_begin++;
			rhs_it_begin++;
		}
		return false;
	}
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator lhs_it_begin = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lhs_it_end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_begin = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_end = rhs.end();

		if (lhs.size() < rhs.size())
			return true;
		while (lhs_it_begin != lhs_it_end) {
			if (*lhs_it_begin < *rhs_it_begin)
				return true;
			lhs_it_begin++;
			rhs_it_begin++;
		}
		return (rhs_it_begin != rhs_it_end);
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator lhs_it_begin = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lhs_it_end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_begin = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_end = rhs.end();

		if (lhs.size() <= rhs.size())
			return true;
		while (lhs_it_begin != lhs_it_end) {
			if (*lhs_it_begin <= *rhs_it_begin)
				return true;
			lhs_it_begin++;
			rhs_it_begin++;
		}
		return false;
	}
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator lhs_it_begin = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lhs_it_end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_begin = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_end = rhs.end();

		if (lhs.size() > rhs.size())
			return true;
		while (lhs_it_begin != lhs_it_end) {
			if (*lhs_it_begin > *rhs_it_begin)
				return true;
			lhs_it_begin++;
			rhs_it_begin++;
		}
		return (lhs_it_begin != lhs_it_end);
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator lhs_it_begin = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lhs_it_end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_begin = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rhs_it_end = rhs.end();

		if (lhs.size() >= rhs.size())
			return true;
		while (lhs_it_begin != lhs_it_end) {
			if (*lhs_it_begin >= *rhs_it_begin)
				return true;
			lhs_it_begin++;
			rhs_it_begin++;
		}
		return false;
	}
}