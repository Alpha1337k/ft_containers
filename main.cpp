
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

	std::cout << "size: " << l.size() << std::endl;
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << std::endl;

	l.pop_back();
	l.pop_front();
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "empty? " << l.empty() << std::endl;
	std::cout << "back: " << l.back() << std::endl;
	std::cout << "front: " << l.front() << std::endl;
	std::cout << "clearing.." << std::endl;
	l.clear();
	std::cout << "empty? " << l.empty() << std::endl;
	std::cout << "clearing.." << std::endl;
	l.clear();
	std::cout << "empty? " << l.empty() << std::endl;
	for (list<int>::iterator it = l_ass.begin(); it != l_ass.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	for (list<int>::iterator it = l_copy.begin(); it != l_copy.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	l.assign(5, 'a');
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
    const std::string extra(6, 'b');
    l.assign(extra.begin(), extra.end());
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	std::cout << "are l and l_copy the same???\t" << (bool)(l == l_ass) << std::endl;
	std::cout << "are l_ass and l_copy the same???\t" << (bool)(l_ass == l_copy) << std::endl;

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
}

int main(void)
{
	std::cout << "------------ LIST ----------- " << std::endl;
	list_test();
	std::cout << "------------ VECTOR ----------- " << std::endl;
	vector_test();
}