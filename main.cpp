
#include <ft_list.hpp>
#include <ft_vector.hpp>
#include <iostream>
#include <list>
#include <vector>

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
	std::cout << "\n";
	return (out);
}

void	list_test()
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
	// list<int>::iterator it_tmp = l.begin();
	// it_tmp++;
	// it_tmp++;
	// it_tmp++;
	// it_tmp = l.erase(it_tmp);
	// std::cout << l << std::endl;
	// std::cout << "new size:" << l.size() << " start: " << l.front() << " end: " << l.back() <<std::endl;
	// l.erase(l.begin(), it_tmp);
	// std::cout << l << std::endl;
	// std::cout << "new size:" << l.size() << " start: " << l.front() << "end: " << l.back() <<std::endl;

	// l.remove(22);
	// std::cout << l << std::endl;
	// std::cout << "new size:" << l.size() << std::endl;
	// l.remove_if([](int n){return n > 8;});
	// std::cout << l << std::endl;
	// std::cout << "new size:" << l.size() << std::endl;
}

void vector_test()
{
	vector<int> a;

	std::cout << "Max size: " << a.max_size() << std::endl;
	a.push_back(10);
	a.push_back(11);
	a.push_back(12);
	a.push_back(13);
	a.push_back(14);
	std::cout << "Capacity " << a.capacity() << " size: " << a.size() << std::endl;
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << "\n";
	std::cout << "Front: " << a.front() << " back " << a.back() << std::endl;
	try
	{
		a.at(10) = 0;
	}
	catch(const std::exception& e) {
		std::cout << "caught error!" << std::endl; }
	a.at(1) = 69;
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << "\n";
	a.resize(2);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << "\n";
	a.resize(10, 69);
	a.resize(11);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << "\n";
	vector<int> a1;
	a1.push_back(1);
	a1.swap(a);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << "\n";
	std::cout << "are a and a1 the same???\t" << (bool)(a == a1) << std::endl;
	vector<int> a2;
	a2.push_back(1);
	std::cout << "are a and a2 the same???\t" << (bool)(a2 == a) << std::endl;
	for (vector<int>::iterator it = a1.begin(); it != a1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";

	for (vector<int>::reverse_iterator it = a1.rbegin(); it != a1.rend(); it++)
		std::cout << *it << " ";
	std::cout << "\n";

	vector<int> compare_1;
	vector<int> compare_2;
	vector<int> compare_3;
	vector<int> compare_4;

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

}

int main(void)
{
	std::cout << "------------ LIST ----------- " << std::endl;
	list_test();
	std::cout << "------------ VECTOR ----------- " << std::endl;
	vector_test();
}