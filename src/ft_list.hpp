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
	public:
		list(): _begin(0), _end(0),_size(0) {}
		list( const list& other );
		~list() {}
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
		void clear() 
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

				friend std::ostream& operator<<(std::ostream &out, list::iterator & it)
				{
					out << it._pos->data;
					return (out);
				}
		};
		iterator begin()
		{
			return iterator(_begin);
		}
		iterator end()
		{
			return iterator(_end);
		}
	};
}

#endif