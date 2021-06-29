#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <iostream>
#include <ft_pair.hpp>

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
	typedef ft::pair<const K, T> value_type;

	struct map_node
	{
		map_node *left;
		map_node *right;
		map_node *back;
		ft::pair<K, T> val;
		map_node(map_node *l, map_node *r, map_node *b, const K &k, T val): val(k, val)
		{
			left = l;
			right = r;
			back = b;
		}
	};
	map_node *_nodes;
	size_t	_size;
	Compare _cmp;
	
	void		update_back(map_node *it, map_node *replace)
	{
		if (!it->back)
			return;
		if (it->back->left == it)
			it->back->left = replace;
		else
			it->back->right = replace;
	}

	void	remove_node(map_node *it)
	{
		if (it == 0)
			return;
		std::cout << it->val.first << std::endl;
		if (it->left == 0 && it->right == 0)
		{
			update_back(it, 0);
			delete it;
		}
		else if (it->left == 0 || it->right == 0)
		{
			map_node *tmp;
			if (it->left)
				tmp = it->left;
			else
				tmp = it->right;
			tmp->back = it->back;
			update_back(it, tmp);
			delete it;
		}
		else
		{
			map_node *tmp = it->right;
			while (tmp->left)
				tmp = tmp->left;
			if (tmp->right)
				tmp->back->left = tmp->right;
			tmp->back = it->back;
			update_back(it, tmp);
			it->left->back = tmp;
			it->right->back = tmp;
			delete it;
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
		pair<K, T>	*operator->() { return &_pos->val;}
		pair<K, T>	&operator*()
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
			next++;
			remove_node(first._pos);
			first = next;
			_size--;
			removed++;
		}
	}
	pair<iterator, bool> insert( const value_type& value )
	{
		size_t old_size = _size;
		iterator i = iterator(get_add_node(value.first, value.second), _nodes);

		return (pair<iterator, bool>(i, !(old_size == _size)));
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

	pair<iterator,iterator> equal_range( const K& key )
	{
		return (pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
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