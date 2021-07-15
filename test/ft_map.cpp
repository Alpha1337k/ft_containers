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
		out << it->first << " : " << it->second << " ";
	return (out);
}

struct ModCmp {
    bool operator()(const int lhs, const int rhs) const
    {
        return (lhs % 97) < (rhs % 97);
    }
};

// so cppreference
void	m_observer_test(void)
{
	typedef typename map<int, char, ModCmp>::value_compare value_compare;

	map<int, char, ModCmp> cont;
	cont[1] = 'a';
	cont[2] = 'b';
	cont[3] = 'c';
	cont[4] = 'd';
	cont[5] = 'e';
	cont[6] = 'f';

	value_compare val_cmp = cont.value_comp();
	ModCmp key_cm = cont.key_comp();

    const pair<int, char> val = { 100, 'a' };

    for (map<int, char, ModCmp>::iterator it = cont.begin(); it != cont.end(); it++) {
        bool before = val_cmp(*it, val);
        bool after = val_cmp(val, *it);
 
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
    for (map<int, char, ModCmp>::iterator it = cont.begin(); it != cont.end(); it++) {
        bool before = key_cm(it->first, 100);
        bool after = key_cm(100, it->first);
 
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
	std::cout << "empty: " << m1.empty() << " size: " << m1.size() << std::endl;
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

void	m_modifiers_test(void)
{
	map<char, int> m1;
	map<char, int> m2;
	map<char, int> m3;
	m1['a'] = 300;
	m1['b'] = 301;
	m1['c'] = 302;
	m1['d'] = 304;
	m1['f'] = 309;
	m2['w'] = 304;
	m2['x'] = 301;
	m2['y'] = 302;
	m2['z'] = 300;

	m3 = m1;
	std::cout << m3 << std::endl;
	std::cout << "empty: " << m3.empty() << " size: " << m3.size() << std::endl;
	m3.clear();
	std::cout << m3 << std::endl;
	std::cout << "empty: " << m3.empty() << " size: " << m3.size() << std::endl;
	m3.insert(m1.begin(), m1.end());
	std::cout << m3 << std::endl;
	std::cout << "empty: " << m3.empty() << " size: " << m3.size() << std::endl;

	pair<map<char, int>::iterator, bool> rv = m1.insert(pair<char, int>('e', 305));
	std::cout << m1 << std::endl;
	std::cout << rv.first->first << " : " << rv.first->second << " : " << rv.second << std::endl;
	rv = m1.insert(pair<char, int>('e', 308));
	std::cout << m1 << std::endl;
	std::cout << rv.first->first << " : " << rv.first->second << " : " << rv.second << std::endl;

	std::cout << m1.erase('d') << std::endl;
	std::cout << m1.erase('d') << std::endl;

	std::cout << m1 << std::endl;
	std::cout << "empty: " << m1.empty() << " size: " << m1.size() << std::endl;
	m1.erase(m1.find('c'));
	std::cout << m1 << std::endl;
	std::cout << "empty: " << m1.empty() << " size: " << m1.size() << std::endl;
	m1.erase(m1.find('d'), m1.end());
	std::cout << m1 << std::endl;
	std::cout << "empty: " << m1.empty() << " size: " << m1.size() << std::endl;
	std::cout << m2 << std::endl;
	m1.swap(m2);
	std::cout << m1 << std::endl;
	std::cout << "empty: " << m1.empty() << " size: " << m1.size() << std::endl;
	std::cout << m2 << std::endl;
	std::cout << "empty: " << m2.empty() << " size: " << m2.size() << std::endl;
	swap(m1, m2);
	std::cout << m1 << std::endl;
	std::cout << "empty: " << m1.empty() << " size: " << m1.size() << std::endl;
	std::cout << m2 << std::endl;
	std::cout << "empty: " << m2.empty() << " size: " << m2.size() << std::endl;
}

void	m_lookup_test(void)
{
	map<char, int> m1;
	m1['a'] = 300;
	m1['b'] = 301;
	m1['c'] = 302;
	m1['d'] = 303;
	m1['e'] = 304;

	std::cout << m1.at('a') << std::endl;
	try
	{
		std::cout << m1.at('z') << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << m1.count('a') << std::endl;
	std::cout << m1.count('b') << std::endl;
	std::cout << m1.count('z') << std::endl;
	std::cout << m1.find('a')->first << std::endl;
	std::cout << m1.find('b')->first << std::endl;
	std::cout << (m1.find('z') == m1.end() ? 0 : 1) << std::endl;

	for (map<char, int>::iterator it = m1.lower_bound('c'); it != m1.end(); it++)
		std::cout << it->first << " : " << it->second << " ";
	std::cout << std::endl;

	for (map<char, int>::iterator it = m1.upper_bound('c'); it != m1.end(); it++)
		std::cout << it->first << " : " << it->second << " ";
	std::cout << std::endl;

	pair<map<char, int>::iterator,map<char, int>::iterator> bound = m1.equal_range('c');
	do
	{
		std::cout << bound.first->first << " : " << bound.first->second << " ";
		bound.first++;
	} while (bound.first != bound.second);
	
	std::cout << std::endl;
}

void	m_compare_test(void)
{
	map<int, int> compare_1;
	map<int, int> compare_2;
	map<int, int> compare_3;
	map<int, int> compare_4;
	map<int, int> compare_5;

	compare_1[3] = 3;
	compare_1[1] = 1;
	compare_1[2] = 2;
	compare_2[1] = 1;
	compare_2[2] = 2;
	compare_2[3] = 3;
	compare_3[3] = 3;
	compare_3[1] = 1;
	compare_4[1] = 1;
	compare_4[2] = 2;
	compare_4[3] = 3;

	std::cout << compare_1 << compare_2 << compare_3 << compare_4 << std::endl;

	std::cout << (compare_1 == compare_2) << (compare_1 != compare_2) << (compare_1 >= compare_2) << (compare_1 <= compare_2)
		<< (compare_1 > compare_2) << (compare_1 < compare_2) << std::endl;
	std::cout << (compare_1 == compare_3) << (compare_1 != compare_3) << (compare_1 >= compare_3) << (compare_1 <= compare_3)
		<< (compare_1 > compare_3) << (compare_1 < compare_3) << std::endl;
	std::cout << (compare_1 == compare_4) << (compare_1 != compare_4) << (compare_1 >= compare_4) << (compare_1 <= compare_4)
		<< (compare_1 > compare_4) << (compare_1 < compare_4) << std::endl;
	std::cout << (compare_2 == compare_3) << (compare_2 != compare_3) << (compare_2 >= compare_3) << (compare_2 <= compare_3)
		<< (compare_2 > compare_3) << (compare_2 < compare_3) << std::endl;
	std::cout << (compare_2 == compare_4) << (compare_2 != compare_4) << (compare_2 >= compare_4) << (compare_2 <= compare_4)
		<< (compare_2 > compare_4) << (compare_2 < compare_4) << std::endl;
	std::cout << (compare_3 == compare_4) << (compare_3 != compare_4) << (compare_3 >= compare_4) << (compare_3 <= compare_4)
		<< (compare_3 > compare_4) << (compare_3 < compare_4) << std::endl;
	std::cout << (compare_3 == compare_5) << (compare_3 != compare_5) << (compare_3 >= compare_5) << (compare_3 <= compare_5)
		<< (compare_3 > compare_5) << (compare_3 < compare_5) << std::endl;	
}

void	map_test()
{
	std::cout << "\t------- Create " << std::endl;
	m_create_test();
	std::cout << "\t------- Lookup " << std::endl;
	m_lookup_test();
	std::cout << "\t------- Modifiers " << std::endl;
	m_modifiers_test();
	std::cout << "\t------- Observers" << std::endl;
	m_observer_test();
	std::cout << "\t------- Compare" << std::endl;
	m_compare_test();
}
