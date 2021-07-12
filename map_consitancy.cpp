#include <vector>
#include <map>
#include <ft_map.hpp>
#include <iostream>
#include <random>
#include <queue>

void	run_test(size_t size)
{
	std::vector<int> sorted;
	std::queue<int>	unsorted;
	ft::map<int, int> mappie;

	for (size_t i = 0; i < size; i++)
		sorted.push_back(i);
	for (size_t i = 0; i < size; i++)
	{
		size_t indx = rand() % sorted.size();
		unsorted.push(sorted[indx]);
		sorted.erase(sorted.begin() + indx);
	}
	for (; !unsorted.empty(); )
	{
		mappie[unsorted.front()] = unsorted.front();
		unsorted.pop();
	}
	size_t failsafe = 0;
	mappie.inorder();
	std::cout << std::endl;
	for (ft::map<int, int>::iterator it = mappie.begin(); it != mappie.end() && failsafe != size + 2; it++)
	{
		std::cout << it->first << " ";
		failsafe++;
	}
	std::cout << std::endl << std::endl;
}

int		main()
{
	size_t size = 10;
	srand(time(NULL));
	for (int i = 0; i < 1; i++)
	{
		run_test(size);
	}
	return 0;
}