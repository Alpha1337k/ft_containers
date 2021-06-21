#include <iostream>


struct map_node
{
	map_node *left;
	map_node *right;
	map_node *back;
	bool isred;
	int	value;
	const int	key;
	map_node(map_node *l, map_node *r, map_node *b, int val, const int &k): key(k)
	{
		left = l;
		right = r;
		back = b;
		value = val;
		if (!b)
			isred = false;
		else
			isred = true;
	}
};

map_node *nodes = 0;

map_node	*go_or_create(map_node *parent, int dir, int key)
{
	if (dir == 1)
	{
		if (!parent->right)
			parent->right = new map_node(0, 0, parent, key, key);
		return (parent->right);
	}
	if (!parent->left)
		parent->left = new map_node(0, 0, parent, key, key);
	return (parent->left);

}

void rr(map_node* parent)
{
    map_node* left = parent->left;
    parent->left = left->right;
    if (parent->left)
        parent->left->back = parent;
    left->back = parent->back;
    if (!parent->back) // set new root if needed
        nodes = left;
    else if (parent == parent->back->left)
        parent->back->left = left;
    else
        parent->back->right = left;
    left->right = parent;
    parent->back = left;
}

void rl(map_node* parent)
{
    map_node* right = parent->right;
    parent->right = right->left;
    if (parent->right)
        parent->right->back = parent;
    right->back = parent->back;
    if (!parent->back)
        nodes = right;
    else if (parent == parent->back->left)
        parent->back->left = right;
    else
        parent->back->right = right;
    right->left = parent;
    parent->back = right;
}

void		rebalance_tree(map_node *it)
{
	map_node *grand_parent = 0, *parent = 0, *uncle = 0;

	while (it != nodes && it->isred && it->back->isred)
	{
		parent = it->back;
		grand_parent = it->back->back;

		if (parent == grand_parent->left)
		{
			uncle = grand_parent->right;
			if (uncle && uncle->isred)
			{
				grand_parent->isred = 1;
				parent->isred = 0;
				uncle->isred = 0;
				it = grand_parent;
			}
			else
			{
				if (it == parent->right)
				{
					rl(parent);
					it = parent;
					parent = parent->back;
				}
				rr(grand_parent);
				bool tmp_color = parent->isred;
				parent->isred = grand_parent->isred;
				grand_parent->isred = tmp_color;
				it = parent;
			}
		}
		else
		{
			uncle = grand_parent->left;
			if (uncle && uncle->isred)
			{
				grand_parent->isred = 1;
				parent->isred = 0;
				uncle->isred = 0;
				it = grand_parent;
			}
			else
			{
				if (it == parent->left)
				{
					rr(parent);
					it = parent;
					parent = parent->back;
				}
				rl(grand_parent);
				bool tmp_color = parent->isred;
				parent->isred = grand_parent->isred;
				grand_parent->isred = tmp_color;
				it = parent;
			}
		}


	}
	nodes->isred = 0;
}

void inorder(map_node* trav, int depth = 0)
{
    if (trav == NULL)
        return;
    inorder(trav->left, depth + 1);
    printf("[%d, %d, %d] ", trav->key, depth, trav->isred);
    inorder(trav->right, depth + 1);
}

map_node	*get_add_node(int key)
{
	map_node *it = nodes;
	if (nodes == 0)
		nodes = new map_node(0, 0, 0, key, key);
	else
	{
		do {
		if (key == it->key)
			break;
		if (key > it->key)
			it = go_or_create(it, 1, key);
		if (key < it->key)
			it = go_or_create(it, 0, key);
		} while (1);
		rebalance_tree(it);
	}
	return (nodes);
}

class iterator
{
private:
	map_node *_pos;
	map_node *_origin;
	int status = 0;
public:
	iterator(map_node *pos): _pos(pos), _origin(pos) {}
	~iterator() {}
	iterator operator++(int)
	{
		std::cout << _pos << std::endl;
		if (_pos->left && _pos != nodes)
		{
			status = 0;
			_pos = _pos->left;
		}
		else if (_pos->right)
		{
			status = 1;
			_pos = _pos->right;
		}
		else if (status == 1 && _pos->left == 0 && _pos->right == 0)
		{
			status = 2;
			do {
				_origin = _pos;
				_pos = _pos->back;
			} while (_pos && _pos->right == _origin);
			status = 0;
		}

		return *this;
	}
	int	&operator*()
	{
		return (_pos->value);
	}
	friend bool operator==(const iterator& lhs, const iterator& rhs)
	{
		return (lhs._pos == rhs._pos);
	}
	friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !(lhs == rhs); }

};



int main()
{
	get_add_node(3);
	get_add_node(21);
	get_add_node(32);
	get_add_node(17);
	get_add_node(33);

	inorder(nodes);
	map_node *it = nodes;
	while (it->left)
		it = it->left;
	iterator i = iterator(it);
	iterator end = iterator(0);
	std::cout << "\n" << std::endl;
	for(; i != end; i++)
	{
		std::cout << *i << std::endl;
	}
}
