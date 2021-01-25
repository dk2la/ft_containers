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
		list*   _t_node;
		class list {
		public:
			value_type field; // поле данных
			list *next; // указатель на следующий элемент
			list *prev; // указатель на предыдущий элемент
		};
		class ring {
		public:
			value_type size;
			list        *current;
		};
	public:
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		//Constructors
		explicit list (const allocator_type& alloc = allocator_type());

		explicit list (size_type n, const value_type& val = value_type(),
		               const allocator_type& alloc = allocator_type());

		template <class InputIterator>
		list (InputIterator first, InputIterator last,
		      const allocator_type& alloc = allocator_type());

		list (const list& x);

		~list();

		list& operator= (const list& x);

		/* Iterators */
		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/* Capacity */
		bool empty() const;

		size_type size() const;

		size_type max_size() const;

		/* Element access */
		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		/* Modifiers */
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);

		void assign (size_type n, const value_type& val);

		void push_front (const value_type& val);

		void pop_front();

		void push_back (const value_type& val);

		void pop_back();

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
	};

}