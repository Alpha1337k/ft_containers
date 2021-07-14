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
	std::map<int, int> real_mappie;

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
		real_mappie[unsorted.front()] = unsorted.front();
		unsorted.pop();
	}
	size_t failsafe = 0;
	mappie.inorder();
	std::cout << std::endl;
	std::map<int, int>::iterator rit = real_mappie.begin();
	for (ft::map<int, int>::iterator it = mappie.begin(); it != mappie.end() && failsafe != size + 2; it++)
	{
		std::cout << it->first << " " << rit->first << std::endl;
		if (rit ==	real_mappie.end() || rit->first != it->first)
		{
			std::cerr << "KO, they differ!" << std::endl;
			if (rit != real_mappie.end())
				std::cerr << "diff: " << it->first << " " << rit->first << std::endl;
			return;
		}
		rit++;
		failsafe++;
	}
	failsafe = 0;
	std::cout << "----- test 2" << std::endl;
	std::map<int, int>::reverse_iterator rrit = real_mappie.rbegin();
	for (ft::map<int, int>::reverse_iterator it = mappie.rbegin(); it != mappie.rend() && failsafe != size + 2; ++it)
	{
		std::cout << it->first << " " << rrit->first << std::endl;
		if (rrit ==	real_mappie.rend() || rrit->first != it->first)
		{
			std::cerr << "KO, they differ!" << std::endl;
			if (rrit != real_mappie.rend())
				std::cerr << "diff: " << it->first << " " << rrit->first << std::endl;
			return;
		}
		rrit++;
		failsafe++;
	}
	std::cerr << "OK" << std::endl;
}

int		main()
{
	size_t size = 10;
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		run_test(size);
	}
	return 0;
}