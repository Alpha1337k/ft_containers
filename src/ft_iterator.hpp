#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

#include <memory>

namespace ft
{

template< class Iter >
struct iterator_traits
{
	typedef typename Iter::difference_type	difference_type;
	typedef typename Iter::value_type		value_type;
	typedef typename Iter::pointer			pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template< class Iter >
struct iterator_traits<Iter *>
{
	typedef std::ptrdiff_t					difference_type;
	typedef Iter							value_type;
	typedef const Iter*					pointer;
	typedef const Iter&						reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template< class Iter >
class reverse_iterator
{
	private:
		Iter _it;
		typedef iterator_traits<Iter> _traits;
		typedef Iter								iterator_type;
		typedef typename _traits::iterator_category	iterator_category;
		typedef	typename _traits::value_type		value_type;
		typedef typename _traits::difference_type	difference_type;
		typedef	typename _traits::pointer			pointer;
		typedef	typename _traits::reference			reference;
	public:
		reverse_iterator(): _it() {}
		explicit reverse_iterator( iterator_type x ): _it(x) {}
		template< class U >
		reverse_iterator( const reverse_iterator<U>& other ) {*this = other;}

		template< class U >
		reverse_iterator &operator=(const reverse_iterator<U>& other)
		{
			_it = other._it;
			return (*this);
		}

		iterator_type base() const {return _it;}

		reference operator*() const
		{
			Iter tmp = _it;
			return *--tmp;
		}

		pointer operator->() const
		{
			return (std::addressof(operator*()));
		}

		reference operator[]( difference_type n ) const
		{
			return (base()[-n-1]);
		}

		reverse_iterator& operator++()
		{
			--_it;
			return (*this);
		}
		reverse_iterator& operator--()
		{
			++_it;
			return (*this);
		}
		reverse_iterator operator++(int)	
		{
			reverse_iterator tmp = *this; 
			--_it;
			return (tmp);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this; 
			++_it;
			return (tmp);
		}
		reverse_iterator& operator+(difference_type n) const	{return _it -= n;}
		reverse_iterator& operator-(difference_type n) const	{return _it += n;}
		reverse_iterator& operator+=(difference_type n)			{return _it -= n;}
		reverse_iterator& operator-=(difference_type n)			{return _it += n;}
		template< class Iterator1, class Iterator2 >
		friend bool operator==( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ) {return lhs._it == rhs._it;}

		template< class Iterator1, class Iterator2 >
		friend bool operator<( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ) {return lhs._it < rhs._it;}
};

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ) {return !(lhs == rhs);}

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ) {return !(lhs < rhs);}

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ) {return !(rhs < lhs);}


template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ) {return rhs < lhs;}

template< class Iter >
reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
{
	return (reverse_iterator<Iter>(it.base() - n));
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
{
	return (rhs.base() - lhs.base());
}

};

#endif