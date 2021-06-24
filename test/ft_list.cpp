#include <list>
#include <ft_list.hpp>
#include <iostream>


#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

template <typename T>
std::ostream &operator<<(std::ostream &out, list<T> &l)
{
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		out << *it << " ";
	return (out);
}

void	l_create_test(void)
{
	list<int> l;
	list<int> l_empty;

	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	l.push_back(104);
	l.push_back(105);
	l.push_back(140);
	l.push_back(120);
	l.push_front(0);
	list<int> l_ass = l;
	list<int> l_copy(l);
	list<int> l_list(l.begin(), l.end());
	list<int> l_ass2 = l_empty;
	list<int> l_copy2(l_empty);
	list<int> l_list2(l_empty.begin(), l_empty.end());
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << "empty? " << l_ass.empty() << " size: " << l_ass.size() << std::endl;
	std::cout << "empty? " << l_copy.empty() << " size: " << l_copy.size() << std::endl;
	std::cout << "empty? " << l_list.empty() << " size: " << l_list.size() << std::endl;
	std::cout << "empty? " << l_empty.empty() << " size: " << l_empty.size() << std::endl;
	std::cout << "empty? " << l_ass2.empty() << " size: " << l_ass2.size() << std::endl;
	std::cout << "empty? " << l_copy2.empty() << " size: " << l_copy2.size() << std::endl;
	std::cout << "empty? " << l_list2.empty() << " size: " << l_list2.size() << std::endl;
	std::cout << l << std::endl;
	std::cout << l_ass << std::endl;
	std::cout << l_copy << std::endl;
	std::cout << l_list << std::endl;
	std::cout << l_empty << std::endl;
	std::cout << l_ass2 << std::endl;
	std::cout << l_copy2 << std::endl;
	std::cout << l_list2 << std::endl;
}

void	l_pop_test(void)
{
	list<int> l;
	list<int> l_empty;

	l.push_back(104);
	l.push_back(105);
	l.push_back(140);
	l.push_back(120);
	l.push_front(0);

	l.pop_back();
	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	l.pop_front();
	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
}

void	l_assign_test(void)
{
	list<int> l;

	l.assign(0, 'a');
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.assign(10, 'b');
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.assign(10, 'c');
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.assign(11, 'd');
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.assign(9, 'e');
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.assign(0, 'f');
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	const std::string extra(6, 'x');
	l.assign(extra.begin() + 1, extra.end());
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;
}

void	l_cie_test(void)
{
	list<int> l;

	l.insert(l.begin(), 10);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.insert(l.begin(), 12);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.erase(l.begin());
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.clear();
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	const std::string extra(66, 'x');
#ifdef USE_OS_VARIANT
	l.insert(l.begin(), extra.begin() + 1, extra.end());
#else
	l.insert(l.begin(), extra.begin() + 1, extra.end(), 0);
#endif
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l.erase(l.begin(), l.end());
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;
}

void	l_comp_test(void)
{
	list<int> compare_1;
	list<int> compare_2;
	list<int> compare_3;
	list<int> compare_4;
	list<int> compare_5;

	compare_1.push_back(3);
	compare_1.push_back(1);
	compare_1.push_back(2);
	compare_2.push_back(1);
	compare_2.push_back(2);
	compare_2.push_back(3);
	compare_3.push_back(36);
	compare_3.push_back(32);
	compare_3.push_back(31);
	compare_3.push_back(1);
	compare_4.push_back(1);
	compare_4.push_back(2);
	compare_4.push_back(3);

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

void	list_test(void)
{

	std::cout << "\t------- Create " << std::endl;
	l_create_test();
	std::cout << "\t------- Pop " << std::endl;
	l_pop_test();
	std::cout << "\t------- Assign " << std::endl;
	l_assign_test();
	std::cout << "\t------- Clear, insert, erase " << std::endl;
	l_cie_test();
	std::cout << "\t------- Compare_test " << std::endl;
	l_comp_test();
}