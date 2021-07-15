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

#ifndef FT_QUEUE_HPP
#define FT_QUEUE_HPP

#include <deque>

namespace ft
{

template <typename T, typename Container = std::deque<T> >
class queue
{
public:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;
protected:
	typedef queue<T, Container> _this_c;
	
	container_type _c;
public:
	explicit queue( const Container& cont = Container() ): _c(cont) {}
	queue( const _this_c& other ): _c(other._c) {}
	queue& operator=( const queue& other ) {_c = other._c;}
	~queue();

	value_type &front() {return _c.front();}
	const value_type &front() const {return _c.front();}

	value_type &back() {return _c.back();}
	const value_type &back() const {return _c.back();}

	bool empty() const {return _c.empty();}
	size_type size() const {_c.size();}

	void push(const value_type &value) { _c.push_back(value);}
	void pop() {_c.pop();}
};

template< class T, class Container >
bool operator==( const queue<T,Container>& lhs, const queue<T,Container>& rhs ) {return lhs._c == rhs._c;}

template< class T, class Container >
bool operator!=( const queue<T,Container>& lhs, const queue<T,Container>& rhs ) {return lhs._c != rhs._c;}

template< class T, class Container >
bool operator<( const queue<T,Container>& lhs, const queue<T,Container>& rhs ) {return lhs._c < rhs._c;}

template< class T, class Container >
bool operator<=( const queue<T,Container>& lhs, const queue<T,Container>& rhs ) {return lhs._c <= rhs._c;}

template< class T, class Container >
bool operator>( const queue<T,Container>& lhs, const queue<T,Container>& rhs ) {return lhs._c >= rhs._c;}

template< class T, class Container >
bool operator>=( const queue<T,Container>& lhs, const queue<T,Container>& rhs ) {return lhs._c >= rhs._c;}

}

#endif