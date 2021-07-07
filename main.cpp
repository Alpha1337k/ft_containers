
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

template <typename T>
std::ostream &operator<<(std::ostream &out, list<T> &l)
{
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		out << *it << " ";
	return (out);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, vector<T> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	return (out);
}

void	list_test_depr()
{
	list<int> l;

	std::cout << "empty? " << l.empty() << std::endl;
	l.push_back(10);
	l.push_back(11);
	l.push_back(12);
	l.push_front(0);
	list<int> l_ass = l;
	list<int> l_copy(l);
	list<int> l_list(l.begin(), l.end());
	// list<int> l_count(10, 0);

	std::cout << "size: " << l.size() << " | " << l_ass.size() << " | "<< l_copy.size() << " | " << l_list.size() << std::endl;
	std::cout << l << std::endl;
	l.reverse();
	std::cout << l << std::endl;
	l.pop_back();
	l.pop_front();
	std::cout << l << std::endl;
	std::cout << "empty? " << l.empty() << std::endl;
	std::cout << "back: " << l.back() << std::endl;
	std::cout << "front: " << l.front() << std::endl;
	std::cout << "clearing.." << std::endl;
	l.clear();
	std::cout << "empty? " << l.empty() << std::endl;
	std::cout << "clearing.." << std::endl;
	l.clear();
	std::cout << "empty? " << l.empty() << std::endl;
	std::cout << l << std::endl;
	std::cout << l_copy << std::endl;
	std::cout << l_ass << std::endl;
	std::cout << l_list << std::endl;

	l.assign(5, 'a');
	std::cout << l << std::endl;

    const std::string extra(6, 'b');
    l.assign(extra.begin(), extra.end());
	std::cout << l << std::endl;

	std::cout << "are l and l_copy the same???\t" << (bool)(l == l_ass) << std::endl;
	std::cout << "are l_ass and l_copy the same???\t" << (bool)(l_ass == l_copy) << std::endl;
	for (list<int>::reverse_iterator it = l_copy.rbegin(); it != l_copy.rend(); it++)
		std::cout << *it << " ";
	std::cout << "\n";

	l.resize(10);
	std::cout << "new size:" << l.size() << std::endl;
	std::cout << l << std::endl;
	l.resize(2);
	std::cout << "new size:" << l.size() << std::endl;
	std::cout << l << std::endl;

	l.resize(0);
	std::cout << "new size:" << l.size() << std::endl;
	std::cout << l << std::endl;

	l.swap(l_copy);
	std::cout << "new size:" << l.size() << " | " << l_copy.size() << std::endl;
	std::cout << l << std::endl;

	l.push_back(22);
	l.push_back(-10);
	l.push_back(9);
	l.push_back(22);
	l.push_back(-10);
	l.push_back(9);

	l.sort();
	std::cout << l << std::endl;
	l.sort(std::greater<int>());
	std::cout << l << std::endl;
	l.unique();
	std::cout << l << std::endl;
	l.push_back(22);
	l.push_back(-10);
	l.push_back(9);
	std::cout << l << std::endl;
	l.unique(std::not_equal_to<int>());
	std::cout << l << std::endl;
	l.unique();
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << " start: " << l.front() << "end: " << l.back() <<std::endl;
	l.push_back(22);
	l.push_back(-10);
	l.push_back(9);
	l.push_back(22);
	l.push_back(10);
	l.push_back(9);
	l.push_back(8);

	list<int> compare_1;
	list<int> compare_2;
	list<int> compare_3;
	list<int> compare_4;

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
	std::cout << "new size:" << l.size() << " start: " << l.front() << "end: " << l.back() <<std::endl;

	list<int>::iterator it_tmp = l.begin();
	it_tmp++;
	it_tmp++;
	it_tmp++;

	l.insert(it_tmp, 10);
	std::cout << l << " | " << *it_tmp << " | " << l.size() <<std::endl;

	l.insert(it_tmp, 3, 55);
	std::cout << l << " | " << *it_tmp << " | " << l.size() <<std::endl;

	it_tmp = l.erase(it_tmp);
	list<int> l_copy2(l);
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << " start: " << l.front() << " end: " << l.back() <<std::endl;
	l.erase(l.begin(), it_tmp);
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << " start: " << l.front() << " end: " << l.back() <<std::endl;
	l.erase(l.begin(), l.end());
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << std::endl;
	l.erase(l.begin(), l.end());
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << std::endl;

	l = l_copy2;
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << " start: " << l.front() << " end: " << l.back() <<std::endl;
	l.remove(22);
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << std::endl;
	l.remove_if([](int n){return n >= 10;});
	std::cout << l << std::endl;
	std::cout << "new size:" << l.size() << std::endl;
	l = l_copy2;
	l.sort();
	std::cout << l << std::endl;
	std::cout << l_ass << std::endl;
	l.merge(l_ass);
	std::cout << l << std::endl;
	std::cout << l_ass << std::endl;
	std::cout << "new size:" << l.size() << std::endl;
	std::cout << "new size:" << l_ass.size() << std::endl;
	std::cout << l_copy2 << std::endl;
	list<int>::iterator iter = l.begin();
	iter++;
	iter++;

	l.splice(iter, l_copy2);
	std::cout << l << std::endl;
	std::cout << l_copy2 << std::endl;
	std::cout << "new size:" << l.size() << std::endl;
	std::cout << "new size:" << l_copy2.size() << std::endl;

	l_copy2.splice(l_copy2.begin(), l, iter, l.end());
	std::cout << l << std::endl;
	std::cout << l_copy2 << std::endl;
	std::cout << "new size:" << l.size() << std::endl;
	std::cout << "new size:" << l_copy2.size() << std::endl;

}


// void	map_test(void)
// {
// 	map<int, int> m;

// 	std::cout << "empty: " << m.empty() << " size: " << m.size() << std::endl;
// 	m[10] = 21;
// 	std::cout << "empty: " << m.empty() << " size: " << m.size() << std::endl;
// 	std::cout << m[10] << std::endl;
// 	std::cout << "empty: " << m.empty() << " size: " << m.size() << std::endl;
// 	m.clear();
// 	std::cout << "empty: " << m.empty() << " size: " << m.size() << std::endl;
// 	// std::cout << "Count: " << m.count(10) << std::endl;

// 	map<char,int> mymap;

// 	mymap['b'] = 100;
// 	mymap['a'] = 200;
// 	mymap['c'] = 300;

// 	std::cout << "empty: " << mymap.empty() << " size: " << mymap.size() << std::endl;

// 	// show content:
// 	for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); it++)
// 		std::cout << it->first << " => " << it->second << '\n';

// 	mymap.clear();
// 	std::cout << "empty: " << mymap.empty() << " size: " << mymap.size() << std::endl;
// }

void stack_test();
void list_test();
void map_test();
void vector_test();
void pair_test();
void iterator_test();
void integral_test();
void enable_if_test();


int main(void)
{

	// std::cout << "------------ PAIR ----------- " << std::endl;
	// pair_test();
	// std::cout << "------------ LIST ----------- " << std::endl;
	// list_test();
	std::cout << "------------ VECTOR ----------- " << std::endl;
	vector_test();
	// std::cout << "------------ MAP ----------- " << std::endl;
	// map_test();
	// std::cout << "------------ Iterator ----------- " << std::endl;
	// iterator_test();
	// std::cout << "------------ Integral ----------- " << std::endl;
	// integral_test();
	std::cout << "------------ Enable if ----------- " << std::endl;
	enable_if_test();
	// std::cout << "------------ STACK ----------- " << std::endl;
	// stack_test();
}