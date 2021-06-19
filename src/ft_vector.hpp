#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <limits>
#include <iterator>

namespace ft
{

template <typename T>
class vector
{
private:
	T *_data;
	size_t _size;
	size_t _capacity;

	template< class InputIt >
	size_t distance (InputIt first, InputIt last)
	{
		size_t count = 0;
		for (; first != last; first++, last++, count++);
		return (count);
	}
public:
	vector(): _data(0), _size(0), _capacity(0) {}
	~vector() {delete[] _data;}
	vector (const vector &other): _data(0), _size(0), _capacity(0) {*this = other;}
	explicit vector( size_t count, const T& value = T()): _data(0), _size(0), _capacity(0)
	{
		resize(count, value);
	}
	vector& operator=( const vector& other )
	{
		reserve(other.size() * 2);
		for (size_t i = 0; i < other._size; i++)
			push_back(other._data[i]);

		return *this;
	}
	// template< class InputIt >
	// vector( InputIt first, InputIt last): _data(0), _size(0), _capacity(0)
	// {
	// 	for (; first != last; first++)
	// 		push_back(*first);
	// }

	void assign( size_t count, const T& value )
	{
		resize(count, value);
	}

	// template< class InputIt >
	// void assign( InputIt first, InputIt last )
	// {

	// }

	bool empty() const {return !!!_size;}
	size_t size() const {return _size;}
	size_t capacity() const {return _capacity;}
	size_t max_size() const {return (std::numeric_limits<T>::max() / sizeof(T));}

	T	&back() {return _data[_size == 0 ? 0 : _size - 1];}
	T	&front() {return _data[0];}
	void push_back( const T& value )
	{
		if (_size >= _capacity)
			reserve(_capacity * 2);
		_data[_size++] = value;
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
		if (new_size < _capacity)
			return;
		if (new_size == 0 && _capacity == 0)
			new_size++;
		T *new_addr = new T[new_size];
		for (size_t i = 0; i < _size; i++)
			new_addr[i] = _data[i];
		delete[] _data;
		_data = new_addr;
		_capacity = new_size;
	}
	T& at(size_t pos)
	{
		if (pos >= _size)
			throw std::out_of_range("out of range");
		return (_data[pos]);
	}
	void resize( size_t count, T value = T() )
	{
		T *new_addr = new T[count];
		for (size_t i = 0; i < count && i < _size; i++)
			new_addr[i] = _data[i];
		for (size_t i = _size; i < count; i++)
			new_addr[i] = value;
		delete[] _data;
		_capacity = count;
		_size = count;
		_data = new_addr;
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
	class iterator
	{
	protected:
		T		*_data;
	public:
		iterator(T *d): _data(d) {}
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
		friend iterator operator+(iterator lhs, const int &rhs)
		{
			lhs += rhs;
			return (lhs);
		}
		iterator &operator-=(const int &val)
		{
			_data -= val;
			return (*this);
		}
		friend iterator operator-(iterator lhs, const int &rhs)
		{
			lhs -= rhs;
			return (lhs);
		}
		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
			return (lhs._data == rhs._data);
		}
		friend bool operator!=(const iterator& lhs, const iterator& rhs) {return !(lhs == rhs);}
		T	&operator*()
		{
			return (*_data);
		}
	};
	iterator begin()		{return iterator(_data);}
	iterator end()			{return iterator(_data + _size);}	
	iterator begin() const	{return iterator(_data);}
	iterator end()	const	{return iterator(_data + _size);}
	class reverse_iterator : public iterator
	{
	public:
		reverse_iterator(T *d): iterator(d) {}
		reverse_iterator operator++(int)
		{
			this->_data--;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			this->_data++;
			return (*this);
		}
	};
	reverse_iterator rbegin()		{return reverse_iterator(_data + _size - 1);}
	reverse_iterator rbegin() const	{return reverse_iterator(_data + _size - 1);}
	reverse_iterator rend()			{return reverse_iterator(_data - 1);}
	reverse_iterator rend() const	{return reverse_iterator(_data - 1);}

	iterator insert( iterator pos, const T& value )
	{
		insert(pos, 1, value);
		return (pos);
	}

	void insert( iterator pos, size_t count, const T& value )
	{
		size_t i = &*pos - _data;
		size_t x = _size + count;

		reserve(_size + count);
		for (; x >= i + count; x--)
			_data[x] = _data[x - count];
		for (x = 0; x < count; x++)
			_data[x + i] = value;
		_size += count;
	}

	// template< class InputIt, class T != int>
	// void insert( iterator pos, InputIt first, InputIt last)
	// {
	// 	size_t i = &*pos - _data;
	// 	size_t count = distance(first, last);
		
	// 	size_t x = _size + count;

	// 	reserve(_size + count);
	// 	for (; x >= i + count; x--)
	// 		_data[x] = _data[x - count];
	// 	x = 0;
	// 	for (InputIt it = first; x < count; x++, it++)
	// 		_data[x + i] = *it;
	// 	_size += count;
	// }
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
		{
			first = erase(first);
		}
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
bool operator>(const vector<T> &lhs, const vector<T> &rhs)
{
	size_t l1 = 0, r1 = 0;
	size_t l_size = lhs.size(), r_size = rhs.size();
	for (; l1 < l_size && r1 < r_size; l1++, r1++)  {
		if (lhs[l1] < rhs[r1]) return false;
        if (rhs[l1] < lhs[r1]) return true;
	}
	return (l1 != l_size) && (r_size == r1);
}

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