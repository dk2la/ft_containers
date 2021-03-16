#pragma once

#include <iostream>
#include <iterator>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class list {
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<bool B, class C = void>
		struct enable_if {};

		template <class C>
		struct enable_if <true, C> { typedef T type; };
	private:
	    size_type _size;
		allocator_type _alloc;

		typedef struct List {
			value_type* content; // поле данных
			struct List *next; // указатель на следующий элемент
			struct List *prev; // указатель на предыдущий элемент
		}      _List;
        _List*   _end;

        typedef typename allocator_type::template rebind<_List>::other allocator_rebind_type;
		allocator_rebind_type _allocator_rebind;

		struct _less {
			bool operator()(const value_type& first, const value_type& second) { return first < second; }
		};

		struct _equal {
			bool operator()(const value_type& first, const value_type& second) { return first == second; }
		};

		_List*   _createNode(const value_type& val) {
			_List* tmp = this->_allocator_rebind.allocate(1);
			tmp->content = this->_alloc.allocate(1);
			this->_alloc.construct(tmp->content, val);
			this->_size++;
			return tmp;
		}

		void	_destroyNode(_List* cur) {
			_alloc.destroy(cur->content);
		}

		void	_deallocateNode(_List* cur) {
			_alloc.deallocate(cur->content, 1);
			_allocator_rebind.deallocate(cur, 1);
		}

		void   _insertList(_List* current, _List* prevNode, _List* nextNode) {
			this->_linkNode(prevNode, current);
			this->_linkNode(current, nextNode);
		}

		void    _linkNode(_List* prevNode, _List* nextNode) {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}

		template <class Compare>
		void	_mergeSort(_List** headRef, Compare comp) { // Принимаем ссылку на begin node
			_List*	head = *headRef;
			_List*	a;
			_List*	b;

			if ((head == _end) || (head->next == _end))
				return;
			_frontBackSplit(head, &a, &b);
			_mergeSort(&a, comp);
			_mergeSort(&b, comp);
			*headRef = _sortedMerge(a, b);
		}

		void	_frontBackSplit(_List* head, _List** frontRef, _List** backRef) {
			_List* fast;
			_List* slow;
			slow = head; // begin node
			fast = head->next; // ++begin node

			while (fast != _end) {
				fast = fast->next;
				if (fast != _end) {
					slow = slow->next;
					fast = fast->next;
				}
			}
			*frontRef = head;
			*backRef = slow->next;
			slow->next = _end;
		}

		_List*	_sortedMerge(_List* a, _List* b) {
			_List* result = _end;
			if (a == _end)
				return b;
			else if (b == _end)
				return a;
			if (a->content <= b->content) {
				result = a;
				result->next = _sortedMerge(a->next, b);
			}
			else {
				result = b;
				result->next = _sortedMerge(a, b->next);
			}
			return result;
		}
	public:
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		class iterator: public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_List* _it;
		public:
			explicit iterator(_List* it = nullptr): _it(it) {};
			~iterator() {};
			iterator & operator=(const iterator &it) { this->_it = it._it; return *this; };
			iterator(const iterator &it) { *this = it; };
			iterator & operator++() { this->_it = _it->next; return *this; };
			iterator operator++(int) {
				iterator tmp(_it);
				this->_it = _it->next;
				return tmp;
			};
			iterator & operator--() { this->_it = _it->prev; return *this; };
			iterator operator--(int) {
				iterator tmp(_it);
				this->_it = _it->prev;
				return tmp;
			};
			bool operator==(const iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const iterator &it) const { return this->_it->content != it.getElement()->content; };
			bool operator==(const const_iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const const_iterator &it) const { return this->_it->content != it.getElement()->content; };

			T & operator*() const { return *(this->_it->content); }
			T * operator->() const { return this->it->content; }

			_List *getElement() const { return _it; }
		};

		/* const_iterator */
		class const_iterator: public std::iterator<std::bidirectional_iterator_tag, value_type const > {
		private:
			_List* _it;
		public:
			explicit const_iterator(_List* it = nullptr) : _it(it) {};
			const_iterator(const const_iterator &it) { *this = it; };
			const_iterator(const iterator &it) { *this = it; };
			~const_iterator() {};
			const_iterator& operator=(const const_iterator &it)  { this->_it = it._it; return *this; };
			const_iterator& operator=(const iterator &it)  { this->_it = it.getElement(); return *this; };
			const_iterator & operator++() { this->_it = _it->next; return *this; };
			const_iterator operator++(int) {
				const_iterator tmp(_it);
				this->_it = _it->next;
				return tmp;
			};
			const_iterator & operator--() { this->_it = _it->prev; return *this; };
			const_iterator operator--(int) {
				const_iterator tmp(_it);
				this->_it = _it->prev;
				return tmp;
			};
			bool operator==(const const_iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const const_iterator &it) const { return this->_it->content != it.getElement()->content; };
			bool operator==(const iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const iterator &it) const { return this->_it->content != it.getElement()->content; };

			T & operator*() const { return *(this->_it->content); };
			T * operator->() const { return this->it->content; }

			_List *getElement() const { return _it; }
		};

		/* reverse_iterator */
		class reverse_iterator: public std::reverse_iterator<list::iterator>{
		private:
			_List* _it;
		public:
			explicit reverse_iterator(_List* it = nullptr): _it(it) {};
			~reverse_iterator() {};
			reverse_iterator(const reverse_iterator &it) { *this = it; };
			reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it._it; return *this; };
			reverse_iterator & operator++() { this->_it = _it->prev; return *this; };
			reverse_iterator operator++(int) {
				reverse_iterator tmp(_it);
				this->_it = _it->prev;
				return tmp;
			};
			reverse_iterator & operator--() { this->_it = _it->next; return *this; };
			reverse_iterator operator--(int) {
				reverse_iterator tmp(_it);
				this->_it = _it->next;
				return tmp;
			};

			bool operator==(const reverse_iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const reverse_iterator &it) const { return this->_it->content != it.getElement()->content; };

			bool operator==(const const_reverse_iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const const_reverse_iterator &it) const { return this->_it->content != it.getElement()->content; };
			T & operator*() const { return *(this->_it->content); };
			T * operator->() const { return this->it->content; }

			_List *getElement() const { return _it; }
		};

		/* const_reverse_iterator */
		class const_reverse_iterator: public std::reverse_iterator<list::const_iterator> {
		private:
			_List* _it;
		public:
			explicit const_reverse_iterator(_List* it = nullptr): _it(it) {};
			~const_reverse_iterator() {};
			const_reverse_iterator & operator=(const const_reverse_iterator &it) { this->_it = it._it; return *this; };
			const_reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it.getElement(); return *this; };
			const_reverse_iterator(const const_reverse_iterator &it) { *this = it; };
			const_reverse_iterator(const reverse_iterator &it) { *this = it; };
			const_reverse_iterator & operator++() { this->_it = _it->prev; return *this; };
			const_reverse_iterator operator++(int) {
				const_reverse_iterator tmp(_it);
				this->_it = _it->prev;
				return tmp;
			};
			const_reverse_iterator & operator--() { this->_it = _it->next; return *this; };
			const_reverse_iterator operator--(int) {
				const_reverse_iterator tmp(_it);
				this->_it = _it->next;
				return tmp;
			};

			bool operator==(const const_reverse_iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const const_reverse_iterator &it) const { return this->_it->content != it.getElement()->content; };

			bool operator==(const reverse_iterator &it) const { return this->_it->content == it.getElement()->content; };
			bool operator!=(const reverse_iterator &it) const { return this->_it->content != it.getElement()->content; };
			reference operator*() const { return *(this->_it->content); }
			pointer operator->() const { return this->it->content; }

			_List *getElement() const { return _it; }
		};

		//Constructors
		explicit list (const allocator_type& alloc = allocator_type()): _size(0), _alloc(alloc), _end(0) {
			_end = _allocator_rebind.allocate(1);
			_end->content = _alloc.allocate(1);
			_end->next = _end;
			_end->prev = _end;
			_size = 0;
		}

		explicit list (size_type n, const value_type& val = value_type(),
		               const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0) {
			_end = _allocator_rebind.allocate(1);
			_end->content = _alloc.allocate(1);
			_end->next = _end;
			_end->prev = _end;
			_size = 0;
			for (; n != 0; n--)
				push_back(val);
		}

		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			  typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0): _alloc(alloc), _size(0) {
			_end = _allocator_rebind.allocate(1);
			_end->content = _alloc.allocate(1);
			_end->next = _end;
			_end->prev = _end;
			_size = 0;
			while (first != last) {
				push_back(*first);
				first++;
			}
		}

		list (const list& x): _alloc(x._alloc), _end(0) {
			_end = _allocator_rebind.allocate(1);
			_end->content = _alloc.allocate(1);
			_end->next = _end;
			_end->prev = _end;
			_size = 0;
			*this = x;
		}

		~list() {
			clear();
			_deallocateNode(_end);
		}

		list& operator=(const list& x) {
			if (!empty())
					clear();
			const_iterator it = x.begin();
			const_iterator ite = x.end();
			while (it != ite) {
				push_back(*it);
				it++;
			}
			return *this;
		}

		/* Iterators */
		iterator begin() { return iterator(this->_end->next); }
		const_iterator begin() const { return const_iterator(this->_end->next); }

		iterator end() { return iterator(this->_end); }
		const_iterator end() const { return const_iterator(this->_end); }

		reverse_iterator rbegin() { return reverse_iterator(this->_end->prev); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_end->prev); }

		reverse_iterator rend() { return reverse_iterator(this->_end); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->_end); }

		/* Capacity */
		bool empty() const { return (this->_size == 0); }

		size_type size() const { return this->_size; }

		size_type max_size() const {
			if (sizeof(value_type) == 1)
				return ((size_t)(-1) / sizeof(value_type) / 2);
			else
				return ((size_t)(-1) / sizeof(value_type));
		}

		/* Element access */
		reference front() { return *(_end->next->content); }
		const_reference front() const { return *(_end->next->content); }

		reference back() { return *(_end->prev->content); }
		const_reference back() const { return *(_end->prev->content); }

		/* Modifiers */
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
					 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			clear();
			insert(begin(), first, last);
		}

		void assign (size_type n, const value_type& val) {
			clear();
			insert(begin(), n, val);
		}

		void push_front(const value_type& val) {
			_List* current = this->_createNode(val);
			_insertList(current, this->_end, this->_end->next);
		}

		void pop_front() {
			_List* tmp = _end->next;
			_linkNode(tmp->prev, tmp->next);
			_destroyNode(tmp);
			_deallocateNode(tmp);
			_size--;
		}

		void push_back (const value_type& val) {
			_List* current = _createNode(val);
			_insertList(current, _end->prev, _end);
		}

		void pop_back() {
			_List* tmp = _end->prev;
			_linkNode(tmp->prev, tmp->next);
			_destroyNode(tmp);
			_deallocateNode(tmp);
			_size--;
		}

		iterator insert (iterator position, const value_type& val) {
			_List* current = _createNode(val);
			_List* it_pos = position.getElement();
			_insertList(current, it_pos->prev, it_pos);
			return iterator(current);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			for (; n != 0; n--)
				insert(position, val);
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
					 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			for (; first != last; ++first)
				insert(position, *first);
		}

		iterator erase (iterator position) {
			_List* it_pos = position.getElement();
			_List* save_node = it_pos->next;
			_linkNode(it_pos->prev, it_pos->next);
			_destroyNode(it_pos);
			_deallocateNode(it_pos);
			_size--;
			return iterator(save_node);
		}
		iterator erase (iterator first, iterator last) {
			while (first != last)
				erase(first++);
			return last;
		}

		void swap (list& x) {
            _List* tmp = _end;
            _end = x._end;
            x._end = tmp;
            size_type size = _size;
            _size = x._size;
            x._size = size;
		}

		void resize (size_type n, value_type val = value_type()) {
			while (n < _size)
				erase(iterator(_end->prev));
			while (_size < n)
				push_back(val);
		}

		void clear() {
			while (_size != 0)
				pop_back();
		}

		/* Operations */
		void splice (iterator position, list& x) {
			_List*	tmp = position.getElement()->prev;
			_List*	tmpPos = position.getElement();
			_linkNode(tmp, x._end->next);
			_linkNode(x._end->prev, tmpPos);
			_linkNode(x._end, x._end);
			_size += x._size;
			x._size = 0;
		}

		void splice (iterator position, list& x, iterator i) {
			_List*	curr_node = position.getElement();
			_List*	from_pos = i.getElement();
			_linkNode(from_pos->prev, from_pos->next);
			_insertList(from_pos, curr_node->prev, curr_node);
			_size += 1;
			x._size -= 1;

		}

		void splice (iterator position, list& x, iterator first, iterator last) {
			iterator tmp;
			while (first != last) {
				tmp = first++;
				splice(position, x, tmp);
			}
		}

		void remove (const value_type& val) {
		    for (iterator it = begin(); it != end(); ++it) {
		        if (*it == val)
		            erase(it);
		    }
		}

		template <class Predicate>
		void remove_if (Predicate pred) {
		    for (iterator it = begin(); it != end(); ++it) {
		        if (pred(*it))
		            erase(it);
		    }
		}

		void unique() {
			unique(_equal());
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred) {
            iterator it = begin();
            iterator next = ++begin();
            while (next != end()) {
                if (binary_pred(*it, *next))
                    next = erase(next);
                else {
                    ++it;
                    ++next;
                }
            }
        }

		void merge (list& x) {
			merge(x, _less());
		}

		template <class Compare>
		void merge (list& x, Compare comp) {
			iterator xBegin = x.begin();
			iterator mfirst = begin();
			sort();
			while (xBegin != x.end()) {
				while (mfirst != end() && !comp(*xBegin, *mfirst))
					mfirst++;
				splice(mfirst, x, xBegin++);
			}
		}

		void sort() {
			sort(_less());
		}

		template <class Compare>
		void sort (Compare comp) {
			iterator	first;
			iterator	second;
			iterator	itend = end();

			while (itend != ++begin()) {
				first = begin();
				second = ++begin();
				while (second != itend) {
					if (!comp(*first, *second)) {
						_List *firstNode = first.getElement();
						_List *secondNode = second.getElement();
						_List *changeBuffer = firstNode->prev;
						firstNode->prev = secondNode;
						firstNode->next = secondNode->next;
						firstNode->next->prev = firstNode;
						secondNode->prev = changeBuffer;
						secondNode->next = firstNode;
						secondNode->prev->next = secondNode;
						iterator tmp = first;
						first = second;
						second = tmp;
					}
					++first;
					++second;
				}
				itend = first;
			}
		}

		void reverse() {
			_List* currentNode = begin().getElement();
			_List* nextNode;
			_List* tmp;
			for (size_type i = 0; i <= _size; ++i) {
				nextNode = currentNode->next;

				tmp = currentNode->prev;
				currentNode->prev = currentNode->next;
				currentNode->next = tmp;

				currentNode = nextNode;
			}
		}
	};
	template <class P, class AllocSwap>
	void swap (ft::list<P,AllocSwap>& x, ft::list<P,AllocSwap>& y) {
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		typename ft::list<T, Alloc>::const_iterator lit;
		typename ft::list<T, Alloc>::const_iterator lite = lhs.end();
		typename ft::list<T, Alloc>::const_iterator rit = rhs.begin();
		typename ft::list<T, Alloc>::const_iterator rite = rhs.end();

		for (lit = lhs.begin(); lit != lite; ++lit) {
			if (rit == rite || *lit != *rit)
				return false;
			++rit;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return !(lhs == rhs); }

	template <class T, class Alloc>
	bool operator<  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) {
		if (lhs.size() < rhs.size()) {
			return true;
		}
		typename ft::list<T, Alloc>::const_iterator lit;
		typename ft::list<T, Alloc>::const_iterator lite = lhs.end();
		typename ft::list<T, Alloc>::const_iterator rit = rhs.begin();
		typename ft::list<T, Alloc>::const_iterator rite = rhs.end();

		for (lit = lhs.begin(); lit != lite; ++lit) {
			if (rit == rite)
				return false;
			if (*lit < *rit)
				return true;
			++rit;
		}
		return false;
	}

	template <class T, class Alloc>
	bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return !(rhs < lhs); }

	template <class T, class Alloc>
	bool operator>  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return rhs < lhs; }

	template <class T, class Alloc>
	bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return !(lhs < rhs); }
}