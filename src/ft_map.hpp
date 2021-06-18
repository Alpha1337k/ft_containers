#ifndef FT_MAP_HPP
#define FT_MAP_HPP

namespace ft
{
template <typename K, typename T>
class map
{
private:
	struct map_node
	{
		map_node *left;
		map_node *right;
		map_node *back;
		bool isred;
		T	value;
		const K	key;
		map_node(map_node *l, map_node *r, map_node *b, T val, const K &k): key(k)
		{
			left = l;
			right = r;
			back = b;
			value = val;
			if (back)
				isred = !back->isred;
			else
				isred = true;
		}
	};
	map_node *_nodes;
	size_t	_size;
	map_node *find_or_create(const K &key)
	{
		map_node *it = _nodes;
		while (it)
		{
			// std::cout << "entering new tree: " << it->key << std::endl;
			if (it->key == key)
				return (it);
			if (it->left && it->right->key < key)
				it = it->left;
			else if (it->right)
				it = it->right;
			else
			{
				_size++;
				if (it->key < key)
				{
					it->right = new map_node(0, 0, it, T(), key);
					return (it->right);
				}
				else
				{
					it->left = new map_node(0, 0, it, T(), key);
					return (it->left);
				}
			}
		}
		_nodes = new map_node(0, 0, 0, T(), key);
		_size++;
		// std::cout << "Created new node! " << std::endl;
		return (_nodes);
	}
public:
	map(): _nodes(0), _size(0) {}
	~map() {}
	map(const map &m): _nodes(0), _size(0) {*this = m;}

	map	&operator=(const map &m)
	{
		this->_size = m._size;
	}
	T& operator[](const K &key)
	{
		return (find_or_create(key)->value);
	}
	bool empty() const {return !!!_size;}
	size_t size() const {return _size;}

};


}

#endif