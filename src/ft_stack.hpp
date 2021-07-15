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

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <ft_vector.hpp>

namespace ft
{

template <typename T, typename Container = ft::vector<T>>
class stack
{
public:
	typedef Container container_type;
	typedef typename Container::value_type			value_type;
	typedef typename Container::size_type			size_type;
	typedef typename Container::reference			reference;
	typedef	typename Container::const_reference		const_reference;
protected:
	typedef stack<T, Container> _this_c;

	container_type c;
public:
	stack( const container_type& cont = container_type()): c(cont) {}
	stack( const _this_c& other ): c(other.c) {}
	~stack() {};
	_this_c &operator=(const _this_c &s)
	{
		this->c = s.c;
		return (*this);
	}

	value_type &top() {return (c.back());}
	const_reference &top() const {return (c.back());}
	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	void push( const value_type& value ) {c.push_back(value);}
	void pop() {c.pop_back();}

	template <typename T1, typename Container1>
	friend bool operator==( const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs );
	template <typename T1, typename Container1>
	friend bool operator<( const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs );
};

template <typename T, typename Container>
bool operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs.c == rhs.c;}

template <typename T, typename Container>
bool operator!=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return !(lhs == rhs);}

template <typename T, typename Container>
bool operator>=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return !(lhs < rhs);}

template <typename T, typename Container>
bool operator<=( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return !(rhs < lhs);}

template <typename T, typename Container>
bool operator>( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return rhs < lhs;}

template <typename T, typename Container>
bool operator<( const stack<T, Container>& lhs, const stack<T, Container>& rhs ) {return lhs.c < rhs.c;}

}

#endif