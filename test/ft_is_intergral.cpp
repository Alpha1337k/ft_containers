#include <type_traits>
#include <ft_is_integral.hpp>
#include <iostream>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

class A {};
enum B : int {};

template< class T >
std::string	integral_bool(void)
{
	if (is_integral<T>())
		return ("true");
	return "false";
}

void	intergral_test(void)
{
	// std::cout << is_integral<A>::value			<< '\n';
    // std::cout << is_integral_v<B> 				<< '\n';
    // std::cout << is_integral_v<float>			<< '\n';
    // std::cout << is_integral_v<int>				<< '\n';
    // std::cout << is_integral_v<const int>		<< '\n';
    // std::cout << is_integral_v<bool>			<< '\n';

    std::cout << std::is_integral<A>::value << '\n';
    std::cout << integral_bool<B>() << '\n';
    std::cout << integral_bool<float>() << '\n';
    std::cout << integral_bool<int>() << '\n';
    std::cout << integral_bool<const int>() << '\n';
    std::cout << integral_bool<bool>() << '\n';
}

