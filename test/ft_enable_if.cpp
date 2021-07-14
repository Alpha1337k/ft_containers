#include <ft_enable_if.hpp>
#include <type_traits>
#include <iostream>
#include <ft_is_integral.hpp>

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

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

struct test
{
	enum { int_t, float_t } type;
	template <typename Integer, ft::enable_if_t<ft::is_integral<Integer>::value, bool> = true >
	test(Integer)
	{
		std::cout << "interger!!!" << std::endl;
	}
	template <typename Float, ft::enable_if_t<std::is_floating_point<Float>::value, bool> = true >
	test(Float)
	{
		std::cout << "float!!!" << std::endl;
	}
};


void	enable_if_test()
{
	test(10);
	test(10.10);
}