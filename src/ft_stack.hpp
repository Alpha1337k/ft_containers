#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <deque>

namespace ft
{

template <typename T, typename Container = std::deque<T>>
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
	explicit stack( const container_type& cont = container_type()): _c(cont) {}
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
	void swap( stack& other ) {std::swap(_c, other);}
};

template <typename T, typename Container>
bool operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c == rhs._c;}

template <typename T, typename Container>
bool operator!=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c != rhs._c;}

template <typename T, typename Container>
bool operator>=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c >= rhs._c;}

template <typename T, typename Container>
bool operator<=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c <= rhs._c;}

template <typename T, typename Container>
bool operator>( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c > rhs._c;}

template <typename T, typename Container>
bool operator<( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs._c < rhs._c;}


}

#endif