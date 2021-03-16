#pragma once

#include <iostream>
#include "list.hpp"

namespace ft {
	template <class T, class Container = ft::list<T> >
	class queue: public ft::list<T> {
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	public:

		//constructor
		explicit queue (const container_type& ctnr = container_type()): _size(0), _list(ctnr) {}

		//destructor
		~queue() {}

		// methods
		bool empty() const { return _list.empty(); }

		size_type size() const { return _list.size(); }

		value_type& front() { return _list.front(); }
		const value_type& front() const { return _list.front(); }

		value_type& back() { return _list.back(); }
		const value_type& back() const { _list.back(); }

		void push (const value_type& val) { _list.push_back(val); }
		void pop() { this->_list.pop_front(); }

		container_type getQueue() const { return _list; }

	private:
		container_type _list;
		size_t _size;
	};

	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.getQueue() == rhs.getQueue());
	}
	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.getQueue() != rhs.getQueue());
	}
	template <class T, class Container>
	bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.getQueue() < rhs.getQueue());
	}
	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.getQueue() <= rhs.getQueue());
	}
	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.getQueue() > rhs.getQueue());
	}
	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.getQueue() >= rhs.getQueue());
	}
};