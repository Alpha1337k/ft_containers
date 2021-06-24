#ifndef FT_MAP_HPP
#define FT_MAP_HPP

namespace ft
{
template <typename K, typename T, class Compare = std::less<K>>
class map
{
protected:
	typedef K key_type;
	typedef T mapped_type;
	typedef size_t size_type;
	typedef Compare key_compare;
	typedef std::pair<const K, T> value_type;
	
	struct map_node
	{
		map_node *left;
		map_node *right;
		map_node *back;
		bool isred;
		T	value;
		K	key;
		map_node(map_node *l, map_node *r, map_node *b, const K &k, T val): key(k)
		{
			left = l;
			right = r;
			back = b;
			value = val;
			if (!b)
				isred = false;
			else
				isred = true;
		}
	};
	map_node *_nodes;
	size_t	_size;

	void rr(map_node* parent)
	{
		map_node* left = parent->left;
		parent->left = left->right;
		if (parent->left)
			parent->left->back = parent;
		left->back = parent->back;
		if (!parent->back) // set new root if needed
			_nodes = left;
		else if (parent == parent->back->left)
			parent->back->left = left;
		else
			parent->back->right = left;
		left->right = parent;
		parent->back = left;
	}

	void rl(map_node* parent)
	{
		map_node* right = parent->right;
		parent->right = right->left;
		if (parent->right)
			parent->right->back = parent;
		right->back = parent->back;
		if (!parent->back)
			_nodes = right;
		else if (parent == parent->back->left)
			parent->back->left = right;
		else
			parent->back->right = right;
		right->left = parent;
		parent->back = right;
	}
	void		rebalance_tree(map_node *it)
	{
		map_node *grand_parent = 0, *parent = 0, *uncle = 0;

		while (it != _nodes && it->isred && it->back->isred)
		{
			parent = it->back;
			grand_parent = it->back->back;

			if (parent == grand_parent->left)
			{
				uncle = grand_parent->right;
				if (uncle && uncle->isred)
				{
					grand_parent->isred = 1;
					parent->isred = 0;
					uncle->isred = 0;
					it = grand_parent;
				}
				else
				{
					if (it == parent->right)
					{
						rl(parent);
						it = parent;
						parent = parent->back;
					}
					rr(grand_parent);
					bool tmp_color = parent->isred;
					parent->isred = grand_parent->isred;
					grand_parent->isred = tmp_color;
					it = parent;
				}
			}
			else
			{
				uncle = grand_parent->left;
				if (uncle && uncle->isred)
				{
					grand_parent->isred = 1;
					parent->isred = 0;
					uncle->isred = 0;
					it = grand_parent;
				}
				else
				{
					if (it == parent->left)
					{
						rr(parent);
						it = parent;
						parent = parent->back;
					}
					rl(grand_parent);
					bool tmp_color = parent->isred;
					parent->isred = grand_parent->isred;
					grand_parent->isred = tmp_color;
					it = parent;
				}
			}


		}
		_nodes->isred = 0;
	}
	map_node	*go_or_create(map_node *parent, int dir, K key, T value)
	{
		if (dir == 1)
		{
			if (!parent->right)
			{
				_size++;
				parent->right = new map_node(0, 0, parent, key, value);
			}
			return (parent->right);
		}
		if (!parent->left)
		{
			_size++;
			parent->left = new map_node(0, 0, parent, key, value);
		}
		return (parent->left);
	}
	map_node	*get_add_node(K key, T value = T())
	{
		map_node *it = _nodes;
		if (_nodes == 0)
		{
			_size++;
			_nodes = new map_node(0, 0, 0, key, value);
			return (_nodes);
		}
		do {
			if ((it->key < key))
				it = go_or_create(it, 1, key, value);
			if ((key < it->key))
				it = go_or_create(it, 0, key, value);
			else
				break;
		} while (1);
		rebalance_tree(it);
		return (it);
	}
public:
	map(): _nodes(0), _size(0) {}
	~map() {clear();}
	map(const map &m): _nodes(0), _size(0) {*this = m;}

	map	&operator=(const map &m)
	{
		this->_size = m._size;
		iterator it = m.begin();
		while (it != m.end())
		{
			get_add_node(it->first) = it->second;
			it++;
		}
		
	}
	T& operator[](const K &key)
	{
		return (get_add_node(key)->value);
	}
	void swap( map& other )
	{
		size_t tmp_size = this->_size;
		map_node *tmp_node = this->_nodes;

		this->_size = other.size;
		this->_nodes = other._nodes;
		other.size = tmp_size;
		other._nodes = tmp_node;
	}

	void clear()
	{
		erase(begin(), end());		
	}

	void erase( iterator pos );

	key_compare key_comp() const {return key_compare;}

	class value_compare
	{
		protected:
			Compare _c;
			value_compare( Compare c ): _c(c) {}
		public:
			bool operator()( const value_type& lhs, const value_type& rhs ) const {
				return (_c(lhs.first, rhs.second));
			}
	};
	map::value_compare value_comp() const {return value_compare(key_compare)();}


	class iterator
	{
	private:
		map_node *_pos;
		map_node *_base;
		map_node *_origin;
		int status = 0;

	public:
		K	first;
		T	second;
		iterator(map_node *pos, map_node *base): _pos(pos), _base(base),_origin(pos) {
			if (_pos != 0)
			{
				first = _pos->key;
				second = _pos->value;
			}
		}
		~iterator() {}
		iterator operator++(int)
		{
			std::cout << _pos << " | " << status << " | " << _base << std::endl;
			if (_pos->left && _pos != _base)
			{
				std::cout << "going left!" << std::endl;
				status = 0;
				_pos = _pos->left;
			}
			else if (_pos->right)
			{
				std::cout << "going right!" << std::endl;
				status = 1;
				_pos = _pos->right;
			}
			else if (_pos->left == 0 && _pos->right == 0)
			{
				std::cout << "going up!" << std::endl;
				status = 2;
				do {
					_origin = _pos;
					_pos = _pos->back;
				} while (_pos && _pos->right == _origin);
				status = 0;
			}
			else
			{
				std::cout << "end???" << std::endl;
				_pos = 0;
			}
			if (_pos)
			{
				first = _pos->key;
				second = _pos->value;
			}
			return *this;
		}
		iterator *operator->() { return this;}
		std::pair<K , T>	&operator*()
		{
			return (std::pair<K, T>(_pos->key, _pos->value));
		}
		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
			std::cout << "Comparing.." << std::endl;
			return (lhs._pos == rhs._pos);
		}
		friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !(lhs == rhs); }

	};


	iterator 		begin() {
		map_node *it = _nodes;
		while (it->left)
			it = it->left;
		return iterator(it, _nodes);
	}
	iterator 		end() {return iterator(0, _nodes);}

	bool empty() const {return !!!_size;}
	size_t size() const {return _size;}
	size_type count( const K& key )
	{
		if (find(key) == end())
			return (0);
		return (1);
	}

	iterator find( const K& key )
	{
		iterator it = begin();
		while (it != end())
		{
			std::cout << "Checking.." << std::endl;
			if (it->first == key)
				return (it);
			it++;
		}
		return (it);
	}
};

template <typename K, typename T, typename Compare = std::less<K>>
bool	operator==(const map<K, T> &lhs, const map<K, T> &rhs)
{
	typedef typename ft::map<K, T>::iterator iterator;

	if (lhs.size() != rhs.size())
		return (false);
	iterator li = lhs.begin();
	iterator ri = rhs.begin();
	for (; li != lhs.end(); li++, ri++)
		if (li->first != ri->first || li->second != ri->second)
			return (false);
	return (true);
}

template <typename K, typename T, typename Compare = std::less<K>>
bool	operator!=(const map<K, T> &lhs, const map<K, T> &rhs) {return !(lhs == rhs);}

template <typename K, typename T, typename Compare = std::less<K>>
bool operator<(const map<K, T> &lhs, const map<K,T> &rhs)
{
	typedef typename ft::map<K, T>::iterator iterator;



	iterator li = lhs.begin(), le = lhs.end(), ri = rhs.begin(), re = rhs.end();
	for ( ; (li != le) && (ri != re); li++, ri++ ) {
		if (li->first < ri->first || li->second < ri->second) return true;
		if (ri->first < li->first || ri->second < li->second) return false;
	}
	return (li == le) && (ri != re);
}

template <typename K, typename T, typename Compare = std::less<K>>
bool operator>(const map<K, T> &lhs, const map<K,T> &rhs)	{return rhs < lhs;}
template <typename K, typename T, typename Compare = std::less<K>>
bool operator>=(const map<K, T> &lhs, const map<K,T> &rhs) {return !(lhs < rhs);}
template <typename K, typename T, typename Compare = std::less<K>>
bool operator<=(const map<K, T> &lhs, const map<K,T> &rhs) {return !(lhs > rhs);}

}

#endif