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

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <limits>
#include <iterator>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <ft_enable_if.hpp>
#include <ft_is_integral.hpp>
#include <ft_iterator.hpp>

namespace ft
{

template <typename T, class Allocator = std::allocator<T>>
class vector
{
public:

	class iterator
	{
	public:
		typedef T 					value_type;
		typedef ptrdiff_t 			difference_type;
		typedef size_t 				size_type;
		typedef T&					const_reference;
		typedef T& 					reference;
		typedef typename std::allocator_traits<Allocator>::pointer	pointer;
		typedef	T					iterator_category;
	protected:
		T		*_data;
	public:
		iterator(T *d): _data(d) {}
		iterator &operator=(const iterator &i)
		{
			_data = i._data;
			return (*this);
		}
		~iterator() {};
		iterator& operator++()
		{
			_data++;
			return *this;
		}
		iterator& operator--()
		{
			_data--;
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
		iterator &operator+=(const int &val)
		{
			_data += val;
			return (*this);
		}
		friend iterator operator+(vector<T, Allocator>::iterator lhs, const int &rhs)
		{
			lhs += rhs;
			return (lhs);
		}
		iterator &operator-=(const int &val)
		{
			_data -= val;
			return (*this);
		}
		friend iterator operator-(vector<T, Allocator>::iterator lhs, const int &rhs)
		{
			lhs -= rhs;
			return (lhs);
		}
	
		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
			return (lhs._data == rhs._data);
		}
		friend bool operator!=(const iterator& lhs, const iterator& rhs) {return !(lhs == rhs);}
		const T	&operator*() const
		{
			return (*_data);
		}
		T	&operator*()
		{
			return (*_data);
		}
		T	*operator->()
		{
			return (_data);
		}
	};
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef T&		const_reference;
	typedef T& 		reference;
	typedef	iterator const_iterator;
	//typedef	ft::reverse_iterator<const ft::vector::iterator> const_reverse_iterator;
	typedef	ft::reverse_iterator<iterator> reverse_iterator;
private:
	T *_data;
	size_t _size;
	size_t _capacity;
	Allocator _alloc;

	template< class InputIt >
	size_t distance (InputIt first, InputIt last)
	{
		size_t count = 0;
		for (; first != last; first++, count++);
		return (count);
	}
public:
	vector(): _data(0), _size(0), _capacity(0), _alloc(Allocator()) {}
	~vector() {clear();}
	vector (const vector &other): _data(0), _size(0), _capacity(0), _alloc(Allocator()) {*this = other;}

	explicit vector( size_t count, const T& value = T()): _data(0), _size(0), _capacity(0), _alloc(Allocator())
	{
		resize(count, value);
	}
	vector& operator=( const vector& other )
	{
		reserve(other.size() == 0 ? 1 : other.size() * 2);
		for (size_t i = 0; i < other._size; i++)
			push_back(other._data[i]);

		return *this;
	}

	template< class InputIt>
	vector( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr): 
		_data(0), _size(0), _capacity(0), _alloc(Allocator())
	{
		for (; first != last; first++)
			push_back(*first);
	}

	void assign( size_t count, const T& value )
	{
		clear();
		resize(count, value);
	}

	template< class InputIt>
	void assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr)
	{
		clear();
		for (; first != last; first++)
			push_back(*first);
	}

	bool empty() const {return !!!_size;}
	size_t size() const {return _size;}
	size_t capacity() const {return _capacity;}
	size_t max_size() const {return (std::numeric_limits<ptrdiff_t>::max() / sizeof(T) * 2 + 1);}
	void clear() {
		_alloc.deallocate(_data, _capacity);
		_size = 0;
		_capacity = 0;
		_data = 0;
	}

	T	&back() {return _data[_size == 0 ? 0 : _size - 1];}
	T	&front() {return _data[0];}
	const T&front() const {return _data[0];}
	const T	&back() const {return _data[_size == 0 ? 0 : _size - 1];}
	void push_back( const T& value )
	{
		if (_size >= _capacity)
			reserve(_capacity == 0 ? 1 : _capacity * 2);
		_alloc.construct(&_data[_size], value);
		_size++;
	}
	void pop_back()
	{
		_size--;
	}
	T& operator[](size_t idx)
	{
		return _data[idx];
	}
	const T &operator[]( size_t idx ) const
	{
		return _data[idx];
	}
	void reserve( size_t new_size)
	{
		// std::cout << "New size: " << new_size << std::endl;
		if (new_size <= _capacity)
			return;
		if (new_size > max_size())
			throw std::length_error("vector::reserve");
		T *new_addr = _alloc.allocate(new_size);
		for (size_t i = 0; i < _size; i++)
			_alloc.construct(&new_addr[i], _data[i]);
		_alloc.deallocate(_data, _capacity);
		_data = new_addr;
		_capacity = new_size;
	}
	T& at(size_t pos)
	{
		if (pos >= _size)
			throw std::out_of_range("out of range");
		return (_data[pos]);
	}
	const T& at(size_t pos) const
	{
		if (pos >= _size)
			throw std::out_of_range("out of range");
		return (_data[pos]);
	}
	void resize( size_t count, T value = T() )
	{
		T *new_addr;
		if (count > _capacity)
			new_addr = _alloc.allocate(count);
		else
			new_addr = _data;
		for (size_t i = 0; _data != new_addr && i < count && i < _size; i++)
			new_addr[i] = _data[i];
		for (size_t i = _size; i < count; i++)
			new_addr[i] = value;
		
		if (_data != new_addr)
		{
			_alloc.deallocate(_data, _capacity);
			_capacity = count;
			_data = new_addr;
		}
		_size = count;
	}
	void swap(vector& other)
	{
		T *tmp = this->_data;
		size_t tmp_size = this->_size;
		size_t tmp_capacity = this->_capacity;
		this->_size = other._size;
		this->_capacity = other._capacity;
		this->_data = other._data;
		other._data = tmp;
		other._size = tmp_size;
		other._capacity = tmp_capacity;
	}

	iterator begin()		{return iterator(_data);}
	iterator end()			{return iterator(_data + _size);}	
	iterator begin() const	{return iterator(_data);}
	iterator end()	const	{return iterator(_data + _size);}

	reverse_iterator rbegin()		{return reverse_iterator(_data + _size - 1);}
	reverse_iterator rbegin() const	{return reverse_iterator(_data + _size - 1);}
	reverse_iterator rend()			{return reverse_iterator(_data - 1);}
	reverse_iterator rend() const	{return reverse_iterator(_data - 1);}

	iterator insert( iterator pos, const T& value )
	{
		insert(pos, 1, value);
		return (pos);
	}

	void insert  ( iterator pos, size_t count, const T& value )
	{
		size_t i_pos = 0;
		if (_data != 0)
			i_pos = &*pos - _data;

		if (_size + count > _capacity)
			reserve(_size == 0 ? count : _size * 2);
		for (size_t i = _size + count; i >= i_pos + count; i--)
			_data[i] = _data[i - count];
		for (size_t i = 0; i < count; i++)
			_data[i_pos + i] = value;
		_size += count;
	}

	template< class InputIt>
	void insert( iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = nullptr)
	{	
		size_t i_pos = 0;
		if (_data != 0)
			i_pos = &*pos - _data;
		size_t count = distance(first, last);

		// std::cout << "p--------------------------"<< i_pos << " " << count << " " << _size << std::endl;
		if (_size + count > _capacity)
			reserve(_size == 0 ? count : _size * 2);
		for (size_t i = _size + count; i > i_pos + count; i--)
			_data[i] = _data[i - count];
		size_t x = 0;
		for (InputIt it = first; x < count && it != last; x++, it++)
			_alloc.construct(&_data[x + i_pos], *it);
		_size += count;
	}

	iterator erase(iterator pos )
	{
		size_t i = &*pos - _data + 1;
		for (; i < _size; i++)
			_data[i - 1] = _data[i];
		_size--;
		return (pos);
	}

	iterator erase( iterator first, iterator last )
	{
		size_t i = &*first - _data + 1;
		size_t endi = &*last - _data + 1;

		for (; i < endi; i++)
			first = erase(first);
		return (first);
	}

};

template<class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < rhs.size(); i++)
		if (rhs[i] != lhs[i])
			return (false);
	return (true);
}

template<class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs ) {return !(lhs == rhs);}

template< typename T>
bool operator<(const vector<T> &lhs, const vector<T> &rhs)
{
	size_t l1 = 0, r1 = 0;
	size_t l_size = lhs.size(), r_size = rhs.size();
	for (; l1 < l_size && r1 < r_size; l1++, r1++) {
		if (lhs[l1] < rhs[r1]) return true;
        if (rhs[l1] < lhs[r1]) return false;
	}
	return (l1 == l_size) && (r_size != r1);
}

template< typename T>
bool operator>(const vector<T> &lhs, const vector<T> &rhs) {return rhs < lhs;}
template< typename T>
bool operator>=(const vector<T> &lhs, const vector<T> &rhs) {return !(lhs < rhs);}
template< typename T>
bool operator<=(const vector<T> &lhs, const vector<T> &rhs) {return !(lhs > rhs);}

template< typename T >
void swap( ft::vector<T>& lhs, ft::vector<T>& rhs )
{
	lhs.swap(rhs);
}

}

#endif