#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

template <typename T1, typename T2>
struct pair
{
	T1 first;
	T2 second;
	pair(): first(T1()), second(T2()) {}

	template< class U1, class U2 >
	pair( const pair<U1, U2>& p ): first(p.first), second(p.second) {} 

	pair(const T1 &v1, const T2 &v2): first(v1), second(v2) {}

	pair( const pair& p ) = default;
	pair& operator=( const pair& other ) {
		first = other.first;
		second = other.second;
		return (*this);
	}
};

template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
{
	if (lhs.first != rhs.first || lhs.second != lhs.second)
		return (false);
	return (true);
}

template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return !(lhs == rhs);}

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
{
	if (lhs.first < rhs.first == false || lhs.second < rhs.second == false)
		return (false);
	return (true);
}

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return !(lhs > rhs);}
template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return !(lhs < rhs);}
template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return rhs < lhs;}

template< class T1, class T2 >
ft::pair<T1,T2> make_pair( T1 t, T2 u )
{
	return (ft::pair<T1, T2>(t, u));
}

}

#endif