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

#include <ft_is_integral.hpp>
#include <iostream>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

class A {};

template< class T >
std::string	integral_bool(void)
{
	if (ft::is_integral<T>())
		return ("true");
	return "false";
}

void	intergral_test(void)
{
    std::cout << ft::is_integral<A>::value << '\n';
    std::cout << integral_bool<float>() << '\n';
    std::cout << integral_bool<int>() << '\n';
    std::cout << integral_bool<const int>() << '\n';
    std::cout << integral_bool<bool>() << '\n';
}

