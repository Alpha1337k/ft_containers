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

struct ModCmp {
    bool operator()(const int lhs, const int rhs) const
    {
        return (lhs % 97) < (rhs % 97);
    }
};

void	m_value_comp_test(void)
{
	typedef typename map<int, char, ModCmp>::value_compare value_compare;

	map<int, char, ModCmp> cont;
	cont[1] = 'a';
	cont[2] = 'b';
	cont[3] = 'c';
	cont[4] = 'd';
	cont[5] = 'e';
	cont[6] = 'f';

	value_compare to_cmp = cont.value_comp();
    const std::pair<int, char> val = { 100, 'a' };

    for (map<int, char, ModCmp>::iterator it = cont.begin(); it != cont.end(); it++) {
        bool before = to_cmp(*it, val);
        bool after = to_cmp(val, *it);
 
        std::cout << '(' << it->first << ',' << it->second;
        if (!before && !after)
            std::cout << ") equivalent to key " << val.first << '\n';
        else if (before)
            std::cout << ") goes before key " << val.first << '\n';
        else if (after)
            std::cout << ") goes after key " << val.first << '\n';
        else
            std::cout << "idk" << std::endl;
    }	

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
	std::cout << "Done!" << std::endl;
}

void	m_insert_test(void)
{
	map<char, int> m1;
	m1['a'] = 300;
	m1['b'] = 301;
	m1['c'] = 302;
	m1['d'] = 304;

	std::pair<map<char, int>::iterator, bool> rv = m1.insert(std::pair<char, int>('e', 305));
	std::cout << rv.first->first << " : " << rv.first->second << " : " << rv.second << std::endl;
	rv = m1.insert(std::pair<char, int>('e', 308));
	std::cout << rv.first->first << " : " << rv.first->second << " : " << rv.second << std::endl;
}


void	map_test()
{
	std::cout << "\t------- Create " << std::endl;
	m_create_test();
	std::cout << "\t------- Insert " << std::endl;
	m_insert_test();
}