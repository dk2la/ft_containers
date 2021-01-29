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
		typedef struct _List {
			value_type* field; // поле данных
			struct _List *next; // указатель на следующий элемент
			struct _List *prev; // указатель на предыдущий элемент
		};
		typedef typename allocator_type::template rebind<_List>::other allocator_rebind_type;
		allocator_rebind_type _allocator_rebind;

		void    _createList(void) {
			this->_end = this->_allocator_rebind(1);
			this->_end->content = this->alloc.allocate(1);
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_size = 0;
		}

		_List*   _createNode(value_type& val) {
			_List* tmp = this->_allocator_rebind(1);
			tmp->content = this->_alloc.allocate(1);
			this->_alloc.construct(tmp->content, val);
			this->_size++;
			return tmp;
		}

		_List*   _insertList(_List* newNode, _List* pNode, _List* nNode) {
			this->_linkNode(pNode, newNode);
			this->_linkNode(newNode, nNode);
		}

		void    _linkNode(_List* prevNode, _List* nextNode) {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}

	public:
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		//Constructors
		explicit _List (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _alloc(0) _end(0) {
			this->_createList();
		}

		explicit _List (size_type n, const value_type& val = value_type(),
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

		reverse_iterator rbegin() { return reverse_iterator(this->_end); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_end); }

		reverse_iterator rend() { return reverse_iterator(this->_end->next); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->_end->next); }

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
		reference front() { return *(this->_end->next->content); }
		const_reference front() const { return *(this->_end->next->content); }

		reference back() { return *(this->_end->content); }
		const_reference back() const { return *(this->_end->content); }

		/* Modifiers */
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			if (!this->empty)
				this->clear();
			for (;first != last; ++first)
				this->push_back(*first);
		}

		void assign (size_type n, const value_type& val) {
			if (!this->empty)
				this->clear();
			for (difference_type i = 0; i < n; ++i)
				this->push_back(val);
		}

		void push_front (const value_type& val) {
			_List* newNode = this->_createList(val);
			this->_insertList(newNode, this->_end, this->_end->next);
		}

		void pop_front() {
			_List* tmp = this->_end->next;
			this->_insertList(tmp->prev, tmp->next);
			this->_alloc.destroy(tmp->content);
			this->_alloc.deallocate(tmp->content, 1);
			this->_allocator_rebind.deallocate(tmp, 1);
			this->_size--;
		}

		void push_back (const value_type& val) {
			_List* newNode = this->_createList(val);
			this->_insertList(newNode, this->_end->prev, this->_end);
		}

		void pop_back() {
			_List* tmp = this->_end->prev;
			this->_alloc.destroy(tmp->content);
			this->_alloc.deallocate(tmp->content, 1);
			this->_allocator_rebind.deallocate(tmp, 1);
			this->_size--;
		}

		iterator insert (iterator position, const value_type& val) {
			_List* tmp = this->_createNode(val);
			_List* pos_list = position.getElement();
			this->_linkNode(node, list->prev, list);
			return iterator(tmp);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			for (; n != 0; n--)
				insert(position, val);
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last) {
			for (; first != last; ++first)
				insert(position, *first);
		}

		iterator erase (iterator position) {
			_List* tmp = position.getElement();
			_List* save_node = tmp->next;
			this->_linkNode(tmp->prev, tmp->next);
			this->_alloc.destroy(tmp->content);
			this->_alloc.deallocate(tmp->content, 1);
			this->_allocator_rebind.deallocate(tmp, 1);
			this->_size--;
			return iterator(save_node);
		}
		iterator erase (iterator first, iterator last) {
			for (;first != last;)
				erase(++first);
			return last;
		}

		void swap (list& x) {

		}

		void resize (size_type n, value_type val = value_type()) {
			if (this->_size < n) {
				for (;n < this->_size;)
					this->erase(iterator(this->_end->prev));
			}
			else if (this->_size > n) {
				for (;this->_size < n;)
					this->push_back(val);
			}
		}

		void clear() {
			for (; this->_size != 0; --_size)
				pop_back();
		}

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

		_List*  3

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