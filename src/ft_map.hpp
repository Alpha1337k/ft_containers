#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <iostream>
#include <ft_node.hpp>
#include <ft_queue.hpp>
#include <ft_bintree.hpp>

namespace ft
{

template <typename K, typename T, class Compare = std::less<K>, class Allocator = std::allocator<ft::pair<const K, T> > >
class map
{
protected:
	typedef K key_type;
	typedef T mapped_type;
	typedef size_t size_type;
	typedef Compare key_compare;
	typedef ft::pair<const K, T> value_type;

	bintree<K, T, Compare> _tree;
	Compare _cmp;
public:
	map(): _tree() {}
	template< class InputIt >
	map( InputIt first, InputIt last, const Compare& comp = Compare()): _tree(), _cmp(comp)
	{
		for (; first != last; first++)
			_tree.get_add_node(first->first, first->second);
	}
	explicit map( const Compare& comp): _tree(), _cmp(comp()) {}
	~map() {clear();}
	map(const map &m): _tree() {*this = m;}

	map	&operator=(const map &m)
	{
		iterator it = m.begin();
		while (it != m.end())
		{
			_tree.get_add_node(it->first)->val.second = it->second;
			it++;
		}
		return *this;
	}
	T& operator[](const K &key)
	{
		return (_tree.get_add_node(key)->val.second);
	}
	void swap( map& other )
	{
		size_t tmp_size = this->_tree._size;
		map_node<K, T> *tmp_node = this->_tree._nodes;

		this->_tree._size = other._tree._size;
		this->_tree._nodes = other._tree._nodes;
		other._tree._size = tmp_size;
		other._tree._nodes = tmp_node;
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

	void inorder()
	{
		_tree.inorder();
	}

	class iterator
	{
	public:
		map_node<K, T> *_pos;
		map_node<K, T> *_base;
		map_node<K, T> *_origin;
		key_compare		_comp = std::less<K>();
		int status = 0;

	public:
		iterator(map_node<K, T> *pos, map_node<K, T> *base): _pos(pos), _base(base), _origin(pos) {}
		~iterator() {}
		iterator operator++(int)
		{
			// std::cout << _pos->left << " " << _pos->right << " " << _pos->back << " " << _base  << " " << _origin << std::endl;

			if (_pos->right)
			{
				_pos = _pos->right;
				while (_pos->left)
					_pos = _pos->left;
			}
			else
			{
				do
				{
					_origin = _pos;
					_pos = _pos->back;
				} while (_pos && _comp(_pos->val.first, _origin->val.first));
			}
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
		map_node<K, T> *it = _tree._nodes;
		while (it->left)
			it = it->left;
		return iterator(it, _tree._nodes);
	}
	const iterator 		begin() const {
		map_node<K, T> *it = _tree._nodes;
		while (it->left)
			it = it->left;
		return iterator(it, _tree._nodes);
	}
	iterator 		end() {return iterator(0, _tree._nodes);}
	const iterator 		end() const {return iterator(0, _tree._nodes);}

	bool empty() const {return !!!_tree._size;}
	size_t size() const {return _tree._size;}
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
		map_node<K, T> *it = pos._pos;
		_tree._size--;
		_tree.remove_node(it);
	}
	
	void erase( iterator first, iterator last )
	{
		iterator next = first;
		size_t removed = 0;
		while (next != last)
		{
			next++;
			_tree.remove_node(first._pos);
			first = next;
			_tree._size--;
			removed++;
		}
	}
	pair<iterator, bool> insert( const value_type& value )
	{
		size_t old_size = _tree._size;
		iterator i = iterator(_tree.get_add_node(value.first, value.second), _tree._nodes);

		return (pair<iterator, bool>(i, !(old_size == _tree._size)));
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