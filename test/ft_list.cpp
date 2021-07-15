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

	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l.back() << std::endl;
	l.pop_back();
	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l.front() << std::endl;
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
	list<int> copy;

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
	l.insert(l.begin(), extra.begin() + 1, extra.end());
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	copy = l;
	l.erase(l.begin(), l.end());
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;

	l = copy;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;
	l.resize(20, 88);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;
	l.resize(21, 89);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;
	l.resize(0, 89);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;
	l.resize(5);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << l << std::endl;
}

void	l_op_test(void)
{
	list<int> l;
	list<int> lb;

	l.insert(l.begin(), 10, 666);
	lb.insert(lb.begin(), 10, 777);

	l.swap(lb);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << "empty? " << lb.empty() << " size: " << lb.size() << std::endl;
	std::cout << l << std::endl;
	std::cout << lb << std::endl;

	l.clear();
	lb.clear();

	for (size_t i = 0; i < 100; i += 2)
		l.push_back(i);
	for (size_t i = 1; i < 100; i += 2)
		lb.push_back(i);

	l.merge(lb);
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << "empty? " << lb.empty() << " size: " << lb.size() << std::endl;
	std::cout << l << std::endl;
	std::cout << lb << std::endl;
	l.reverse();
	std::cout << l << std::endl;
	for (size_t i = 1; i < 100; i += 2)
		lb.push_back(i);
	l.reverse();
	l.merge(lb);
	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	l.unique();
	std::cout << l << std::endl;
	std::cout << "remove::empty? " << l.empty() << " size: " << l.size() << std::endl;
	l.remove(22);
	l.remove(101);
	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::swap(l, lb);
	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << " size: " << l.size() << std::endl;
	std::cout << lb << std::endl;
	std::cout << "empty? " << lb.empty() << " size: " << lb.size() << std::endl;
}

class OBJ
{
	public:
		OBJ() {}
		std::string print() {return ("printin!!");}
};

void	l_iterator_test(void)
{
	list<int> l;
	list<OBJ> l1;
	
	l.push_back(3);
	l.push_back(1);
	l.push_back(2);
	l.push_back(4);
	l.push_back(6);
	l.push_back(8);

	l1.push_back(OBJ());
	const list<int> l2(l);

	list<int>::iterator it = l.begin();
	list<OBJ>::iterator it2 = l1.begin();
	std::cout << *it << std::endl;
	std::cout << it2->print() << std::endl;
	for (list<int>::reverse_iterator itr = l.rbegin(); itr != l.rend(); ++itr)
		std::cout << *itr << " ";
	std::cout << std::endl;
	for (list<int>::reverse_iterator itr = l.rbegin(); itr != l.rend(); itr++)
	{
		std::cout << *itr++ << " ";
		if (itr == l.rend())
			break;
		--itr;
	}
	std::cout << std::endl;
	for (list<int>::const_iterator itr = l2.begin(); itr != l2.end(); itr++)
		std::cout << *itr << " ";
	std::cout << std::endl;

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
	std::cout << "\t------- Pop, back, front" << std::endl;
	l_pop_test();
	std::cout << "\t------- Assign " << std::endl;
	l_assign_test();
	std::cout << "\t------- Iterators " << std::endl;
	l_iterator_test();
	std::cout << "\t------- Clear, insert, erase, resize " << std::endl;
	l_cie_test();
	std::cout << "\t------- Operations, swap " << std::endl;
	l_op_test();
	std::cout << "\t------- Compare_test " << std::endl;
	l_comp_test();
}
