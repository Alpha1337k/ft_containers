#include <map>
#include <ft_map.hpp>
#include <iostream>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

template <typename K, typename T, class Compare = std::less<K>>
std::ostream &operator<<(std::ostream &out, map<K, T, Compare> &l)
{
	typedef typename map<K, T, Compare>::iterator iterator;
	for (iterator it = l.begin(); it != l.end(); it++)
		out << it->first << " : " << it->second << std::endl;
	return (out);
}

void	m_create_test(void)
{
	map<char, int> m1;
	m1['a'] = 300;
	m1['b'] = 301;
	m1['c'] = 302;
	m1['d'] = 304;
	map<char, int> m2(m1);
	map<char, int> m3 = m1;
	map<char, int> m4(m1.begin(), m1.find('c'));
	std::cout << "empty: " << m1.empty() << " size: " << m1.size() << std::endl;
	std::cout << "empty: " << m2.empty() << " size: " << m2.size() << std::endl;
	std::cout << "empty: " << m3.empty() << " size: " << m3.size() << std::endl;
	std::cout << "empty: " << m4.empty() << " size: " << m4.size() << std::endl;
	std::cout << m1 << '\n' << m2 << '\n' << m3 << '\n' << m4 << std::endl; 
}


void	map_test()
{
	std::cout << "\t------- Create " << std::endl;
	m_create_test();
}