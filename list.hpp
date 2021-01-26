#pragma once

#include <iostream>
#include <iterator>

namespace ft {
	template < class T, class Alloc = allocator<T> >
	class list {
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	private:
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;
		list*   _end;
		typedef struct list {
			value_type* field; // поле данных
			struct list *next; // указатель на следующий элемент
			struct list *prev; // указатель на предыдущий элемент
		};
		typedef typename allocator_type::template rebind<list>::other allocator_rebind_type;
		allocator_rebind_type _allocator_rebind;

		void    _createList(void) {
			this->_end = this->_allocator_rebind(1);
			this->_end->content = this->alloc.allocate(1);
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_size = 0;
		}

		void    _destroyList(void) {

		}

		list*   insertList(list* new_list);
	public:
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		//Constructors
		explicit list (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _alloc(0) _end(0) {
			this->_createList();
		}

		explicit list (size_type n, const value_type& val = value_type(),
		               const allocator_type& alloc = allocator_type()) {
			for (; n != 0; --n)
				push_back(val);
		}

		template <class InputIterator>
		list (InputIterator first, InputIterator last,
		      const allocator_type& alloc = allocator_type());

		list (const list& x) {}

		~list() {
			this->_destroyList();
			this->_size = 0;
			this->_capacity = 0;
		}

		list& operator= (const list& x);

		/* Iterators */
		iterator begin() { return iterator(this->_end->next); }
		const_iterator begin() const { return const_iterator(this->_end->next); }

		iterator end() { return iterator(this->_end); }
		const_iterator end() const { return const_iterator(this->_end); }

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/* Capacity */
		bool empty() const ( return (this->_size == 0));

		size_type size() const { return this->_size; }

		size_type max_size() const {
			if (sizeof(value_type) == 1)
				return ((size_t)(-1) / sizeof(value_type) / 2);
			else
				return ((size_t)(-1) / sizeof(value_type));
		}

		/* Element access */
		reference front() { return *(this->_end->next); }
		const_reference front() const { return *(this->_end->next); }

		reference back() { return *(this->_end); }
		const_reference back() const { return *(this->_end); }

		/* Modifiers */
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);

		void assign (size_type n, const value_type& val);

		void push_front (const value_type& val);

		void pop_front();

		void push_back (const value_type& val) {
		}

		void pop_back() {
			this->_size--;
		}

		iterator insert (iterator position, const value_type& val);

		void insert (iterator position, size_type n, const value_type& val);

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);

		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);

		void swap (list& x);

		void resize (size_type n, value_type val = value_type());

		void clear();

		/* Operations */
		void splice (iterator position, list& x);

		void splice (iterator position, list& x, iterator i);

		void splice (iterator position, list& x, iterator first, iterator last);

		void remove (const value_type& val);

		template <class Predicate>
		void remove_if (Predicate pred);

		void unique();

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred);

		void merge (list& x);

		template <class Compare>
		void merge (list& x, Compare comp);

		void sort();

		template <class Compare>
		void sort (Compare comp);

		void reverse();

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
	};

}