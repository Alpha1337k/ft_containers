#include <ft_stack.hpp>
#include <ft_list.hpp>
#include <ft_vector.hpp>

#include <stack>
#include <list>
#include <vector>
#include <iostream>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif


void swap_test()
{
	stack<int> s1;
	stack<int> s2;

	s1.push(3);
	s1.push(1);
	s1.push(2);
	s2.push(1);
	s2.push(2);
	s2.push(3);
	s2.push(3);
	s2.push(69420);

	std::cout << s1.empty() << " | " << s1.size() << " | " << s1.top() << std::endl;
	std::cout << s2.empty() << " | " << s2.size() << " | " << s2.top() << std::endl;
	s1.swap(s2);
	std::cout << s1.empty() << " | " << s1.size() << " | " << s1.top() << std::endl;
	std::cout << s2.empty() << " | " << s2.size() << " | " << s2.top() << std::endl;
}

void compare_test()
{
	stack<int> compare_1;
	stack<int> compare_2;
	stack<int> compare_3;
	stack<int> compare_4;

	compare_1.push(3);
	compare_1.push(1);
	compare_1.push(2);
	compare_2.push(1);
	compare_2.push(2);
	compare_2.push(3);
	compare_3.push(36);
	compare_3.push(32);
	compare_3.push(31);
	compare_3.push(1);
	compare_4.push(1);
	compare_4.push(2);
	compare_4.push(3);

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

void top_test()
{
	stack<int> s1;
	s1.push(42);

	std::cout << s1.top() << std::endl;
	s1.pop();
	s1.push(43);
	s1.push(44);
	std::cout << s1.top() << std::endl;
	s1.top() = 10;
	std::cout << s1.top() << std::endl;
}

void pop_test()
{
	stack<int> s1;
	s1.push(42);

	s1.pop();
	s1.pop();

	std::cout << s1.empty() << " | " << s1.size()<< std::endl;
}

void list_stack()
{
	list<int> l1;
	l1.resize(10, 10);

	std::stack<int, list<int>> s1(l1);
	std::cout << s1.empty() << " | " << s1.size()<< std::endl;
	std::cout << s1.top() << std::endl;
	s1.push(42);
	std::cout << s1.empty() << " | " << s1.size()<< std::endl;
	std::cout << s1.top() << std::endl;

	stack<int, list<int>> s2(l1);
	std::cout << s2.empty() << " | " << s2.size()<< std::endl;
	std::cout << s2.top() << std::endl;
	s2.push(42);
	std::cout << s2.empty() << " | " << s2.size()<< std::endl;
	std::cout << s2.top() << std::endl;

	vector<int> v1;
	v1.resize(20, 22);
	stack<int, vector<int>> s3(v1);

	std::cout << s3.empty() << " | " << s3.size()<< std::endl;
	std::cout << s3.top() << std::endl;
	s3.push(42);
	std::cout << s3.empty() << " | " << s3.size()<< std::endl;
	std::cout << s3.top() << std::endl;

	std::stack<int, vector<int>> s4(v1);

	std::cout << s4.empty() << " | " << s4.size()<< std::endl;
	std::cout << s4.top() << std::endl;
	s4.push(42);
	std::cout << s4.empty() << " | " << s4.size()<< std::endl;
	std::cout << s4.top() << std::endl;
}


void operator_test()
{
	stack<int> s1;

	std::cout << s1.empty() << " | " << s1.size()<< std::endl;
	s1.push(42);
	s1.push(42);
	s1.push(42);
	s1.push(42);
	stack<int> s2(s1);
	stack<int> s3 = s2;
	s3.pop();
	std::cout << s1.empty() << " | " << s1.size()<< std::endl;
	std::cout << s2.empty() << " | " << s2.size()<< std::endl;
	std::cout << s3.empty() << " | " << s3.size()<< std::endl;
}

void stack_test()
{
	operator_test();
	top_test();
	compare_test();
	list_stack();
	swap_test();
}