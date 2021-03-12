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

		typedef Key	key_type;
		typedef T	mapped_type;
		typedef pair<const key_type, mapped_type >	value_type;
		typedef Compare								key_compare;
		typedef	Alloc								allocator_type;
		typedef	value_type &						reference;
		typedef const value_type &					const_reference;
		typedef value_type *						pointer;
		typedef const value_type *					const_pointer;
		typedef ptrdiff_t							difference_type;
		typedef size_t								size_type;

	private:
		typedef struct Node {
			size_type	key;
			size_type	height;
			Node*		left;
			Node*		right;
		}				t_node;
	public:
		/* Constructor */
		/* empty */
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type());
		/* range */
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type());

		/* copy */
		map (const map& x);

		/* Destructor */
		~map();

		/* Operators */
		 /* copy */
		map& operator= (const map& x);

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
		bool empty() const;

		size_type size() const;

		size_type max_size() const;

		/* Element Access */
		mapped_type& operator[] (const key_type& k);

		/* Mpdifiers */
		/* single element */
		pair<iterator,bool> insert (const value_type& val);
		iterator insert (iterator position, const value_type& val);
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);

		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);

		void swap (map& x);
		void clear();

		/* Observers */
		key_compare key_comp() const;
		value_compare value_comp() const;

		/* Operations */
		iterator find (const key_type& k);
		const_iterator find (const key_type& k) const;

		size_type count (const key_type& k) const;

		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;

		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);

	};
}