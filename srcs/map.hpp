namespace ft {
	template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = less<Key>,                     // map::key_compare
			class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
	>
	class map {
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type, mapped_type >	value_type;
		typedef Compare								key_compare;
		typedef	Alloc								allocator_type;
		typedef	value_type &						reference;
		typedef const value_type &					const_reference;
		typedef value_type *						pointer;
		typedef const value_type *					const_pointer;
		typedef ptrdiff_t							difference_type;
		typedef size_t								size_type;

		template<bool B, class C = void>
		struct enable_if {};

		template <class C>
		struct enable_if <true, C> { typedef T type; };
	private:
		template <class Key, class T, class Compare, class Alloc>
		class map<Key,T,Compare,Alloc>::value_compare
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		}

		static bool black = false;
		static bool red = true;
		allocator_type _alloc;
		typedef struct Map {
			pointer		content;
			struct Map*	left;
			struct Map* right;
			struct Map*	parent;
			bool		color;
		}				_t_map;

		size_type 		_size;
		key_compare 	_compare;
		_t_map*			_rootNode;
		_t_map*			_beginNode;
		_t_map*			_endNode;

		typedef typename allocator_type::template rebind<_t_map>::other allocator_rebind_type;
		allocator_rebind_type _allocator_rebind;

		void	_createBeginEndNode() {
			_beginNode = _allocator_rebind.allocate(1);
			_beginNode->content = _alloc.allocate(1);
			_beginNode->left = nullptr;
			_beginNode->right = nullptr;

			_beginNode = _allocator_rebind.allocate(1);
			_beginNode = _allocator_rebind.allocate(1);
			_beginNode->left = nullptr;
			_beginNode->right = nulltpr;
		}

		_t_map*	_createNode(bool color, const_reference val, _t_map* parent, size_type size) {
			_t_map*	tmpNode = _allocator_rebind.allocate(1);
			tmpNode->content = _alloc.allocate(1);
			tmpNode->content = val;
			tmpNode->left = nullptr;
			tmpNode->right = nullptr;
			tmpNode->parent = parent;
			tmpNode->color = color;
			_size += size;
			return tmpNode;
		}

		void _insertRootNode(void) {
			_rootNode = _createNode(black, val, nullptr, 1);
			_rootNode->left = _beginNode;
			if (_beginNode)
				_beginNode->parent = _rootNode;
			_rootNode->right = _endNode;
			if (_endNode)
				_endNode->parent = _rootNode;
		}

		std::pair<iterator, bool> _otherInsertCases(_t_map* currentNode, const_reference val) {
			int comp = _compare(val.first, currentNode->content->first) | _compare(currentNode->content->first, val.first); // 0 если равны, 1 если меньше или больше

			if (comp == 0)
				return std::pair<iterator(currentNode), false>; // Не добавляем одинаковые значения, возвращаем false, как флаг недобавленной node
			else if (comp == 1) {
				if ((comp = _compare(val.first, currentNode->content->first)) == 1 && currentNode->left) //TODO может быть понадобится проверка на _beginNode rootNode != _beginNode
					_otherInsertCase(currentNode, val);
				else if ((comp = _compare(val.first, currentNode->content->first)) == 0 && currentNode->right) //TODO может быть понадобится проверка на _endNode rootNode != _endNode
					_otherInsertCases(currentNode, val);
				else {
					_t_map* tmpNode = _createNode(red, val, currentNode, 1);
					if (comp == 0) ? _insertLeftNode(tmpNode, currentNode) : _insertRightNode(tmpNode, currentNode);
					_balance(currentNode);
					return std::make_pair(iterator(tmpNode), true);
				}
			}
		}

		void	_insertLeftNode(_t_map* leftNode, _t_map* parentNode) {
			if (parentNode->left == _beginNode) {
				leftNode->left = _beginNode;
				if (_beginNode)
					_beginNode->parent = leftNode;
			}
			parentNode->left = leftNode; // LinkLeft
			if (leftNode)
				leftNode->parent = parentNode;
		}

		void	_insertRightNode(_t_map* rightNode, _t_map* parentNode) {
			if (parentNode->right == _beginNode) {
				rightNode->left = _beginNode;
				if (_beginNode)
					_beginNode->parent = rightNode;
			}
			parentNode->right = rightNode; // LinkRight
			if (rightNode)
				rightNode->parent = parentNode;
		}

		_t_map*		_rotateLeft(_t_map* node) {
			_t_map*	rightTmp = node->right;
			node->right = rightTmp->left;
			rightTmp->left = node;
			rightTmp->color = rightTmp->left->color;
			rightTmp->left->color = red;
			return rightTmp;
		}

		_t_map*		_rotateRight(_t_map* node) {
			_t_map*	leftTmp = node->left;
			node->left = leftTmp->right;
			leftTmp->right = node;
			leftTmp->color = leftTmp->right->color;
			leftTmp->right->color = red;
			return leftTmp;
		}

		_t_map*		_balance(_t_map* node) {
			if (_isRed(node->right))
				node = _rotateLeft(node);
			if (_isRed(node->left) && _isRed(node->left->left))
				node = _rotateRight(node);
			if (_isRed(node->left) && _isRed(node->right))
				_colorFlip(node);
		}

		_t_map*		_colorFlip(_t_map* currentNode) {
			currentNode->color = !currentNode->color;
			currentNode->left->color = !currentNode->left->color;
			currentNode->right->color = !currentNode->right->color;
			return currentNode;
		}

		bool	_isRed(_t_map* node) {
			if (node == nullptr)
				return (false);
			return (node->color == red);
		}
	public:
		/* Constructor */
		/* empty */
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _compare(key_compare) {
			_createBeginEndNode();
		}
		/* range */
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type(),
			 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0): _alloc(alloc), _size(0), _compare(key_compare) {
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
		iterator begin();
		const_iterator begin() const

		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

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
			const_iterator it = find(k);
			if (it == end())
				return (std::make_pair)
			else
				return it->second;
		}

		/* Mpdifiers */
		/* single element */
		std::pair<iterator,bool> insert (const value_type& val) {
			if (_size == 0) {
				_insertRootNode();
				return std::make_pair(iterator(_rootNode), true); // Добавляет iterator на root node, тк it ~= pair;
			}
			return _otherInsertCases(_rootNode, val);
		}
		iterator insert (iterator position, const value_type& val) {} // TODO разобрать и дописать insert по итератору позиции

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
					 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			while(first != last) {
				insert(*first);
				first++;
			}
		}

		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);

		void swap (map& x) {
			_t_map* tmpRootNode = _rootNode;
			_rootNode = x._rootNode;
			x._rootNode = tmpRootNode;

			_t_map*	tmpBeginNode = _beginNode;
			_beginNode = x._beginNode;
			x._beginNode = tmpBeginNode;

			_t_map*	tmpEndNode = _endNode;
			_endNode = x._endNode;
			x._endNode = tmpEndNode;

			size_type tmpSize = _size;
			_size = x._size;
			x._size = tmpSize;
		}

		void clear() {
			while (size != 0)
				erase(begin());
		}

		/* Observers */
		key_compare key_comp() const { return _compare; }
		value_compare value_comp() const { return _}

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

		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;

		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);

	};
}