#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <ft_vector.hpp>

namespace ft
{

template <typename T, typename Container = ft::vector<T>>
class stack
{
public:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;
protected:
	typedef stack<T, Container> _this_c;

	container_type _c;
public:
	stack( const container_type& cont = container_type()): _c(cont) {}
	stack( const _this_c& other ): _c(other._c) {}
	~stack() {};
	_this_c &operator=(const _this_c &s)
	{
		this->_c = s._c;
		return (*this);
	}

	value_type &top() {return (_c.back());}
	const value_type &top() const {return (_c.back());}
	bool empty() const {return _c.empty();}
	size_t size() const {return _c.size();}
	void push( const T& value ) {_c.push_back(value);}
	void pop() {_c.pop_back();}
	void swap( stack& other )
	{
		Container tmp = other._c;
		other._c = this->_c;
		this->_c = tmp;
	}

	template <typename T1, typename Container1>
	friend bool operator==( const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs );
	template <typename T1, typename Container1>
	friend bool operator<( const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs );
};

template <typename T, typename Container>
bool operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c == rhs._c;}

template <typename T, typename Container>
bool operator!=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return !(lhs == rhs);}

template <typename T, typename Container>
bool operator>=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return !(lhs < rhs);}

template <typename T, typename Container>
bool operator<=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return !(rhs < lhs);}

template <typename T, typename Container>
bool operator>( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return rhs < lhs;}

template <typename T, typename Container>
bool operator<( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c < rhs._c;}


}

#endif