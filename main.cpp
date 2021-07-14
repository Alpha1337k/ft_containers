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

#include <ft_list.hpp>
#include <ft_map.hpp>
#include <ft_vector.hpp>
#include <ft_stack.hpp>
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <map>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

void stack_test();
void list_test();
void map_test();
void vector_test();
void pair_test();
void iterator_test();
void intergral_test();
void enable_if_test();


int main(int argc, char **argv)
{
	map<std::string, void (*)()> test;

	test["STACK"]		= 	&stack_test;
	test["LIST"]		=	&list_test;
	test["MAP"]			= 	&map_test;
	test["VECTOR"]		= 	&vector_test;
	test["PAIR"]		=	&pair_test;
	test["ITERATOR"] 	= 	&iterator_test;
	test["INTEGRAL"] 	= 	&intergral_test;
	test["ENABLE_IF"] 	=	&enable_if_test;

	if (argc > 2)
		return (0);
	else if (argc == 1)
	{
		for (map<std::string, void(*)()>::iterator it = test.begin(); it != test.end(); it++)
		{
			std::cout << "----------- " << it->first << " -----------" << std::endl;
			it->second();
		}
	}
	else if (test.count(argv[1]))
	{
		std::cout << "----------- " << argv[1] << " -----------" << std::endl;
		test[argv[1]]();
	}
}
