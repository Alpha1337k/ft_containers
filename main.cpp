
#include <ft_list.hpp>
#include <iostream>
#include <list>

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

}

int main(void)
{
	std::cout << "------------ LIST ----------- " << std::endl;
	list_test();
}