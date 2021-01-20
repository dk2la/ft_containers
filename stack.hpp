#pragma once

#include <iostream>
#include <list>

namespace ft {
	template <class T, class Container = std::list<T> >
	class stack: public std::list<T> {
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	public:
		//constructor
		explicit stack (const container_type& ctnr = container_type()): _size(0), _list(ctnr) {}

		// destructor
		~stack() {}
		//methods
		bool empty() const { return (this->_size == 0); }
		size_type size() const { return this->_size; }

		value_type& top() { return this->_list.back(); }
		const value_type& top() const {return this->_list.back(); }

		void push (const value_type& val) { this->_list.push_back(val); }

		void pop() { this->_list.pop_back(); }

	private:
		container_type _list;
		size_type _size;
	};
	template <class T, class Container>
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs == rhs; }
	template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs != rhs; }
	template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs < rhs; }
	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs <= rhs; }
	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs > rhs; }
	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs >= rhs; }

};
