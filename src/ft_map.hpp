/* ._______________________________________________________________________. */
/* |                                                                       | */
/* |     ____  ______   | Oscar Kruithof                                   | */
/* |    / __/ /__  __/  | https://github.com/Alpha1337k                    | */
/* |   / /=     / /     | okruitho                                         | */
/* |  /_/      /_/      |                                                  | */
/* | _____________________________________________________________________ | */
/* |       _                                                               | */
/* |     /   )                                                             | */
/* |    /       __    _   _/_   _    .   _     _     _      _              | */
/* |   /      /   ) /   ) /   / - ) /  /   ) /  _) /   )  ( _ `            | */
/* |  ( __ / ( _ / /   / /   /   / /  /   / (     /  \`  \ _ )             | */
/* |                                                                       | */
/* ._______________________________________________________________________. */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <iostream>
#include <ft_node.hpp>
#include <ft_bintree.hpp>
#include <ft_iterator.hpp>
#include <limits>

namespace ft
{

template <typename K, typename T, class Compare = std::less<K>, class Allocator = std::allocator<ft::pair<const K, T> > >
class map
{
public:
	typedef K							key_type;
	typedef T							mapped_type;
	typedef ft::pair<const K, T> 		value_type;
	typedef size_t						size_type;
	typedef std::ptrdiff_t				difference_type;
	typedef Compare						key_compare;
	typedef Allocator					allocator_type;
	typedef value_type&					reference;
	typedef value_type const&			const_reference;
	typedef typename Allocator::pointer			pointer;
	typedef typename Allocator::const_pointer	const_pointer;

	class iterator
	{
	public:
		typedef ft::pair<const K, T> 	value_type;
		typedef std::ptrdiff_t			difference_type;
		typedef size_t 					size_type;
		typedef ft::pair<const K, T>&	const_reference;
		typedef ft::pair<const K, T>&	reference;
		typedef typename Allocator::pointer		pointer;
		typedef	T					iterator_category;
	protected:
		map_node<const K, T> *_pos;
		map_node<const K, T> *_origin;
		key_compare		_comp;
	public:
		iterator(map_node<const K, T> *pos, key_compare comp): _pos(pos), _origin(pos), _comp(comp) {}
		~iterator() {}
		iterator &operator=(const iterator &it)
		{
			_pos = it._pos;
			_origin = it._origin;
			_comp = it._comp;
			return *this;
		}
		iterator &operator++()
		{
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
		iterator &operator--()
		{
			if (_pos->left)
			{
				_pos = _pos->left;
				while (_pos->right)
					_pos = _pos->right;
			}
			else
			{
				do
				{
					_origin = _pos;
					_pos = _pos->back;
				} while (_pos && _comp(_origin->val.first, _pos->val.first));
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			operator++();
			return (*this);
		}
		iterator operator--(int)
		{
			iterator old = *this;
			operator--();
			return (*this);
		}
		ft::pair<const K, T>	*operator->() { return &_pos->val;}
		ft::pair<const K, T>	&operator*()
		{
			return (_pos->val);
		}
		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
			return (lhs._pos == rhs._pos);
		}
		friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !(lhs == rhs); }

	};
	typedef	iterator const const_iterator;
	typedef	ft::reverse_iterator<iterator> reverse_iterator;
private:
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
		clear();
		_tree = m._tree;
		return *this;
	}
	T& operator[](const K &key)
	{
		return (_tree.get_add_node(key)->val.second);
	}
	T& at( const K& key )
	{
		map_node<const K, T> *n =	_tree.get_node(key);
		if (n == 0)
			throw std::out_of_range("map::at");
		return (n->val.second);
	}
	const T& at( const K& key ) const
	{
		map_node<const K, T> *n =	_tree.get_node(key);
		if (n == 0)
			throw std::out_of_range("map::at");
		return (n->val.second);
	}


	allocator_type get_allocator() const {return _tree._alloc;}
	size_type max_size() const {return (std::numeric_limits<std::ptrdiff_t>::max() / sizeof(map_node<const K, T>) * 2 + 1);}

	void swap( map& other )
	{
		size_t tmp_size = this->_tree._size;
		map_node<const K, T> *tmp_node = this->_tree._nodes;

		this->_tree._size = other._tree._size;
		this->_tree._nodes = other._tree._nodes;
		other._tree._size = tmp_size;
		other._tree._nodes = tmp_node;
	}

	void clear()
	{
		if (_tree._size)
			erase(begin(), end());
		_tree._nodes = 0;
	}

	key_compare key_comp() const {return _cmp;}

	class value_compare
	{
		friend class map<K, T, Compare, Allocator>;
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
		protected:
			Compare _c;
			value_compare( Compare c ): _c(c) {}
		public:
			bool operator()(const value_type& lhs, const value_type& rhs ) const {
				return (_c(lhs.first, rhs.first));
			}
	};
	map::value_compare value_comp() const {return value_compare(_cmp);}

	void inorder()
	{
		_tree.inorder();
	}

	iterator 		begin() {
		map_node<const K, T> *it = _tree._nodes;
		while (it && it->left)
			it = it->left;
		return iterator(it, _cmp);
	}
	const_iterator 		begin() const {
		map_node<const K, T> *it = _tree._nodes;
		while (it && it->left)
			it = it->left;
		return iterator(it, _cmp);
	}
	reverse_iterator 		rbegin() {
		map_node<const K, T> *it = _tree._nodes;
		while (it && it->right)
			it = it->right;
		return reverse_iterator(iterator(it, _cmp));
	}
	const reverse_iterator 	rbegin() const {
		map_node<const K, T> *it = _tree._nodes;
		while (it && it->right)
			it = it->right;
		return reverse_iterator(iterator(it, _cmp));
	}
	iterator 			end() {return iterator(0, _cmp);}
	const_iterator 		end() const {return iterator(0, _cmp);}
	reverse_iterator 			rend() {return reverse_iterator(iterator(0, _cmp));}
	const reverse_iterator 		rend() const {return reverse_iterator(iterator(0, _cmp));}

	bool empty() const {return !!!_tree._size;}
	size_type size() const {return _tree._size;}
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

	const_iterator find( const K& key ) const
	{
		const_iterator it = begin();
		while (it != end())
		{
			if (it->first == key)
				return (it);
			it++;
		}
		return (it);		
	}

	size_type erase( const key_type& key )
	{
		map_node<const K, T> *n = _tree.get_node(key);
		if (n == 0)
			return (0);
		_tree.remove_node(n);
		_tree._size--;
		return (1);
	}

	void erase( iterator pos ) {
		erase(pos->first);
	}
	
	void erase( iterator first, iterator last )
	{
		iterator next = first;
		while (next != last)
		{
			next++;
			erase(first->first);
			first = next;
		}
	}
	pair<iterator, bool> insert( const value_type& value )
	{
		size_t old_size = _tree._size;
		iterator i = iterator(_tree.get_add_node(value.first, value.second), _cmp);

		return (pair<iterator, bool>(i, !(old_size == _tree._size)));
	}

	iterator insert( iterator hint, const value_type& value )
	{
		(void)hint;
		iterator i = iterator(_tree.get_add_node(value.first, value.second), _cmp);
		return (i);
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last )
	{
		for(; first != last; first++)
			_tree.get_add_node(first->first, first->second);
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

template <typename K, typename T, typename Compare, typename Allocator>
bool	operator==(const map<K, T, Compare, Allocator> &lhs, const map<K, T, Compare, Allocator> &rhs)
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

template <typename K, typename T, typename Compare, typename Allocator>
bool	operator!=(const map<K, T, Compare, Allocator> &lhs, const map<K, T, Compare, Allocator> &rhs) {return !(lhs == rhs);}

template <typename K, typename T, typename Compare, typename Allocator>
bool operator<(const map<K, T, Compare, Allocator> &lhs, const map<K, T, Compare, Allocator> &rhs)
{
	typedef typename ft::map<K, T>::iterator iterator;

	iterator li = lhs.begin(), le = lhs.end(), ri = rhs.begin(), re = rhs.end();
	for ( ; (li != le) && (ri != re); li++, ri++ ) {
		if (li->first < ri->first || li->second < ri->second) return true;
		if (ri->first < li->first || ri->second < li->second) return false;
	}
	return (li == le) && (ri != re);
}

template <typename K, typename T, typename Compare, typename Allocator>
bool operator>(const map<K, T, Compare, Allocator> &lhs, const map<K, T, Compare, Allocator> &rhs)	{return rhs < lhs;}
template <typename K, typename T, typename Compare, typename Allocator>
bool operator>=(const map<K, T, Compare, Allocator> &lhs, const map<K, T, Compare, Allocator> &rhs) {return !(lhs < rhs);}
template <typename K, typename T, typename Compare, typename Allocator>
bool operator<=(const map<K, T, Compare, Allocator> &lhs, const map<K, T, Compare, Allocator> &rhs) {return !(lhs > rhs);}

template <typename K, typename T, class Compare>
void	swap(ft::map<K, T, Compare> &lhs, ft::map<K, T, Compare> &rhs)
{
	lhs.swap(rhs);
}

}

#endif

