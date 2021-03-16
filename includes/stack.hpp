#pragma once

#include <iostream>
#include "list.hpp"
namespace ft {
	template <class T, class Container = ft::list<T> >
	class stack: public ft::list<T> {
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	public:
		//constructor
		explicit stack (const container_type& ctnr = container_type()): _size(0), _list(ctnr) {}

		// destructor
		~stack() {}
		//methods
		bool empty() const { return _list.empty(); }
		size_type size() const { return _list.size(); }

		value_type& top() { return _list.back(); }
		const value_type& top() const {return _list.back(); }

		void push (const value_type& val) { _list.push_back(val); }

		void pop() { _list.pop_back(); }

		container_type getStack() const { return _list; }

	private:
		container_type _list;
		size_type _size;
	};
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.getStack() == rhs.getStack());
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.getStack() != rhs.getStack());
	}
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.getStack() < rhs.getStack());
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.getStack() <= rhs.getStack());
	}
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.getStack() > rhs.getStack());
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.getStack() >= rhs.getStack());
	}

};
