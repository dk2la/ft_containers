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

		void    _createList(void) {
			this->_end = this->_allocator_rebind.allocate(1);
			this->_end->content = this->_alloc.allocate(1);
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_size = 0;
		}

		_List*   _createNode(const value_type& val) {
			_List* tmp = this->_allocator_rebind.allocate(1);
			tmp->content = this->_alloc.allocate(1);
			this->_alloc.construct(tmp->content, val);
			this->_size++;
			return tmp;
		}

		void   _insertList(_List* current, _List* prevNode, _List* nextNode) {
			this->_linkNode(prevNode, current);
			this->_linkNode(current, nextNode);
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
		explicit list (const allocator_type& alloc = allocator_type()): _size(0), _alloc(alloc), _end(0) {
			this->_createList();
		}

		explicit list (size_type n, const value_type& val = value_type(),
		               const allocator_type& alloc = allocator_type()) {
			this->_createList();
		    for (; n != 0; --n)
				push_back(val);
		}

		template <class InputIterator>
		list (InputIterator first, InputIterator last,
		      const allocator_type& alloc = allocator_type());

		list (const list& x): _alloc(x._alloc), _end(0) {
		    this->_createList();
		    *this = x;
		}

		~list() {
		    clear();
			this->_size = 0;
            this->_alloc.deallocate(this->_end->content, 1);
            this->_allocator_rebind.deallocate(this->_end, 1);
		}

		list& operator= (const list& x) {
		    this->_size = x._size;
		    this->_alloc = x._alloc;
		    this->_end = x._end;
		    this->_allocator_rebind = x._allocator_rebind;
		    return *this;
		}

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
		bool empty() const { return (this->_size == 0); }

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

		reference back() { return *(this->_end->prev->content); }
		const_reference back() const { return *(this->_end->prev->content); }

		/* Modifiers */
//		template <class InputIterator>
//		void assign (InputIterator first, InputIterator last) {
//			if (!this->empty)
//				this->clear();
//			for (;first != last; ++first)
//				this->push_back(*first);
//		}

		void assign (size_type n, const value_type& val) {
			if (!this->empty)
				this->clear();
			for (size_type i = 0; i < n; ++i)
				this->push_back(val);
		}

		void push_front (const value_type& val) {
			_List* current = this->_createList(val);
			this->_insertList(current, this->_end, this->_end->next);
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
			_List* current = this->_createNode(val);
			this->_insertList(current, this->_end->prev, this->_end);
		}

		void pop_back() {
			_List* tmp = this->_end->prev;
			this->_linkNode(tmp->prev, tmp->next);
			this->_alloc.destroy(tmp->content);
			this->_alloc.deallocate(tmp->content, 1);
			this->_allocator_rebind.deallocate(tmp, 1);
			this->_size--;
		}

		iterator insert (iterator position, const value_type& val) {
			_List* current = this->_createNode(val);
			_List* it_pos = position.getElement();
			this->_linkNode(current, it_pos->prev, it_pos);
			return iterator(current);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			for (; n != 0; n--)
				insert(position, val);
		}

//		template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last) {
//			for (; first != last; ++first)
//				insert(position, *first);
//		}

		iterator erase (iterator position) {
			_List* it_pos = position.getElement();
			_List* save_node = it_pos->next;
			this->_linkNode(it_pos->prev, it_pos->next);
			this->_alloc.destroy(it_pos->content);
			this->_alloc.deallocate(it_pos->content, 1);
			this->_allocator_rebind.deallocate(it_pos, 1);
			this->_size--;
			return iterator(save_node);
		}
		iterator erase (iterator first, iterator last) {
			for (;first != last;)
				erase(++first);
			return last;
		}

		void swap (list& x) {
            _List* tmp = this->_end;
            this->_end = x._end;
            x._end = tmp;
            size_type size = this->_size;
            this->_size = x._size;
            x._size = size;
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
			for (; this->_size;)
				pop_back();
		}

		/* Operations */
		void splice (iterator position, list& x) {
//		    _List* tmp =
		}

		void splice (iterator position, list& x, iterator i);

		void splice (iterator position, list& x, iterator first, iterator last);

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
//		    this->sort();
		    iterator it = begin();
		    iterator next = ++begin();
		    while (next != end()) {
		        if (*it == *next)
		            next = erase(next);
		        else {
		            ++it;
		            ++next;
		        }
		    }
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred) {
            //		    this->sort();
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
		    iterator itx_begin = this->begin();
		    iterator itx_end = this->end();
		    iterator it_begin = this->begin();
		    iterator it_end = this->end();
		    for (; itx_begin != itx_end; ++itx_begin) {
		        if (it_begin != it_end && *itx_begin != *it_begin)
		            ++it_begin;
		        splice(it_begin, x, itx_begin);
		    }
		}

		template <class Compare>
		void merge (list& x, Compare comp) {
            iterator itx_begin = this->begin();
            iterator itx_end = this->end();
            iterator it_begin = this->begin();
            iterator it_end = this->end();
            for (; itx_begin != itx_end; ++itx_begin) {
                while (it_begin != it_end && !comp(*itx_begin, *it_begin))
                    ++it_begin;
                splice(it_begin, x, itx_begin);
            }
		}

		void sort() {
            _List* current = this->_end->next;
            _List* next_elem = current->next;
            _List* tmp;
            bool sort = 1;
            while (sort) {
                sort = 0;
                next_elem = current->next;
                while (next_elem != this->_end) {
                    if ()
                }
                current = current->next;
            }
		}

		template <class Compare>
		void sort (Compare comp) {
		}

		void reverse() {
            _List* current = this->_end->next;
            _List* tmp = current->next;
            current->next = current->prev;
            current->prev = tmp;
            if (current == this->_end)
                return ;
            reverse(current->prev);
		}

		class iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
			explicit iterator(_List* it = nullptr): _it(it) {}
			iterator(const iterator& it) { *this = it; }
			iterator&   operator=(const iterator& it) {
				this->_it = it._it;
				return *this;
			}
			~iterator() {}

			iterator& operator++() { this->_it = this->_it->next; return *this; }
			iterator& operator--() { this->_it = this->_it->prev; return *this; }

			iterator operator++(int) {
				iterator tmp(*this);
				this->operator++();
				return tmp;
			}
			iterator operator--(int) {
				iterator tmp(*this);
				this->operator--();
				return tmp;
			}

			bool        operator==(const iterator& it) { return (this->_it->content == it.getElement()->content); }
			bool        operator!=(const iterator& it) { return (this->_it->content != it.getElement()->content); }

			T&   operator*() { return *(this->_it->content); }
			T*   operator->() {return this->_it->content; }
			_List* getElement() const { return this->_it; }
		private:
			_List*  _it;
		};

		class const_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		public:
            explicit const_iterator(_List* it = nullptr): _it(it) {}
            const_iterator(const const_iterator& it) { *this = it; }
            const_iterator(const iterator& it) { *this = it; }
            const_iterator&   operator=(const iterator& it) {
                this->_it = it._it;
                return *this;
            }
            const_iterator&   operator=(const const_iterator& it) {
                this->_it = it._it;
                return *this;
            }
            ~const_iterator() {}

            const_iterator& operator++() { this->_it = this->_it->next; return *this; }
            const_iterator& operator--() { this->_it = this->_it->prev; return *this; }

            const_iterator operator++(int) {
                iterator tmp(*this);
                this->operator++();
                return tmp;
            }
            const_iterator operator--(int) {
                iterator tmp(*this);
                this->operator--();
                return tmp;
            }

            bool        operator==(const const_iterator& it) { return (this->_it->content == it.getElement()->content); }
            bool        operator!=(const const_iterator& it) { return (this->_it->content != it.getElement()->content); }

            T&   operator*() { return *(this->_it->content); }
            T*   operator->() {return this->_it->content; }
            _List* getElement() const { return this->_it; }
        private:
            _List*  _it;
		};

		class reverse_iterator: public std::iterator<std::random_access_iterator_tag, T>{
        public:
            explicit reverse_iterator(_List* it = nullptr): _it(it) {}
            reverse_iterator(const reverse_iterator& it) { *this = it; }
            reverse_iterator&   operator=(const reverse_iterator& it) {
                this->_it = it._it;
                return *this;
            }
            ~reverse_iterator() {}

            reverse_iterator& operator++() { this->_it = this->_it->next; return *this; }
            reverse_iterator& operator--() { this->_it = this->_it->prev; return *this; }

            reverse_iterator operator++(int) {
                reverse_iterator tmp(*this);
                this->operator++();
                return tmp;
            }
            reverse_iterator operator--(int) {
                reverse_iterator tmp(*this);
                this->operator--();
                return tmp;
            }

            bool        operator==(const reverse_iterator& it) { return (this->_it->content == it.getElement()->content); }
            bool        operator!=(const reverse_iterator& it) { return (this->_it->content != it.getElement()->content); }

            T&   operator*() { return *(this->_it->content); }
            T*   operator->() {return this->_it->content; }
            _List* getElement() const { return this->_it; }
        private:
            _List*  _it;
		};

		class const_reverse_iterator: public std::iterator<std::random_access_iterator_tag, T> {
        public:
            explicit const_reverse_iterator(_List* it = nullptr): _it(it) {}
            const_reverse_iterator(const const_reverse_iterator& it) { *this = it; }
            const_reverse_iterator(const reverse_iterator& it) { *this = it; }
            const_reverse_iterator&   operator=(const reverse_iterator& it) {
                this->_it = it._it;
                return *this;
            }
            const_reverse_iterator&   operator=(const const_reverse_iterator& it) {
                this->_it = it._it;
                return *this;
            }
            ~const_reverse_iterator() {}

            const_reverse_iterator& operator++() { this->_it = this->_it->next; return *this; }
            const_reverse_iterator& operator--() { this->_it = this->_it->prev; return *this; }

            const_reverse_iterator operator++(int) {
                const_reverse_iterator tmp(*this);
                this->operator++();
                return tmp;
            }
            const_reverse_iterator operator--(int) {
                const_reverse_iterator tmp(*this);
                this->operator--();
                return tmp;
            }

            bool        operator==(const const_reverse_iterator& it) { return (this->_it->content == it.getElement()->content); }
            bool        operator!=(const const_reverse_iterator& it) { return (this->_it->content != it.getElement()->content); }

            T&   operator*() { return *(this->_it->content); }
            T*   operator->() {return this->_it->content; }
            _List* getElement() const { return this->_it; }
        private:
            _List*  _it;
		};
	};

}