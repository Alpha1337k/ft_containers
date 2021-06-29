#ifndef FT_LIST_HPP
#define FT_LIST_HPP

#include <iostream>
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>
#include <type_traits>

namespace ft
{

template <typename T>
class list
{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef T&		const_reference;
	typedef T& 		reference;

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
	class iterator
	{
		protected:
		public:
			typedef T value_type;
			s_list_item *_pos;
			iterator(s_list_item *position): _pos(position) {}
			iterator(const iterator &i) {*this = i;}
			iterator &operator=(const iterator &i)
			{
				_pos = i._pos;
				return *this;
			}
			iterator& operator++()
			{
				_pos = _pos->next;
				return *this;
			}
			iterator& operator--()
			{
				_pos = _pos->prev;
				return *this;
			}
			iterator operator++(int)
			{
				iterator old = *this;
				operator++();
				return (old);
			}
			iterator operator--(int)
			{
				iterator old = *this;
				operator--();
				return (old);
			}
			friend bool operator==(const iterator& lhs, const iterator& rhs)
			{
				return (lhs._pos == rhs._pos);
			}
			T	&operator*()
			{
				return (_pos->data);
			}
			T	*operator->()
			{
				return (&_pos->data);
			}
			friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !(lhs == rhs); }
	};
	iterator begin()		{return iterator(_begin);}
	iterator end()			{return iterator(0);}
	iterator begin() const	{return iterator(_begin);}
	iterator end() const	{return iterator(0);}

	typedef iterator const_iterator;
	class reverse_iterator : public iterator
	{
		public:
			reverse_iterator(s_list_item *position): iterator(position) {}
			reverse_iterator &operator++()
			{
				this->_pos = this->_pos->prev;
				return *this;
			}
			reverse_iterator &operator--()
			{
				this->_pos = this->_pos->next;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator old = *this;
				operator++();
				return (old);
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator old = *this;
				operator--();
				return (old);
			}
	};
	
	reverse_iterator rbegin()		{return reverse_iterator(_end);}
	reverse_iterator rbegin() const	{return reverse_iterator(_end);}
	reverse_iterator rend()			{return reverse_iterator(0);}
	reverse_iterator rend() const	{return reverse_iterator(0);}
	
	~list() {delete_list();}
	list(): _begin(0), _end(0),_size(0) {}
	list( const list& other ): _begin(0), _end(0) {*this = other;}
	list& operator=( const list& other )
	{
		delete_list();
		s_list_item *tmp = other._begin;
		this->_size = 0;
		this->_begin = 0;
		this->_end = 0;
		while (tmp)
		{
			push_back(tmp->data);
			tmp = tmp->next;
		}
		return (*this);
	}	
	template< class InputIt >
	list( InputIt first, InputIt last):_begin(0), _end(0), _size(0)
	{
		for (; first != last; first++)
			push_back(*first);
	}
	// explicit list( size_t count, T& value = T()): _begin(0), _end(0), _size(0)
	// {
	// 	for (size_t i = 0; i < count; i++)
	// 		push_back(value);
	// }
	
	void assign(size_t count, const T& value )
	{
		delete_list();
		for (size_t i = 0; i < count; i++)
			push_back(value);
	}

	template< typename InputIt >
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
			_end = _begin;
		}
		else
		{
			_end->next = new s_list_item(_end, 0, value);
			_end = _end->next;
		}
		_size++;
	}
	void push_front( const T& value )
	{
		if (_begin == 0)
		{
			_begin = new s_list_item(0, 0, value);
			_end = _begin;
		}
		else
		{
			_begin->prev = new s_list_item(0, _begin, value);
			_begin = _begin->prev;
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
			_end = 0;
			_begin = 0;
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
	void resize( size_t count, T value = T() )
	{
		if (count > _size)
			for (size_t i = _size; i < count; i++)
				push_back(value);
		else if (count < _size)
			for (size_t i = _size - count; i > 0; i--)
				pop_back();
		_size = count;
	}
	void swap( list& other )
	{
		s_list_item *tmp_begin = other._begin;
		s_list_item *tmp_end = other._end;
		size_t		tmp_size = other._size;

		other._size = this->_size;
		other._begin = this->_begin;
		other._end = this->_end;
		this->_end = tmp_end;
		this->_begin = tmp_begin;
		this->_size = tmp_size;

	}

	bool empty() const {return (!!!_size);}
	size_t size() const {return _size;}
	T	&back() 	{return _end->data;}
	T	&front()	{return _begin->data;}
	void clear() { delete_list();}

	void reverse()
	{
		s_list_item *i = _begin;
		s_list_item *tmp;
		while (i)
		{
			tmp = i->next;
			i->next = i->prev;
			i->prev = tmp;
			i = i->prev;
		}
		tmp = _begin;
		_begin = _end;
		_end = tmp;
	}


	void sort() {sort(std::less<T>());}	
	template< class Compare >
	void sort( Compare comp )
	{
		size_t changes = 0;
		s_list_item *it = _begin;

		do
		{
			changes = 0;
			it = _begin;
			while (it->next)
			{
				if (comp(it->next->data, it->data))
				{
					T tmp = it->data;
					it->data = it->next->data;
					it->next->data = tmp;
					changes++;
				}
				it = it->next;
			}
		} while (changes != 0);
	}

	void merge( list& other ) {merge(other, std::less<T>());}
	template <class Compare>
	void merge( list& other, Compare comp )
	{
		iterator it_this = this->begin();
		iterator it_this_next = this->begin();
		iterator it_other = other.begin();

		it_this_next++;
		do
		{
			if (it_this_next == this->end())
			{
				push_back(*it_other);
				it_other = other.erase(it_other);
			}
			else if (comp(*it_this, *it_other) && !comp(*it_this_next, *it_other))
			{
				insert(it_this_next, *it_other);
				it_other = other.erase(it_other);
			}
			else
			{
				it_this++;
				it_this_next++;
			}
		} while (it_this != this->end() && other.size());
	}

	void unique() {unique(std::equal_to<T>());}
	template< class BinaryPredicate >
	void unique( BinaryPredicate p )
	{
		iterator lc = begin();
		iterator rc = begin();
		rc++;

		if (lc == end())
			return;
		while (rc != end())
		{
			if (p(*rc, *lc))
			{
				lc = erase(lc);
				rc++;
			}
			else
			{
				lc++;
				rc++;
			}
		}
	}

	void remove( const T& value ) 
	{
		iterator it = begin();

		while (it != end())
		{
			if (*it == value)
				it = erase(it);
			else
				it++;
		}
	}
	template< class UnaryPredicate >
	void remove_if( UnaryPredicate p )
	{
		iterator it = begin();

		while (it != this->end())
		{
			if (p(*it))
				it = erase(it);
			else
				it++;
		}
	}

	void splice( iterator pos, list& other )
	{
		insert(pos, other.begin(), other.end(), 0);
		other.erase(other.begin(), other.end());
	}

	void splice( iterator pos, list& other, iterator it )
	{
		insert(pos, 1, *it);
		other.erase(it);
	}

	void splice(iterator pos, list& other, iterator first, iterator last)
	{
		insert(pos, first, last, 0);
		other.erase(first, last);
	}

	iterator erase( iterator pos )
	{
		s_list_item *deref = pos._pos;
		s_list_item *rv;
		if (deref == 0)
			return (pos);
		if (deref->prev)
			deref->prev->next = deref->next;
		else
			_begin = deref->next;
		if (deref->next)
			deref->next->prev = deref->prev;
		else
			_end = deref->prev;
		rv = deref->next;
		delete deref;
		_size--;
		return (iterator(rv));
	}
	iterator erase( iterator first, iterator last )
	{
		do
		{
			first = erase(first);
		} while (first != last);

		return (first);
	}
	iterator insert( iterator pos, const T& value )
	{
		insert(pos, 1, value);
		return (pos);
	}
	void insert( iterator pos, size_t count, const T& value )
	{
		if (pos._pos == 0)
		{
			for (size_t i = 0; i < count; i++)
				push_back(value);
			return;	
		}
		if (pos._pos->prev == 0)
		{
			for (size_t i = 0; i < count; i++)
				push_front(value);
			return;	
		}
		s_list_item *it = pos._pos->prev;
		s_list_item *end = pos._pos;

		for (size_t i = 0; i < count; i++, it = it->next, _size++)
			it->next = new s_list_item(it, end, value);
		end->prev = it;
	}
	template< typename InputIt >
	void insert( iterator pos, InputIt first, InputIt last, int xddd)
	{
		(void)xddd;
		for (; first != last; first++)
			insert(pos, 1, *first);
	}
};

template< typename T>
bool operator==( const list<T>& lhs, const list<T>& rhs )
{
	typedef typename ft::list<T>::iterator iterator;
	if (lhs.size() != rhs.size())
		return (false);
	iterator li = lhs.begin();
	iterator ri = rhs.begin();
	while (li != lhs.end())
	{
		if (*li != *ri)
			return (false);
		li++;
		ri++;
	}
	return (true);
}

template< typename T>
bool operator!=( const list<T>& lhs, const list<T>& rhs ) {return !(lhs == rhs);}

template< typename T>
bool operator<(const list<T> &lhs, const list<T> &rhs)
{
	typedef typename ft::list<T>::iterator iterator;

	iterator l1 = lhs.begin(), l2 = lhs.end(), r1 = rhs.begin(), r2 = rhs.end();
	for ( ; (l1 != l2) && (r1 != r2); ++l1, (void) ++r1 ) {
		if (*l1 < *r1) return true;
        if (*r1 < *l1) return false;
	}
	return (l1 == l2) && (r1 != r2);
}

template< typename T>
bool operator>(const list<T> &lhs, const list<T> &rhs)	{return rhs < lhs;}
template< typename T>
bool operator>=(const list<T> &lhs, const list<T> &rhs) {return !(lhs < rhs);}
template< typename T>
bool operator<=(const list<T> &lhs, const list<T> &rhs) {return !(lhs > rhs);}


template< typename T>
void	swap(ft::list<T> &lhs, ft::list<T> &rhs)
{
	lhs.swap(rhs);
}

}

#endif