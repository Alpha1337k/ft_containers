// #ifndef FT_MAP_HPP
// #define FT_MAP_HPP

// namespace ft
// {
// template <typename K, typename T, typename Compare = std::less<K>>
// class map
// {
// private:
// 	typedef K key_type
// 	typedef T mapped_type;
// 	typedef size_t size_type;
// 	typedef Compare key_compare;
	
	
// 	struct map_node
// 	{
// 		map_node *left;
// 		map_node *right;
// 		map_node *back;
// 		bool isred;
// 		T	value;
// 		const K	key;
// 		map_node(map_node *l, map_node *r, map_node *b, T val, const K &k): key(k)
// 		{
// 			left = l;
// 			right = r;
// 			back = b;
// 			value = val;
// 			if (!b)
// 				isred = false;
// 			else
// 				isred = true;
// 		}
// 	};
// 	map_node *_nodes;
// 	size_t	_size;

// 	void rr(map_node* parent)
// 	{
// 		map_node* left = parent->left;
// 		parent->left = left->right;
// 		if (parent->left)
// 			parent->left->back = parent;
// 		left->back = parent->back;
// 		if (!parent->back) // set new root if needed
// 			nodes = left;
// 		else if (parent == parent->back->left)
// 			parent->back->left = left;
// 		else
// 			parent->back->right = left;
// 		left->right = parent;
// 		parent->back = left;
// 	}

// 	void rl(map_node* parent)
// 	{
// 		map_node* right = parent->right;
// 		parent->right = right->left;
// 		if (parent->right)
// 			parent->right->back = parent;
// 		right->back = parent->back;
// 		if (!parent->back)
// 			nodes = right;
// 		else if (parent == parent->back->left)
// 			parent->back->left = right;
// 		else
// 			parent->back->right = right;
// 		right->left = parent;
// 		parent->back = right;
// 	}
// 	void		rebalance_tree(map_node *it)
// 	{
// 		map_node *grand_parent = 0, *parent = 0, *uncle = 0;

// 		while (it != nodes && it->isred && it->back->isred)
// 		{
// 			parent = it->back;
// 			grand_parent = it->back->back;

// 			if (parent == grand_parent->left)
// 			{
// 				uncle = grand_parent->right;
// 				if (uncle && uncle->isred)
// 				{
// 					grand_parent->isred = 1;
// 					parent->isred = 0;
// 					uncle->isred = 0;
// 					it = grand_parent;
// 				}
// 				else
// 				{
// 					if (it == parent->right)
// 					{
// 						rl(parent);
// 						it = parent;
// 						parent = parent->back;
// 					}
// 					rr(grand_parent);
// 					bool tmp_color = parent->isred;
// 					parent->isred = grand_parent->isred;
// 					grand_parent->isred = tmp_color;
// 					it = parent;
// 				}
// 			}
// 			else
// 			{
// 				uncle = grand_parent->left;
// 				if (uncle && uncle->isred)
// 				{
// 					grand_parent->isred = 1;
// 					parent->isred = 0;
// 					uncle->isred = 0;
// 					it = grand_parent;
// 				}
// 				else
// 				{
// 					if (it == parent->left)
// 					{
// 						rr(parent);
// 						it = parent;
// 						parent = parent->back;
// 					}
// 					rl(grand_parent);
// 					bool tmp_color = parent->isred;
// 					parent->isred = grand_parent->isred;
// 					grand_parent->isred = tmp_color;
// 					it = parent;
// 				}
// 			}


// 		}
// 		nodes->isred = 0;
// 	}
// 	map_node	*get_add_node(K key)
// 	{
// 		map_node *it = nodes;
// 		if (nodes == 0)
// 			nodes = new map_node(0, 0, 0, key, key);
// 		else
// 		{
// 			do {
// 			if (Compare(it->key, key))
// 				it = go_or_create(it, 1, key);
// 			if (Compare(key, it->key))
// 				it = go_or_create(it, 0, key);
// 			else
// 				break;
// 			} while (1);
// 			rebalance_tree(it);
// 		}
// 		return (it);
// 	}
// public:
// 	map(): _nodes(0), _size(0) {}
// 	~map() {}
// 	map(const map &m): _nodes(0), _size(0) {*this = m;}

// 	map	&operator=(const map &m)
// 	{
// 		this->_size = m._size;
// 	}
// 	T& operator[](const K &key)
// 	{
// 		return (find_or_create(key)->value);
// 	}

// 	class iterator
// 	{
// 		protected:
// 			map_node *_pos;
// 			map_node *_highest_node;
// 			int		_explored_paths;
// 			map_node *enter_left_node(map_node *pos)
// 			{
// 				_pos = _pos->left;
// 			}
// 			map_node *enter_left_node(map_node *pos)
// 			{
// 				_pos = _pos->left;
// 			}

// 		public:
// 			iterator(map_node *p): _pos(p), _explored_paths(0) {}
// 			iterator(const iterator &i) {*this = i}
// 			iterator &operator=(const iterator &i) {_pos = i._pos; return *this;}
// 			iterator& operator++()
// 			{
// 				if (_pos->left)
					
// 				else if (_pos->right)
// 					_pos = _pos->right;
// 				else
// 					_pos = _pos->back;

// 			}
// 			iterator& operator--()
// 			{

// 			}
// 			iterator operator++(int)
// 			{
// 				iterator old = *this;
// 				operator++();
// 				return (old);
// 			}
// 			iterator operator--(int)
// 			{
// 				iterator old = *this;
// 				operator--();
// 				return (old);
// 			}
// 	}


// 	iterator 		begin() {
// 		map_node *it = _nodes;
// 		while (it->left)
// 			it = it->left;
// 		return iterator(it);
// 	}
// 	iterator const	begin() {}
// 	iterator const	end() {return iterator(0);}
// 	iterator 		end() {return iterator(0);}
// 	bool empty() const {return !!!_size;}
// 	size_t size() const {return _size;}

// };


// }

// #endif