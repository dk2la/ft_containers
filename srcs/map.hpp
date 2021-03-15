#include <iostream>

namespace ft {
	template<
			class Key,
			class T,
			class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T> >
	>
	class map {
	public:
		class 	iterator;
		class 	const_iterator;
		class 	reverse_iterator;
		class 	const_reverse_iterator;

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Allocator 									allocator_type;
		typedef value_type &								reference;
		typedef const value_type &							const_reference;
		typedef value_type *								pointer;
		typedef const value_type *							const_pointer;
		typedef size_t 										size_type;
		typedef ptrdiff_t 									difference_type;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
		public:
			key_compare comp;

			explicit value_compare(key_compare c) : comp(c) {};
		public:
			bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); };
		};

		template<bool B, class C = void>
		struct enable_if {};
		template <class C>
		struct enable_if <true, C> { typedef T type; };
	private:
		const static bool black = false;
		const static bool red = true;

		allocator_type _alloc;
		typedef struct 		_sNode {
			pointer			_content;
			_sNode*			_left;
			_sNode*			_right;
			_sNode*			_parent;
			bool			_color;
		}					_Node;

		size_type 		_size;
		key_compare 	_compare;
		_Node*			_rootNode;
		_Node*			_beginNode;
		_Node*			_endNode;

		typedef typename allocator_type::template rebind<_Node>::other allocator_rebind_type;
		allocator_rebind_type _allocator_rebind;

		_Node*						_createNode(bool color, _Node* parent, const value_type& val, size_type size) {
			_Node*	newNode = _allocator_rebind.allocate(1);
			newNode->_parent = parent;
			newNode->_left = nullptr;
			newNode->_right = nullptr;
			newNode->_color = color;
			newNode->_content = _alloc.allocate(1);
			_alloc.construct(newNode->_content, val);
			_size += size;
			return newNode;
		}

		void						_linkLeft(_Node* parent, _Node* left) {
			parent->_left = left;
			if (left)
				left->_parent = parent;
		}

		void						_linkRight(_Node* parent, _Node* right) {
			parent->_right = right;
			if (right)
				right->_parent = parent;
		}

		std::pair<iterator, bool>	_createRoot(bool color, _Node* parent, const value_type& val, size_type size) {
			_rootNode = _createNode(color, parent, val, size);
			_rootNode->_left = _beginNode;
			if (_beginNode)
				_beginNode->_parent = _rootNode;
			_rootNode->_right = _endNode;
			if (_endNode)
				_endNode->_parent = _rootNode;
			return std::make_pair(iterator(_rootNode), true);
		}

		bool						isRed(_Node* cur) {
			if (!cur)
				return black;
			return (cur->_color == red);
		}

		void						_insertLeft(_Node* insertNode, _Node* parent) {
			if (parent->_left == _beginNode)
				_linkLeft(insertNode, _beginNode);
			parent->_left = insertNode;
		}

		void						_insertRight(_Node* insertNode, _Node* parent) {
			if (parent->_right == _endNode)
				_linkRight(insertNode, _endNode);
			parent->_right = insertNode;
		}

		_Node*						_rotateLeft(_Node* cur) {
			_Node*	tmpNode = cur->_right;

			tmpNode->_parent = nullptr;
			if (cur->_parent) {
				if (cur->_parent->_left == cur)
					_linkLeft(cur->_parent, tmpNode);
				else
					_linkRight(cur->_parent, tmpNode);
			}
			else
				tmpNode->_parent = cur->_parent;
			_linkRight(cur, tmpNode->_left);
			_linkLeft(tmpNode, cur);
			if (cur == _rootNode)
				_rootNode = tmpNode;
			tmpNode->_color = cur->_color;
			cur->_color = red;
			return tmpNode;
		}

		_Node*					_rotateRight(_Node* cur) {
			_Node* tmpNode = cur->_left;

			tmpNode->_parent = nullptr;
			if (cur->_parent) {
				if (cur->_parent->_left == cur)
					_linkLeft(cur->_parent, tmpNode);
				else
					_linkRight(cur->_parent, tmpNode);
			}
			else
				tmpNode->_parent = cur->_parent;
			_linkLeft(cur, tmpNode->_right);
			_linkRight(tmpNode, cur);
			if (cur == _rootNode)
				_rootNode = tmpNode;
			tmpNode->_color = cur->_color;
			cur->_color = red;
			return tmpNode;
		}

		void					_inverseColor(_Node* cur) {
			if (cur && cur != _rootNode)
				cur->_color = !cur->_color;
			if (cur->_left && cur->_left != _beginNode) // если есть нода и она не является листом дерева, то перекрашиваем
				cur->_left->_color = !cur->_left->_color;
			if (cur->_right && cur->_right != _endNode)
				cur->_right->_color = !cur->_right->_color;
		}

		_Node*					_treeBalance(_Node*	cur) {
			if (isRed(cur->_right) && !isRed(cur->_left))
				cur = _rotateLeft(cur);
			if (isRed(cur->_left) && cur->_left && isRed(cur->_left->_left))
				cur = _rotateRight(cur);
			if (isRed(cur->_right) && isRed(cur->_left))
				_inverseColor(cur);
			return cur;
		}

		std::pair<iterator, bool>	_recursiveInsert(_Node* cur, const value_type& val) {
			int comp = _compare(val.first, cur->_content->first) | _compare(cur->_content->first, val.first);

			if (comp == 0)
				return std::make_pair(iterator(cur), false);
			else if (comp == 1) {
				comp = _compare(val.first, cur->_content->first);
				if (comp == 1 && cur->_left && cur->_left != _beginNode)
					return _recursiveInsert(cur->_left, val);
				else if (comp == 0 && cur->_right && cur->_right != _endNode)
					return _recursiveInsert(cur->_right, val);
			}

			_Node* newNode = _createNode(red, cur, val, 1);
			(comp == 1) ? _insertLeft(newNode, cur) : _insertRight(newNode, cur);
			_treeBalance(cur);
			return std::make_pair(iterator(newNode), true);
		}

		iterator				_recursivefind(_Node* cur, const key_type& key) {
			if (!cur)
				return end();
			int comp = _compare(key, cur->_content->first) | _compare(cur->_content->first, key);

			if (comp == 0)
				return iterator(cur);
			else if (comp == 1) {
				comp = _compare(key, cur->_content->first);
				if (comp == 1 && cur->_left && cur->_left != _beginNode)
					return _recursivefind(cur->_left, key);
				else if (comp == 0 && cur->_right && cur->_right != _endNode)
					return _recursivefind(cur->_right, key);
			}
			return end();
		}

		const_iterator				_recursivefindconst(_Node* cur, const key_type& key) const {
			if (!cur)
				return end();
			int comp = _compare(key, cur->_content->first) | _compare(cur->_content->first, key);

			if (comp == 0)
				return iterator(cur);
			else if (comp == 1) {
				comp = _compare(key, cur->_content->first);
				if (comp == 1 && cur->_left && cur->_left != _beginNode)
					return _recursivefindconst(cur->_left, key);
				else if (comp == 0 && cur->_right && cur->_right != _endNode)
					return _recursivefindconst(cur->_right, key);
			}
			return end();
		}

		size_type 				_recursivecount(_Node* cur, const key_type& key) const {
			int comp = _compare(key, cur->_content->first) | _compare(cur->_content->first, key);

			if (comp == 0)
				return 1;
			else if (comp == 1) {
				comp = _compare(key, cur->_content->first);
				if (comp == 1 && cur->_left && cur->_left != _beginNode)
					return _recursivecount(cur->_left, key);
				else if (comp == 0 && cur->_right && cur->_right != _endNode)
					return _recursivecount(cur->_right, key);
			}
			return 0;
		}

		_Node*					_moveRedLeft(_Node* cur) {
			_inverseColor(cur);
			if (cur->_right && isRed(cur->_right->_left)) {
				cur->_right = _rotateRight(cur->_right);
				cur = _rotateLeft(cur);
				_inverseColor(cur);
			}
			return cur;
		}

		_Node*					_moveRedRight(_Node* cur) {
			_inverseColor(cur);
			if (cur->_left && isRed(cur->_left->_left)) {
				cur = _rotateRight(cur);
				_inverseColor(cur);
			}
			return cur;
		}

		_Node*					_findLowLeft(_Node* cur) {
			if (cur->_left)
				return _findLowLeft(cur->_left);
			return cur;
		}

		void					_destroyNode(_Node* cur) {
			_alloc.destroy(cur->_content);
			_alloc.deallocate(cur->_content, 1);
			_allocator_rebind.deallocate(cur, 1);
			--_size;
		}

		_Node*					_eraseNode(_Node* cur, const key_type& k) {
			int comp = _compare(k, cur->_content->first) | _compare(cur->_content->first, k);

			if (comp == 1 && _compare(k, cur->_content->first) == 1) {
				if (!isRed(cur->_left) && !isRed(cur->_left->_left)) // проверяем на 2 красных узла друг за другом
					cur = _moveRedLeft(cur);
				_linkLeft(cur, _eraseNode(cur->_left, k));
			}
			else {
				if (isRed(cur->_left)) {
					cur = _rotateRight(cur);
					_linkRight(cur, _eraseNode(cur->_right, k));
					return _treeBalance(cur);
				}
				if (comp == 0 && _compare(cur->_content->first, k) == 0 &&
					(cur->_right == _endNode || cur->_right == nullptr)) {
					_Node*	tmp;
					if (!cur->_left && cur->_right == _endNode)
						tmp = cur->_right;
					else
						tmp = cur->_left;
					_destroyNode(cur);
					return tmp;
				}
				if (!isRed(cur->_right) && cur->_right && !isRed(cur->_right->_left))
					cur = _moveRedRight(cur);
				if (_compare(cur->_content->first, k) == 0) {
					_Node*	min;

					min = _findLowLeft(cur->_right);
					if (cur == _rootNode)
						_rootNode = min;
					if (min->_parent != cur) {
						_linkLeft(min->_parent, min->_right); // min->_right == nullptr;
						_linkRight(min, cur->_right); // cur->_ right
					}
					if (cur->_left == _beginNode) {
						cur->_left->_parent = min;
						min->_left = _beginNode;
					} else
						_linkLeft(min, cur->_left);
					min->_parent = nullptr;
					if (cur->_parent) {
						if (cur->_parent->_left == cur)
							_linkLeft(cur->_parent, min);
						else
							_linkRight(cur->_parent, min);
					}
					_destroyNode(cur);
					cur = min;
				} else
					_linkRight(cur, _eraseNode(cur->_right, k));
			}
			return _treeBalance(cur);
		}
	public:
		/* iterator */
		class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_Node* _it;
		public:
			explicit iterator(_Node* it = nullptr): _it(it) {};
			~iterator() {};
			iterator & operator=(const iterator &it) { this->_it = it._it; return *this; };
			iterator(const iterator &it) { *this = it; };
			iterator & operator++() {
				_it = nextNode(_it);
				return *this;
			};
			iterator operator++(int) {
				iterator tmp(_it);
				operator++();
				return tmp;
			};
			iterator & operator--() { _it = prevNode(_it); return *this; };
			iterator operator--(int) {
				iterator tmp(_it);
				operator--();
				return tmp;
			};
			bool operator==(const iterator &it) const { return this->_it == it._it; };
			bool operator!=(const iterator &it) const { return this->_it != it._it; };

			bool operator==(const const_iterator &it) const { return this->_it == it.getNode(); };
			bool operator!=(const const_iterator &it) const { return this->_it != it.getNode(); };
			reference operator*() const { return *(this->_it->_content); }
			pointer operator->() const { return this->_it->_content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->_left)
					return findLowNode(currentNode->_left);
				return currentNode;
			}

			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->_right)
					return findHighNode(currentNode->_right);
				return currentNode;
			}

			_Node *nextNode(_Node* currentNode) {
				if (currentNode->_right)
					return findLowNode(currentNode->_right);
				else if (currentNode->_parent && currentNode->_parent->_left == currentNode)
					return currentNode->_parent;
				else if (currentNode->_parent->_right == currentNode)
					currentNode = currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_right == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_right;
				return tmp->_parent;
			}

			_Node *prevNode(_Node* currentNode) {
				if (currentNode->_left)
					return findHighNode(currentNode->_left);
				else if (currentNode->_parent && currentNode->_parent->_right == currentNode)
					return currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_left == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_left;
				return tmp->_parent;
			}
		};

		/* const_iterator */
		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type const> {
		private:
			_Node * _it;
		public:
			explicit const_iterator(_Node* it = nullptr) : _it(it) {};
			const_iterator(const const_iterator &it) { *this = it; };
			const_iterator(const iterator &it) { *this = it; };
			~const_iterator() {};
			const_iterator& operator=(const const_iterator &it)  { this->_it = it._it; return *this; };
			const_iterator& operator=(const iterator &it)  { this->_it = it.getNode(); return *this; };
			const_iterator & operator++() { _it = nextNode(_it); return *this; };
			const_iterator operator++(int) {
				const_iterator tmp(_it);
				operator++();
				return tmp;
			};
			const_iterator & operator--() { _it = prevNode(_it); return *this; };
			const_iterator operator--(int) {
				const_iterator tmp(_it);
				operator--();
				return tmp;
			};
			bool operator==(const const_iterator &it) const { return this->_it == it._it; };
			bool operator!=(const const_iterator &it) const { return this->_it != it._it; };
			bool operator==(const iterator &it) const { return this->_it == it.getNode(); };
			bool operator!=(const iterator &it) const { return this->_it != it.getNode(); };
			const_reference operator*() const { return *(this->_it->_content); };
			const_pointer operator->() const { return this->_it->_content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->_left)
					return findLowNode(currentNode->_left);
				return currentNode;
			}
			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->_right)
					return findHighNode(currentNode->_right);
				return currentNode;
			}
			_Node *nextNode(_Node* currentNode) {
				if (currentNode->_right)
					return findLowNode(currentNode->_right);
				else if (currentNode->_parent && currentNode->_parent->_left == currentNode)
					return currentNode->_parent;
				else if (currentNode->_parent->_right == currentNode)
					currentNode = currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_right == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_right;
				return tmp->_parent;
			}
			_Node *prevNode(_Node* currentNode) {
				if (currentNode->_left)
					return findHighNode(currentNode->_left);
				else if (currentNode->_parent && currentNode->_parent->_right == currentNode)
					return currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_left == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_left;
				return tmp->_parent;
			}
		};

		/* reverse_iterator */
		class reverse_iterator : public std::reverse_iterator<iterator> {
		private:
			_Node* _it;
		public:
			explicit reverse_iterator(_Node* it = nullptr): _it(it) {};
			~reverse_iterator() {};
			reverse_iterator(const reverse_iterator &it) { *this = it; };
			reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it._it; return *this; };
			reverse_iterator & operator++() { _it = prevNode(_it); return *this; };
			reverse_iterator operator++(int) {
				reverse_iterator tmp(_it);
				operator++();
				return tmp;
			};
			reverse_iterator & operator--() { _it = nextNode(_it); return *this; };
			reverse_iterator operator--(int) {
				reverse_iterator tmp(_it);
				operator--();
				return tmp;
			};
			bool operator==(const reverse_iterator &it) const { return this->_it == it._it; };
			bool operator!=(const reverse_iterator &it) const { return this->_it != it._it; };
			bool operator==(const const_reverse_iterator &it) const { return this->_it == it.getNode(); };
			bool operator!=(const const_reverse_iterator &it) const { return this->_it != it.getNode(); };
			value_type & operator*() const { return *(this->_it->_content); };
			value_type * operator->() const { return this->_it->_content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->_left)
					return findLowNode(currentNode->_left);
				return currentNode;
			}
			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->_right)
					return findHighNode(currentNode->_right);
				return currentNode;
			}
			_Node *nextNode(_Node* currentNode) {
				if (currentNode->_right)
					return findLowNode(currentNode->_right);
				else if (currentNode->_parent && currentNode->_parent->_left == currentNode)
					return currentNode->_parent;
				else if (currentNode->_parent->_right == currentNode)
					currentNode = currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_right == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_right;
				return tmp->_parent;
			}
			_Node *prevNode(_Node* currentNode) {
				if (currentNode->_left)
					return findHighNode(currentNode->_left);
				else if (currentNode->_parent && currentNode->_parent->_right == currentNode)
					return currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_left == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_left;
				return tmp->_parent;
			}
		};

		/* const_reverse_iterator */
		class const_reverse_iterator : public std::reverse_iterator<iterator> {
		private:
			_Node* _it;
		public:
			explicit const_reverse_iterator(_Node* it = nullptr): _it(it) {};
			~const_reverse_iterator() {};
			const_reverse_iterator & operator=(const const_reverse_iterator &it) { this->_it = it._it; return *this; };
			const_reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it.getNode(); return *this; };
			const_reverse_iterator(const const_reverse_iterator &it) { *this = it; };
			const_reverse_iterator(const reverse_iterator &it) { *this = it; };
			const_reverse_iterator & operator++() { _it = prevNode(_it); return *this; };
			const_reverse_iterator operator++(int) {
				const_reverse_iterator tmp(_it);
				operator++();
				return tmp;
			};
			const_reverse_iterator & operator--() { _it = nextNode(_it); return *this; };
			const_reverse_iterator operator--(int) {
				const_reverse_iterator tmp(_it);
				operator--();
				return tmp;
			};
			bool operator==(const const_reverse_iterator &it) const { return this->_it == it._it; };
			bool operator!=(const const_reverse_iterator &it) const { return this->_it != it._it; };
			bool operator==(const reverse_iterator &it) const { return this->_it == it.getNode(); };
			bool operator!=(const reverse_iterator &it) const { return this->_it != it.getNode(); };
			reference operator*() const { return *(this->_it->_content); }
			pointer operator->() const { return this->it->_content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->_left)
					return findLowNode(currentNode->_left);
				return currentNode;
			}
			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->_right)
					return findHighNode(currentNode->_right);
				return currentNode;
			}
			_Node *nextNode(_Node* currentNode) {
				if (currentNode->_right)
					return findLowNode(currentNode->_right);
				else if (currentNode->_parent && currentNode->_parent->_left == currentNode)
					return currentNode->_parent;
				else if (currentNode->_parent->_right == currentNode)
					currentNode = currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_right == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_right;
				return tmp->_parent;
			}
			_Node *prevNode(_Node* currentNode) {
				if (currentNode->_left)
					return findHighNode(currentNode->_left);
				else if (currentNode->_parent && currentNode->_parent->_right == currentNode)
					return currentNode->_parent;
				_Node *tmp = currentNode;
				while (tmp->_parent->_left == tmp)
					if ((tmp = tmp->_parent) == nullptr)
						return currentNode->_left;
				return tmp->_parent;
			}
		};

		/* Constructor */
		/* empty */
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _compare(comp), _rootNode(nullptr) {
			_beginNode = _allocator_rebind.allocate(1);
			_beginNode->_content = nullptr;
			_beginNode->_left = nullptr;
			_beginNode->_right = nullptr;
			_beginNode->_parent = nullptr;
			_beginNode->_color = black;

			_endNode = _allocator_rebind.allocate(1);
			_endNode->_content = nullptr;
			_endNode->_left = nullptr;
			_endNode->_right = nullptr;
			_endNode->_parent = nullptr;
			_endNode->_color = black;
		}
		/* range */
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type(),
			 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0): _alloc(alloc), _size(0), _compare(comp), _rootNode(nullptr) {
				_beginNode = _allocator_rebind.allocate(1);
				_beginNode->_content = nullptr;
				_beginNode->_left = nullptr;
				_beginNode->_right = nullptr;
				_beginNode->_parent = nullptr;
				_beginNode->_color = black;

				_endNode = _allocator_rebind.allocate(1);
				_endNode->_content = nullptr;
				_endNode->_left = nullptr;
				_endNode->_right = nullptr;
				_endNode->_parent = nullptr;
				_endNode->_color = black;

				insert(first, last);
			 }

		/* copy */
		map (const map& x): _alloc(x._alloc), _size(0), _allocator_rebind(x._allocator_rebind) {
			_beginNode = _allocator_rebind.allocate(1);
			_beginNode->_content = nullptr;
			_beginNode->_left = nullptr;
			_beginNode->_right = nullptr;
			_beginNode->_parent = nullptr;
			_beginNode->_color = black;

			_endNode = _allocator_rebind.allocate(1);
			_endNode->_content = nullptr;
			_endNode->_left = nullptr;
			_endNode->_right = nullptr;
			_endNode->_parent = nullptr;
			_endNode->_color = black;
			*this = x;
		}

		/* Destructor */
		~map() {
			clear();
			_allocator_rebind.deallocate(_beginNode, 1);
			_allocator_rebind.deallocate(_endNode, 1);
		}

		/* Operators */
		 /* copy */
		 map& operator= (const map& x) {
		 	clear();
		 	insert(x.begin(), x.end());
			return *this;
		}

		/* ITERATORS */
		iterator		begin() { return (_size != 0) ? iterator(_beginNode->_parent) : iterator(_endNode); };
		const_iterator 	begin() const { return (_size != 0) ? const_iterator(_beginNode->_parent) : const_iterator(_endNode); };
		iterator		end() { return iterator(_endNode); };
		const_iterator	end() const { return const_iterator(_endNode); };

		/* Reverse Iterators */
		reverse_iterator 		rbegin() { return (_size != 0) ? reverse_iterator(_endNode->_parent) : reverse_iterator(_beginNode); };
		const_reverse_iterator	rbegin() const { return (_size != 0) ? const_reverse_iterator(_endNode->_parent) : const_reverse_iterator(_beginNode); };
		reverse_iterator 		rend() { return reverse_iterator(_beginNode); };
		const_reverse_iterator	rend() const { return const_reverse_iterator(_beginNode); };

		/* CAPACITY */
		bool empty() const {
			return (_size == 0);
		}

		size_type size() const {
			return _size;
		}

		size_type max_size() const {
			if (sizeof(value_type) == 1)
				return ((size_t)(-1) / sizeof(value_type) / 2);
			else
				return ((size_t)(-1) / sizeof(value_type));
		}

		/* Element Access */
		mapped_type& operator[] (const key_type& k) {
			iterator it = find(k);
			if (it == end())
				return insert(std::make_pair(k, mapped_type())).first->second;
			else
				return it->second;
		}

		/* Mpdifiers */
		/* single element */
		std::pair<iterator,bool> insert (const value_type& val) {
			if (_size == 0)
				return _createRoot(black, nullptr, val, 1);
			return _recursiveInsert(_rootNode, val);
		}

		iterator insert (iterator position, const_reference val) {
			static_cast<void>(position);
			return insert(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
					 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			for (; first != last; ++first)
				insert(*first);
		}

		void erase (iterator position) {
			erase(position->first);
		}

		size_type erase(const key_type& k) {
			if (_size == 0 || find(k) == end())
				return 0;
			_eraseNode(_rootNode, k);
			return 1;
		}

		void erase (iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		void swap (map& x) {
			_Node* tmpRootNode = _rootNode;
			_rootNode = x._rootNode;
			x._rootNode = tmpRootNode;

			_Node*	tmpBeginNode = _beginNode;
			_beginNode = x._beginNode;
			x._beginNode = tmpBeginNode;

			_Node*	tmpEndNode = _endNode;
			_endNode = x._endNode;
			x._endNode = tmpEndNode;

			size_type tmpSize = _size;
			_size = x._size;
			x._size = tmpSize;
		}

		void clear() {
			while (size() != 0)
				erase(begin());
		}

		/* Observers */
		key_compare key_comp() const { return _compare; }
		value_compare value_comp() const { return value_compare(_compare); }

		/* Operations */
		iterator find (const key_type& k) {
			return _recursivefind(_rootNode, k);
		}
		const_iterator find (const key_type& k) const {
			return _recursivefindconst(_rootNode, k);
		}

		size_type count (const key_type& k) const {
			return _recursivecount(_rootNode, k);
		}

		iterator lower_bound (const key_type& k) {
			iterator it = begin();
			while (it != end() && _compare(it->first, k))
				++it;
			return it;
		}
		const_iterator lower_bound (const key_type& k) const {
			iterator it = begin();
			while (it != end() && _compare(it->first, k))
				++it;
			return it;
		}

		iterator upper_bound (const key_type& k) {
			iterator it = lower_bound(k);
			if (it != end() && !_compare(k, it->first) && !_compare(it->first, k))
				return (++it);
			else
				return (it);
		}
		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = lower_bound(k);
			if (it != end() && !_compare(k, it->first) && !_compare(it->first, k))
				return (++it);
			else
				return (it);
		}

		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		}

		std::pair<iterator,iterator>             equal_range (const key_type& k) {
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		}
	};
	template < class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{

		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg1 = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg2 = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end1 = lhs.end();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end2 = rhs.end();

		while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
		{
			beg1++;
			beg2++;
		}

		if (beg1 == end1 && beg2 == end2)
			return (true);
		return (false);
	}

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	bool operator!=(const ft::map<Key, T, Compare, Allocator > &lhs, const ft::map<Key, T, Compare, Allocator > &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	bool operator<(const ft::map<Key, T, Compare, Allocator > &lhs, const ft::map<Key, T, Compare, Allocator > &rhs)
	{

		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() > rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Allocator >::const_iterator beg1 = lhs.begin();
		typename ft::map<Key, T, Compare, Allocator >::const_iterator beg2 = rhs.begin();
		typename ft::map<Key, T, Compare, Allocator >::const_iterator end1 = lhs.end();
		typename ft::map<Key, T, Compare, Allocator >::const_iterator end2 = rhs.end();

		while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
		{
			beg1++;
			beg2++;
		}

		if ((beg1 == end1 && beg2 == end2) || beg2 == end2 || *beg1 >= *beg2)
			return (false);
		return (true);
	}

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	bool operator<=(const ft::map<Key, T, Compare, Allocator > &lhs, const ft::map<Key, T, Compare, Allocator > &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	bool operator>(const ft::map<Key, T, Compare, Allocator > &lhs, const ft::map<Key, T, Compare, Allocator > &rhs)
	{

		if (lhs.size() > rhs.size())
			return (true);
		if (lhs.size() < rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Allocator >::const_iterator beg1 = lhs.begin();
		typename ft::map<Key, T, Compare, Allocator >::const_iterator beg2 = rhs.begin();
		typename ft::map<Key, T, Compare, Allocator >::const_iterator end1 = lhs.end();
		typename ft::map<Key, T, Compare, Allocator >::const_iterator end2 = rhs.end();

		while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
		{
			beg1++;
			beg2++;
		}
		if ((beg1 == end1 && beg2 == end2) || beg1 == end1 || *beg1 <= *beg2)
			return (false);
		return (true);
	}

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	bool operator>=(const ft::map<Key, T, Compare, Allocator > &lhs, const ft::map<Key, T, Compare, Allocator > &rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	void swap(ft::map<Key, T, Compare, Allocator > &lhs, ft::map<Key, T, Compare, Allocator > &rhs)
	{
		lhs.swap(rhs);
	}
}