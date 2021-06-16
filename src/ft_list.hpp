#ifndef FT_LIST_HPP
#define FT_LIST_HPP

#include <iostream>
#include <memory>
#include <iostream>
#include <string>

namespace ft
{
class iterator;

template <typename T>
class list
{
private:
	struct 	s_list_item
	{
		s_list_item *prev;
		s_list_item *next;
		
		T	data;
		s_list_item(s_list_item *p, s_list_item *n, const T &val)
		{
			prev = p;
			next = n;
			data = val;
		}
		s_list_item(s_list_item *p, s_list_item *n)
		{
			prev = p;
			next = n;
		}
	};
	s_list_item *_begin;
	s_list_item *_end;

	size_t _size;
	void	delete_list()
	{
		s_list_item *tmp;
		if (!_begin)
			return ;
		do
		{
			tmp = _begin;
			_begin = _begin->next;
			delete tmp;
		} while (_begin != 0);
		_size = 0;
	}
public:
	list(): _begin(0), _end(0),_size(0) {}
	~list() {delete_list();}
	list( const list& other ) {*this = other;}
	list& operator=( const list& other )
	{
		delete_list();
		s_list_item *tmp = other._begin;
		this->_size = other._size;
		while (tmp && tmp->next)
		{
			push_back(tmp->data);
			tmp = tmp->next;
		}
		return (*this);
	}
	void assign(size_t count, const T& value )
	{
		delete_list();
		for (size_t i = 0; i < count; i++)
			push_back(value);
	}

	template< class InputIt >
	void assign( InputIt first, InputIt last )
	{
		delete_list();
		for (; first != last; first++)
			push_back(*first);
	}

	void push_back( const T& value )
	{
		if (_begin == 0)
		{
			_begin = new s_list_item(0, 0, value);
			_begin->next = new s_list_item(_begin, 0);
			_end = _begin->next;
		}
		else
		{
			_end->data = value;
			_end->next = new s_list_item(_end, 0);
			_end = _end->next;
		}
		_size++;
	}
	void push_front( const T& value )
	{
		if (_begin == 0)
		{
			_begin = new s_list_item(0, 0, value);
			_begin->next = new s_list_item(_begin, 0);
			_end = _begin->next;
		}
		else
		{
			s_list_item *tmp = new s_list_item(0, _begin, value);
			_begin->prev = tmp;
			_begin = tmp;				
		}
		_size++;
	}
	void pop_back()
	{
		if (_size == 0)
			return;
		if (_end->prev == 0)
		{
			delete _end;
			_begin = 0;
			_end = 0;
		}
		else
		{
			_end = _end->prev;
			delete _end->next;
			_end->next = 0;
		}
		_size--;
	}
	void pop_front()
	{
		if (_size == 0)
			return;
		if (_begin->next == 0)
		{
			delete _begin;
			_begin = 0;
			_end = 0;
		}
		else
		{
			_begin = _begin->next;
			delete _begin->prev;
			_begin->prev = 0;
		}
		_size--;
	}

	bool empty() const {return (!!!_size);}
	size_t size() const {return _size;}
	T	&back() 	{return _end->prev->data;}
	T	&front()	{return _begin->data;}
	void clear() { delete_list();}

	class iterator
	{
		private:
			s_list_item *_pos;
		public:
			iterator(s_list_item *position): _pos(position)
			{

			}
			iterator operator++(int)
			{
				_pos = _pos->next;
				return (_pos);
			}
			iterator operator--(int)
			{
				_pos = _pos->prev;
				return (_pos);
			}
			friend bool operator==(const iterator& lhs, const iterator& rhs)
			{
				return (lhs._pos == rhs._pos);
			}
			T	&operator*()
			{
				return (_pos->data);
			}
			friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !(lhs == rhs); }
	};
	iterator begin()
	{
		return iterator(_begin);
	}
	iterator end()
	{
		return iterator(_end);
	}
	iterator begin() const
	{
		return iterator(_begin);
	}
	iterator end() const
	{
		return iterator(_end);
	}
};

template< class T>
bool operator==( const list<T>& lhs, const list<T>& rhs )
{
	// std::cout << "Different sizes? " << lhs.size() << " vs " << rhs.size() << std::endl;
	if (lhs.size() != rhs.size())
		return (false);
	auto li = lhs.begin();
	auto ri = rhs.begin();
	while (li != lhs.end())
	{
		if (*li != *ri)
		{
			return (false);
		}
		li++;
		ri++;
	}
	return (true);
}

template< class T>
bool operator!=( const list<T>& lhs, const list<T>& rhs ) {return !(lhs == rhs);}

}

#endif