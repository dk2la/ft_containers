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
		typedef struct Node {
			pointer		content;
			struct Node*	left;
			struct Node* right;
			struct Node*	parent;
			bool		color;
		}				_Node;

		size_type 		_size;
		key_compare 	_compare;
		_Node*			_rootNode;
		_Node*			_beginNode;
		_Node*			_endNode;

		typedef typename allocator_type::template rebind<_Node>::other allocator_rebind_type;
		allocator_rebind_type _allocator_rebind;

		void	_createBeginEndNode() {
			_beginNode = _allocator_rebind.allocate(1);
			_beginNode->content = _alloc.allocate(1);
			_beginNode->left = nullptr;
			_beginNode->right = nullptr;

			_beginNode = _allocator_rebind.allocate(1);
			_beginNode->content = _alloc.allocate(1);
			_beginNode->left = nullptr;
			_beginNode->right = nullptr;
			std::cout << "HERE" << std::endl;
		}

		_Node*	_createNode(bool color, const_reference val, _Node* parent, size_type size) {
			_Node*	tmpNode = _allocator_rebind.allocate(1);
			tmpNode->content = _alloc.allocate(1);
			_alloc.construct(tmpNode->content, val);
			tmpNode->left = nullptr;
			tmpNode->right = nullptr;
			tmpNode->parent = parent;
			tmpNode->color = color;
			_size += size;
			return tmpNode;
		}

		void _insertRootNode(bool color, const_reference val, _Node* parent, size_type size) {
			_rootNode = _createNode(color, val, parent, size);
			_rootNode->left = _beginNode;
			if (_beginNode)
				_beginNode->parent = _rootNode;
			_rootNode->right = _endNode;
			if (_endNode)
				_endNode->parent = _rootNode;
		}

		std::pair<iterator, bool> _otherInsertCases(_Node* currentNode, const_reference val) {
			int comp = ((_compare(val.first, currentNode->content->first)) | (_compare(currentNode->content->first, val.first))); // 0 если равны, 1 если меньше или больше

			if (comp == 0)
				return std::make_pair(iterator(currentNode), false); // Не добавляем одинаковые значения, возвращаем false, как флаг недобавленной node
			else if (comp == 1) {
				if ((comp = _compare(val.first, currentNode->content->first)) == 1 && currentNode->left) //TODO может быть понадобится проверка на _beginNode rootNode != _beginNode
					return _otherInsertCases(currentNode, val);
				else if ((comp = _compare(val.first, currentNode->content->first)) == 0 && currentNode->right) //TODO может быть понадобится проверка на _endNode rootNode != _endNode
					return _otherInsertCases(currentNode, val);

			}
			_Node* tmpNode = _createNode(red, val, currentNode, 1); // Создаем newNode, все новые ноды создаются с красным цветом
			(comp = _compare(val.first, currentNode->content->first) == 1) ? _insertLeftNode(tmpNode, currentNode) : _insertRightNode(tmpNode, currentNode); // В зависимости от значения раскидываем node
			_balance(currentNode); // балансируем дерево
			return std::make_pair(iterator(tmpNode), true);

		}

		void	_insertLeftNode(_Node* leftNode, _Node* parentNode) {
			if (parentNode->left == _beginNode) {
				leftNode->left = _beginNode;
				if (_beginNode)
					_beginNode->parent = leftNode;
			}
			parentNode->left = leftNode; // LinkLeft
			if (leftNode)
				leftNode->parent = parentNode;
		}

		void	_insertRightNode(_Node* rightNode, _Node* parentNode) {
			if (parentNode->right == _beginNode) {
				rightNode->left = _beginNode;
				if (_beginNode)
					_beginNode->parent = rightNode;
			}
			parentNode->right = rightNode; // LinkRight
			if (rightNode)
				rightNode->parent = parentNode;
		}

		_Node*		_rotateLeft(_Node* node) { // Поднимаем левую находящуюся снизу ноду на узел выше
			_Node*	rightTmp = node->right;
			node->right = rightTmp->left;
			rightTmp->left = node;
			rightTmp->color = rightTmp->left->color;
			rightTmp->left->color = red;
			return rightTmp;
		}

		_Node*		_rotateRight(_Node* node) { // Поднимаем правую находящуюся снизу ноду на узел выше
			_Node*	leftTmp = node->left;
			node->left = leftTmp->right;
			leftTmp->right = node;
			leftTmp->color = leftTmp->right->color;
			leftTmp->right->color = red;
			return leftTmp;
		}

		_Node*		_balance(_Node* node) {
			if (_isRed(node->right))
				node = _rotateLeft(node);
			if (_isRed(node->left) && _isRed(node->left->left))
				node = _rotateRight(node);
			if (_isRed(node->left) && _isRed(node->right))
				_colorFlip(node);
			return (node);
		}

		_Node*		_colorFlip(_Node* currentNode) { // делаем инверсию цветов
			currentNode->color = !currentNode->color;
			currentNode->left->color = !currentNode->left->color;
			currentNode->right->color = !currentNode->right->color;
			return currentNode;
		}

		bool	_isRed(_Node* currentNode) {
			if (currentNode == nullptr) // Проверяем сущуствует ли node
				return (black); // возвращяем black, тк все lastNode, имееют черный цвет
			return (currentNode->color == red);
		}

		void	_linkRightNode(_Node* parent, _Node* right) {
			parent->right = right; // линкуем родителя с новой rightNode, они модет быть, либо nullptr
			if (right) // если rightNode != nullptr
				right->parent = parent;// линкуем значение parent с parentNode, если _rootNode, то _rootNode->parent == nullptr
		}

		void	_linkLeftNode(_Node* parent, _Node* left) {
			parent->left = left; // линкуем родителя с новой leftNode, они модет быть, либо nullptr
			if (left) // если leftNode != nullptr
				left->parent = parent; // линкуем значение parent с parentNode, если _rootNode, то _rootNode->parent == nullptr
		}

		_Node*	_deleteNode(const key_type& k, _Node* currentNode) {
			int comp = ((_compare(k, currentNode->content->first)) | (_compare(currentNode->content->first, k))); // 0 если они равны, в противном случае 1

			if (comp == 1 &&  _compare(k, currentNode->content->first) == 1) {// compare == 1 && _comp(k, currentNode->content->first) == 1, значит мы идем по левой ветке
				if (!_isRed(currentNode->left) && !_isRed(currentNode->left->left))
					currentNode = _moveRedLeft(currentNode->left);
				_linkLeftNode(currentNode, _deleteNode(k, currentNode->left));
				return _balance(currentNode);
			}
			else {
				if (_isRed(currentNode->left)) { // если k > currentNode->content->first, то мы будем всегда поднимать краную левую ветку, для простоты итерирования
					currentNode = _rotateRight(currentNode);
					_linkRightNode(currentNode, _deleteNode(k, currentNode->right)); // линкуем currentNode(parent) со следуущей findNode, тем самым рекурсивно раскручивая связи
					return _balance(currentNode);
				}
				if (comp == 0 && (currentNode == nullptr || currentNode == _endNode)) {
					_Node*	tmpLink; // tmpLink хранит в себе связь с _endNode, которую до этого хранила удаленная currentNode
					if (!currentNode->left && currentNode->right == _endNode)
						tmpLink = currentNode->right;
					else
						tmpLink = currentNode->left;
//					_destroyNode(currentNode); //  удаляем currentNode
					return tmpLink; // возвращяем link на _endNode;
				}
				if (!_isRed(currentNode->right) && !_isRed(currentNode->right->left))
					currentNode = _moveRedRight(currentNode);
				if (_compare(k, currentNode->content->first) == 0) {
					_Node* tmpLink;
					_Node*	tmpCurrent = currentNode->right;
					while (tmpCurrent->left)
						tmpCurrent = tmpCurrent->left;
					tmpLink = tmpCurrent;
					return tmpLink;
				}
			}
			return nullptr;
		}

		_Node*	_moveRedLeft(_Node* currentNode) {
			_colorFlip(currentNode);
			if (_isRed(currentNode->right->left)) {
				currentNode->right = _rotateRight(currentNode->right);
				currentNode = _rotateLeft(currentNode);
				_colorFlip(currentNode);
			}
			return currentNode;
		}

		_Node*	_moveRedRight(_Node* currentNode) {
			_colorFlip(currentNode);
			if (_isRed(currentNode->left->left)) {
				currentNode = _rotateRight(currentNode);
				_colorFlip(currentNode);
			}
			return currentNode;
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
			reference operator*() const { return *(this->_it->content); }
			pointer operator->() const { return this->_it->content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->left)
					return findLowNode(currentNode->left);
				return currentNode;
			}

			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->right)
					return findHighNode(currentNode->right);
				return currentNode;
			}

			_Node *nextNode(_Node* currentNode) {
				if (currentNode->right)
					return findLowNode(currentNode->right);
				else if (currentNode->parent && currentNode->parent->left == currentNode)
					return currentNode->parent;
				else if (currentNode->parent->right == currentNode)
					currentNode = currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->right == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->right;
				return tmp->parent;
			}

			_Node *prevNode(_Node* currentNode) {
				if (currentNode->left)
					return findHighNode(currentNode->left);
				else if (currentNode->parent && currentNode->parent->right == currentNode)
					return currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->left == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->left;
				return tmp->parent;
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
			const_reference operator*() const { return *(this->_it->content); };
			const_pointer operator->() const { return this->_it->content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->left)
					return findLowNode(currentNode->left);
				return currentNode;
			}
			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->right)
					return findHighNode(currentNode->right);
				return currentNode;
			}
			_Node *nextNode(_Node* currentNode) {
				if (currentNode->right)
					return findLowNode(currentNode->right);
				else if (currentNode->parent && currentNode->parent->left == currentNode)
					return currentNode->parent;
				else if (currentNode->parent->right == currentNode)
					currentNode = currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->right == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->right;
				return tmp->parent;
			}
			_Node *prevNode(_Node* currentNode) {
				if (currentNode->left)
					return findHighNode(currentNode->left);
				else if (currentNode->parent && currentNode->parent->right == currentNode)
					return currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->left == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->left;
				return tmp->parent;
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
			value_type & operator*() const { return *(this->_it->content); };
			value_type * operator->() const { return this->_it->content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->left)
					return findLowNode(currentNode->left);
				return currentNode;
			}
			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->right)
					return findHighNode(currentNode->right);
				return currentNode;
			}
			_Node *nextNode(_Node* currentNode) {
				if (currentNode->right)
					return findLowNode(currentNode->right);
				else if (currentNode->parent && currentNode->parent->left == currentNode)
					return currentNode->parent;
				else if (currentNode->parent->right == currentNode)
					currentNode = currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->right == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->right;
				return tmp->parent;
			}
			_Node *prevNode(_Node* currentNode) {
				if (currentNode->left)
					return findHighNode(currentNode->left);
				else if (currentNode->parent && currentNode->parent->right == currentNode)
					return currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->left == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->left;
				return tmp->parent;
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
			reference operator*() const { return *(this->_it->content); }
			pointer operator->() const { return this->it->content; }
			_Node *getNode() const { return _it; }
		private:
			_Node *findLowNode(_Node *currentNode) {
				if (currentNode->left)
					return findLowNode(currentNode->left);
				return currentNode;
			}
			_Node *findHighNode(_Node *currentNode) {
				if (currentNode->right)
					return findHighNode(currentNode->right);
				return currentNode;
			}
			_Node *nextNode(_Node* currentNode) {
				if (currentNode->right)
					return findLowNode(currentNode->right);
				else if (currentNode->parent && currentNode->parent->left == currentNode)
					return currentNode->parent;
				else if (currentNode->parent->right == currentNode)
					currentNode = currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->right == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->right;
				return tmp->parent;
			}
			_Node *prevNode(_Node* currentNode) {
				if (currentNode->left)
					return findHighNode(currentNode->left);
				else if (currentNode->parent && currentNode->parent->right == currentNode)
					return currentNode->parent;
				_Node *tmp = currentNode;
				while (tmp->parent->left == tmp)
					if ((tmp = tmp->parent) == nullptr)
						return currentNode->left;
				return tmp->parent;
			}
		};

		/* Constructor */
		/* empty */
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _compare(comp) {
			_createBeginEndNode();
		}
		/* range */
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type(),
			 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0): _alloc(alloc), _size(0), _compare(comp) {
				_createBeginEndNode();
			 	insert(first, last);
			 }

		/* copy */
		map (const map& x): _alloc(x._alloc), _size(x._size), _compare(x._compare) {
			_createBeginEndNode();
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
		iterator		begin() { return (_size != 0) ? iterator(_beginNode->parent) : iterator(_endNode); };
		const_iterator 	begin() const { return (_size != 0) ? const_iterator(_beginNode->parent) : const_iterator(_endNode); };
		iterator		end() { return iterator(_endNode); };
		const_iterator	end() const { return const_iterator(_endNode); };

		/* Reverse Iterators */
		reverse_iterator 		rbegin() { return (_size != 0) ? reverse_iterator(_endNode->parent) : reverse_iterator(_beginNode); };
		const_reverse_iterator	rbegin() const { return (_size != 0) ? const_reverse_iterator(_endNode->parent) : const_reverse_iterator(_beginNode); };
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
		std::pair<iterator,bool> insert (const_reference val) {
			if (_size == 0) {
				_insertRootNode(black, val, nullptr, 1);
				return std::make_pair(iterator(_rootNode), true); // Добавляет iterator на root node, тк it ~= pair;
			}
			return _otherInsertCases(_rootNode, val);
		}
		iterator insert (iterator position, const_reference val) {
			(void)position;
			return insert(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
					 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			while(first != last) {
				insert(*first);
				first++;
			}
		}

		void erase (iterator position) {
			erase(position->first);
		}

		size_type erase(const key_type& k) {
			if (_size == 0 || find(k) == end())
				return 0;
			_deleteNode(k, _rootNode);
			return 1;
		}

		void erase (iterator first, iterator last) {
			while (first != last) {
				erase(first->first);
				first++;
			}
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
			while (_size != 0)
				erase(begin());
		}

		/* Observers */
		key_compare key_comp() const { return _compare; }
		value_compare value_comp() const { return value_compare(_compare); }

		/* Operations */
		iterator find (const key_type& k) {
			for (iterator it = begin(); it != end(); ++it) {
				if (it->first == k)
					return it;
			}
			return end();
		}
		const_iterator find (const key_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (it->first == k)
					return it;
			}
			return end();
		}

		size_type count (const key_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (it->first == k)
					return 1;
			}
			return 0;
		}

		iterator lower_bound (const key_type& k) {
			iterator it = begin();
			for (; it != end() && !_compare(k, it->first); ++it)
				NULL;
			return it;
		}
		const_iterator lower_bound (const key_type& k) const {
			const_iterator it = begin();
			for (; it != end() && !_compare(k, it->first); ++it)
				NULL;
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