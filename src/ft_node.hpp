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

#ifndef NODE_HPP
#define NODE_HPP

#include <ft_pair.hpp>

template <typename K, typename T>
struct map_node
{
	map_node *left;
	map_node *right;
	map_node *back;
	ft::pair<const K, T> val;
	map_node(map_node *l, map_node *r, map_node *b, const K &k, T &val): val(k, val)
	{
		left = l;
		right = r;
		back = b;
	}
	map_node(const map_node &other): val(other.val) {*this = other;}
	map_node &operator=(const map_node &other)
	{
		this->left = other.left;
		this->right = other.right;
		this->back = other.back;

		return *this;
	}
};

#endif
