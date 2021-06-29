
#include <ft_pair.hpp>
#include <utility>
#include <iostream>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &out, pair<T1, T2> &v)
{
	out << v.first << " " << v.second;
	return (out);
}


void	pair_test()
{
	pair<int, std::string> p1(10, "hallo?");
	pair<int, std::string> p2(p1);
	pair<int, std::string> p3 = p1;
	pair<int, double> p4;

	std::cout << p1 << std::endl;
	std::cout << p2 << std::endl;
	std::cout << p3 << std::endl;
	std::cout << p4 << std::endl;

}