#pragma once

#include <iostream>
#include <list>

namespace ft {
	template <class T, class Container = std::list<T> >
	class queue: public std::list<T> {
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	public:

		//constructor
		explicit queue (const container_type& ctnr = container_type()): _size(0), _list(0) {}

		//destructor
		~queue() {}

		// methods
		bool empty() const { return (this->_size == 0); }

		size_type size() const { return this->_size; }

		value_type& front() { return this->_list.front(); }
		const value_type& front() const { return this->_list.front(); }

		value_type& back() { return this->_list.back(); }
		const value_type& back() const { return this->_list.back(); }

		void push (const value_type& val) { this->_list.push_back(val); }
		void pop() { this->_list.pop_front(); }

	private:
		container_type _list;
		size_t _size;

	};
};