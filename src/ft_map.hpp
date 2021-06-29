#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <iostream>

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
		std::pair<K, T> val;
		map_node(map_node *l, map_node *r, map_node *b, const K &k, T val): val(k, val)
		{
			left = l;
			right = r;
			back = b;
			if (!b)
				isred = false;
			else
				isred = true;
		}
	};
	map_node *_nodes;
	size_t	_size;
	Compare _cmp;

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
	map_node *to_replace(map_node *n)
	{
		if (n->left && n->right)
		{
			map_node *it = n->right;
			while (it->left != 0)
				it = it->left;
			return (it);		
		}
		if (n->right)
			return (n->right);
		return (n->left);
	}

	map_node	*get_sibling(map_node *it)
	{
		if (it == 0 || it->back == 0)
			return (0);
		if (it->back->left == it)
			return (it->right);
		return (it->left);
	}

	void	update_back(map_node *n, map_node *it)
	{
		if (n != 0)
			n->back = it;
	}

	void	swap_succesor(map_node *lhs, map_node *rhs)
	{
		// std::pair<K, T> tmp(lhs->val);
		// lhs->val = rhs->val;
		// rhs->val = tmp;
		map_node *lhs_ptr[3];

		lhs_ptr[0] = lhs->left;
		lhs_ptr[1] = lhs->right;
		lhs_ptr[2] = lhs->back;

		lhs->left = rhs->left;
		lhs->right = rhs->right;
		lhs->back = rhs->back;
		rhs->left = lhs_ptr[0];
		rhs->right = lhs_ptr[1];
		rhs->back = lhs_ptr[2];
		// std::cout << "updating.." << std::endl;
		update_back(lhs->left, lhs);
		update_back(lhs->right, lhs);
		update_back(rhs->left, rhs);
		update_back(rhs->right, rhs);
		// std::cout << "backing.." << std::endl;
		if (rhs->back)
		{
			if (rhs->back->left == lhs)
				rhs->back->left = rhs;
			else
				rhs->back->right = rhs;
		}
		if (lhs->back)
		{
			if (lhs->back->left == rhs)
				lhs->back->left = lhs;
			else
				lhs->back->right = lhs;
		}
	}

	void	fix_dblack(map_node *it)
	{
		if (it == _nodes)
			return;
		
		map_node *sibling = get_sibling(it);
		map_node *parent = it->back;

		if (sibling == 0)
			return (fix_dblack(parent));
		if (sibling->isred)
		{
			parent->isred = true;
			sibling->isred = false;
			if (parent->left == sibling)
				rr(parent);
			else
				rl(parent);
			fix_dblack(it);
		}
		else
		{
			if ((sibling->left && sibling->left->isred) || (sibling->right && sibling->right->isred))
			{
				if (sibling->left && sibling->left->isred)
				{
					if (parent->left == sibling)
					{
						sibling->left->isred = sibling->isred;
						sibling->isred = parent->isred;
						rr(parent);
					}
					else
					{
						sibling->left->isred = parent->isred;
						rr(sibling);
						rl(parent);
					}
				}
				else
				{
					if (parent->left == sibling)
					{
						sibling->right->isred = parent->isred;
						rl(sibling);
						rr(parent);
					}
					else
					{
						sibling->right->isred = sibling->isred;
						sibling->isred = parent->isred;
						rl(parent);
					}
					
				}
			}
			else
			{
				sibling->isred = true;
				if (parent->isred == false)
					fix_dblack(parent);
				else
					parent->isred = false;
			}
		}
	}

	map_node	*remove_node(map_node *it)
	{
		if (it == 0)
			return (0);
		map_node *next = to_replace(it);

		bool dblack = (next == 0 || next->isred == 0) && it->isred == 0;
		map_node *parent = it->back;
		map_node *sibling = get_sibling(it);

		// std::cout << it << " | " << next << " | " << parent << " | " << sibling << " | " << _nodes << " | "  << it->val.first << std::endl;
		if (next == 0)
		{
			if (it == _nodes)
				_nodes = 0;
			else
			{
				if (dblack)
					fix_dblack(it);
				else if (sibling)
					sibling->isred = true;
				if (parent->left == it)
					parent->left = 0;
				else if (parent->right == it)
					parent->right = 0;
			}
			delete it;
			return (parent);
		}
		else if (it->left == 0 || it->right == 0)
		{
			if (it == _nodes)
			{
				delete it;
				next->back = 0;
				_nodes = next;
				// std::cout << "returning next " << std::endl;
				return (next);
			}
			else
			{
				if (parent->left == it)
					parent->left = next;
				else
					parent->right = next;
				delete it;
				next->back = parent;
				if (dblack)
					fix_dblack(next);
				else
					next->isred = false;
				return (next);
			}
		}
		else
		{
			swap_succesor(next, it);
			return (remove_node(next));
		}
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
			if (_cmp(it->val.first, key))
				it = go_or_create(it, 1, key, value);
			else if (_cmp(key, it->val.first))
				it = go_or_create(it, 0, key, value);
			else
				break;
		} while (1);
		rebalance_tree(it);
		return (it);
	}

	/*
		start of the map functions
	*/

public:
	map(): _nodes(0), _size(0), _cmp(Compare()) {}
	template< class InputIt >
	map( InputIt first, InputIt last, const Compare& comp = Compare()): _nodes(0), _size(0), _cmp(comp)
	{
		for (; first != last; first++)
			get_add_node(first->first, first->second);
	}
	explicit map( const Compare& comp): _nodes(0), _size(0), _cmp(comp) {}
	~map() {clear();}
	map(const map &m): _nodes(0), _size(0) {*this = m;}

	map	&operator=(const map &m)
	{
		iterator it = m.begin();
		while (it != m.end())
		{
			get_add_node(it->first)->val.second = it->second;
			it++;
		}
		return *this;
	}
	T& operator[](const K &key)
	{
		return (get_add_node(key)->val.second);
	}
	void swap( map& other )
	{
		size_t tmp_size = this->_size;
		map_node *tmp_node = this->_nodes;

		this->_size = other._size;
		this->_nodes = other._nodes;
		other._size = tmp_size;
		other._nodes = tmp_node;
	}

	void clear()
	{
		erase(begin(), end());
	}

	key_compare key_comp() const {return _cmp;}

	class value_compare
	{
		protected:
			Compare _c;
		public:
			value_compare( Compare c ): _c(c) {}
			bool operator()(const value_type& lhs, const value_type& rhs ) const {
				return (_c(lhs.first, rhs.first));
			}
	};
	map::value_compare value_comp() const {return value_compare(_cmp);}


	class iterator
	{
	public:
		map_node *_pos;
		map_node *_base;
		map_node *_origin;
		int status = 0;

	public:
		iterator(map_node *pos, map_node *base): _pos(pos), _base(base),_origin(pos) {
		}
		~iterator() {}
		iterator operator++(int)
		{
			if (_pos->left && _pos != _base && _origin != _pos->left)
			{
				status = 0;
				_pos = _pos->left;
				while (_pos->left)
					_pos = _pos->left;
			}
			else if (_pos->right)
			{
				status = 1;
				_pos = _pos->right;
				while (_pos->left)
					_pos = _pos->left;
			}
			else if (_pos->left == 0 && _pos->right == 0)
			{
				do {
					_origin = _pos;
					_pos = _pos->back;
				} while (_pos && _pos->right == _origin);
				status = 1;
			}
			else
				_pos = 0;
			return *this;
		}
		std::pair<K, T>	*operator->() { return &_pos->val;}
		std::pair<K, T>	&operator*()
		{
			return (_pos->val);
		}
		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
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
	const iterator 		begin() const {
		map_node *it = _nodes;
		while (it->left)
			it = it->left;
		return iterator(it, _nodes);
	}
	iterator 		end() {return iterator(0, _nodes);}
	const iterator 		end() const {return iterator(0, _nodes);}

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
			if (it->first == key)
				return (it);
			it++;
		}
		return (it);
	}
	void erase( iterator pos ) {
		map_node *it = pos._pos;
		_size--;
		remove_node(it);
	}
	
	void erase( iterator first, iterator last )
	{
		iterator next = first;
		size_t removed = 0;
		while (next != last)
		{
			// std::cout << removed << " removing.." << first->first << std::endl;
			next++;
			remove_node(first._pos);
			first = next;
			_size--;
			removed++;
		}
	}
	std::pair<iterator, bool> insert( const value_type& value )
	{
		size_t old_size = _size;
		iterator i = iterator(get_add_node(value.first, value.second), _nodes);

		return (std::pair<iterator, bool>(i, !(old_size == _size)));
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last )
	{
		for(; first != last; first++)
			get_add_node(first.first, first.second);
	}

	iterator lower_bound( const K& key )
	{
		iterator it = begin();
		while (it != end())
		{
			if (!_cmp(it->first, key)) // !key < k
				break;
			it++;
		}
		return (it);
	}
	iterator upper_bound( const K& key )
	{
		iterator it = begin();
		while (it != end())
		{
			if (_cmp(key, it->first))  // key < k
				break;
			it++;
		}
		return (it);		
	}

	std::pair<iterator,iterator> equal_range( const K& key )
	{
		return (std::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
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

template <typename K, typename T, class Compare = std::less<K>>
void	swap(ft::map<K, T, Compare> &lhs, ft::map<K, T, Compare> &rhs)
{
	lhs.swap(rhs);
}

}

#endif