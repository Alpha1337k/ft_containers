#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <iostream>
#include <ft_node.hpp>

namespace ft
{

template <typename K, typename T, class Compare = std::less<K>, class Allocator = std::allocator<map_node<K,T>> >
class bintree
{
protected:
	Compare _cmp;
	Allocator _alloc;
public:
	size_t	_size;
	map_node<K, T> *_nodes;
	bintree(): _cmp(Compare()), _alloc(Allocator()), _size(0), _nodes(0) {}


	void inorder()
	{
		inorder(_nodes, 0);
	}

	void inorder(map_node<K, T> *trav, int depth = 0)
	{
		if (trav == NULL)
			return;
		inorder(trav->left, depth + 1);
		printf("[%d, %d] ", trav->val.first, depth);
		inorder(trav->right, depth + 1);
	}

	void	update_back(map_node<K, T> *it, map_node<K, T> *replace)
	{
		if (!it->back)
			return;
		if (it->back->left == it)
			it->back->left = replace;
		else
			it->back->right = replace;
	}

	void	remove_node(map_node<K, T> *it)
	{
		if (it == 0)
			return;
		// std::cout << it->val.first << std::endl;
		if (it->left == 0 && it->right == 0)
		{
			update_back(it, 0);
			_alloc.deallocate(it, 1);
		}
		else if (it->left == 0 || it->right == 0)
		{
			map_node<K, T> *tmp;
			if (it->left)
				tmp = it->left;
			else
				tmp = it->right;
			tmp->back = it->back;
			update_back(it, tmp);
			if (it == _nodes)
				_nodes = tmp;
			_alloc.deallocate(it, 1);
		}
		else
		{
			map_node<K, T> *tmp = it->right;
			while (tmp->left)
				tmp = tmp->left;
			if (tmp->right)
				tmp->back->left = tmp->right;
			tmp->back = it->back;
			update_back(it, tmp);
			it->left->back = tmp;
			it->right->back = tmp;
			_alloc.deallocate(it, 1);
		}
	}
	map_node<K, T>	*go_or_create(map_node<K, T> *parent, int dir, K key, T value)
	{
		if (dir == 1)
		{
			if (!parent->right)
			{
				_size++;
				parent->right = _alloc.allocate(1);
				_alloc.construct(parent->right, map_node<K, T>(0, 0, parent, key, value));
			}
			return (parent->right);
		}
		if (!parent->left)
		{
			_size++;
			parent->left = _alloc.allocate(1);
			_alloc.construct(parent->left, map_node<K, T>(0, 0, parent, key, value));
		}
		return (parent->left);
	}
	map_node<K, T>	*get_add_node(K key, T value = T())
	{
		map_node<K, T> *it = _nodes;
		if (_nodes == 0)
		{
			_size++;
			_nodes = _alloc.allocate(1);
			_alloc.construct(_nodes, map_node<K, T>(0, 0, 0, key, value));
			return (_nodes);
		}
		do {
			if (_cmp(it->val.first, key))
				it = go_or_create(it, 1, key, value);
			else if (_cmp(key, it->val.first))
				it = go_or_create(it, 0, key, value);
			else
				break;
		} while (1);
		return (it);
	}
	map_node<K, T>	*get_node(K key)
	{
		map_node<K, T> *it = _nodes;
		while (it != 0)
		{
			if (_cmp(it->val.first, key))
				it = it->right;
			else if (_cmp(key, it->val.first))
				it = it->left;
			else
				break;
		}
		return (it);
	}

};

}

#endif