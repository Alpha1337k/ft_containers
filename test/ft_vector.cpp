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

#include <vector>
#include <ft_vector.hpp>
#include <iostream>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

template <typename T, typename Allocator>
std::ostream &operator<<(std::ostream &out, vector<T, Allocator> &v)
{
	typedef typename vector<T, Allocator>::iterator iterator;
	for (iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	return (out);
}

void	v_create_test()
{
	vector<int> v1;

	std::cout << "empty? " << v1.empty() << " size: " << v1.size() << std::endl;
	v1.push_back(10);
	v1.push_back(12);
	v1.push_back(13);
	v1.push_back(11);
	v1.push_back(15);
	std::cout << "empty? " << v1.empty() << " size: " << v1.size() << std::endl;

	vector<int> v2(v1);
	vector<int> v3 = v1;
	vector<int> v4(10, 100);
	vector<int> v5(v1.begin(), v1.end());
	std::cout << "empty? " << v1.empty() << " size: " << v1.size() << v1 << std::endl;
	std::cout << "empty? " << v2.empty() << " size: " << v2.size() << v2 << std::endl;
	std::cout << "empty? " << v3.empty() << " size: " << v3.size() << v3 << std::endl;
	std::cout << "empty? " << v4.empty() << " size: " << v4.size() << v4 << std::endl;
	std::cout << "empty? " << v5.empty() << " size: " << v5.size() << v5 << std::endl;
}

void	v_access_test()
{
	vector<char> v;

	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.push_back('d');


	std::cout << v.at(0) << std::endl;
	v.at(0) = 'z';
	std::cout << v.at(0) << std::endl;
	std::cout << v.at(1) << std::endl;
	std::cout << v.at(2) << std::endl;
	std::cout << v.at(3) << std::endl;
	try
	{
		std::cout << v.at(4) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "error!" << '\n';
	}
	v.clear();

	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.push_back('d');



	for (size_t i = 0; i < v.size(); i++)
		v[i]++;
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;

	std::cout << v.front() << std::endl;
	std::cout << v.back() << std::endl;

	const vector<char> v_c(v);
	std::cout << v_c.front() << std::endl;
	std::cout << v_c.back() << std::endl;
	for (size_t i = 0; i < v_c.size(); i++)
		std::cout << v_c[i] << " ";
	std::cout << std::endl;
	std::cout << v.at(3) << std::endl;

	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.push_back('d');

	char *data = v.data();

	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;

}

void	v_assign_test()
{
	vector<double> a;
	vector<double> b;

	a.assign(10, 69.69);
	std::cout << "empty? " << a.empty() << " size: " << a.size() << a << std::endl;
	vector<double>::iterator it = a.begin() + 2;
	b.assign(it, a.end());
	std::cout << "empty? " << b.empty() << " size: " << b.size() << b << std::endl;

}

void	v_capacity_test()
{
	vector<int> a;
	vector<char> b;
	vector<std::string> c;
	vector<double> d;

	std::cout << a.max_size() << std::endl;
	std::cout << b.max_size() << std::endl;
	std::cout << c.max_size() << std::endl;
	std::cout << d.max_size() << std::endl;

	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	a.reserve(10);
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	for (size_t i = 0; i < a.capacity(); i++)
		a[i] = 69;
	vector<int>::iterator it = a.begin();
	a.reserve(1);
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	a.reserve(10);
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	for (; it != a.end(); it++)
		std::cout << *it << " " << std::endl;
	try {
		a.reserve(a.max_size() + 1);
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << '\n';
	}
	for (size_t i = 0; i < 200; i++)
		a.push_back(69);
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
}

class OBJ
{
	public:
		OBJ() {}
		std::string print() {return ("printin!!");}
};

void	v_iterator_test()
{
	vector<int> l;
	vector<OBJ> l1;
	
	l.push_back(3);
	l.push_back(1);
	l.push_back(2);
	l.push_back(4);
	l.push_back(6);
	l.push_back(8);

	l1.push_back(OBJ());
	const vector<int> l2(l);

	vector<int>::iterator it = l.begin();
	vector<OBJ>::iterator it2 = l1.begin();
	std::cout << *it << std::endl;
	it += 3;
	std::cout << *it << std::endl;
	it -= 1;
	std::cout << *it << std::endl;

	std::cout << *(it - 2) << std::endl;

	std::cout << it2->print() << std::endl;
	for (vector<int>::reverse_iterator itr = l.rbegin(); itr != l.rend(); ++itr)
		std::cout << *itr << " ";
	std::cout << std::endl;
	for (vector<int>::reverse_iterator itr = l.rbegin(); itr != l.rend(); itr++)
		std::cout << *itr << " ";
	std::cout << std::endl;
	for (vector<int>::const_iterator itr = l2.begin(); itr != l2.end(); itr++)
		std::cout << *itr << " ";
	std::cout << std::endl;

}

void	v_modifiers_test()
{
	vector<int> a;
	vector<int> b;

	a.resize(10);
	std::cout << a << std::endl;
	a.resize(8, 69);
	std::cout << a << std::endl;
	a.resize(0, 69);
	std::cout << a << std::endl;
	a.resize(0);
	a.resize(8, 69);
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	std::cout << a << std::endl;
	a.pop_back();
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	std::cout << a << std::endl;

	b.resize(10);
	b.insert(b.begin(), 10);
	std::cout << b << std::endl;
	vector<int>::iterator it = b.begin();
	it++;

	std::cout << *it << std::endl;
	b.insert(it, 3, 44);
	std::cout << b << std::endl;
	std::cout << "empty? " << b.empty() << " size: " << b.size() << " capacity: " << b.capacity() << std::endl;
	it++;
	it++;
	b.insert(it, 0, 44);
	std::cout << b << std::endl;
	std::cout << "empty? " << b.empty() << " size: " << b.size() << " capacity: " << b.capacity() << std::endl;
	b.insert(it, 5, 88);
	std::cout << b << std::endl;
	std::cout << "empty? " << b.empty() << " size: " << b.size() << " capacity: " << b.capacity() << std::endl;
	b.erase(it);
	b.swap(a);
	std::cout << a << std::endl;
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	std::cout << b << std::endl;
	std::cout << "empty? " << b.empty() << " size: " << b.size() << " capacity: " << b.capacity() << std::endl;
	a.erase(a.begin());
	std::cout << a << std::endl;
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	a.erase(a.begin(), a.end());
	std::cout << a << std::endl;
	std::cout << "empty? " << a.empty() << " size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	it = b.begin();
	std::cout << *it << std::endl;
	it++;
	it++;
	it++;
	b.erase(b.begin(), it);
	std::cout << b << std::endl;
	std::cout << "empty? " << b.empty() << " size: " << b.size() << " capacity: " << b.capacity() << std::endl;

	vector<std::string> c;

	c.push_back("a1");
	c.push_back("a2");
	c.push_back("a3");
	c.push_back("a4");
	c.push_back("a5");

	std::cout << c << std::endl;
	std::cout << "empty? " << c.empty() << " size: " << c.size() << " capacity: " << c.capacity() << std::endl;
	vector<std::string> c1;

	c1.insert(c1.begin(), c.begin() + 2, c.end());
	std::cout << c1 << std::endl;
	std::cout << "empty? " << c1.empty() << " size: " << c1.size() << " capacity: " << c1.capacity() << std::endl;

	swap(c1, c);
	std::cout << c << std::endl;
	std::cout << "empty? " << c.empty() << " size: " << c.size() << " capacity: " << c.capacity() << std::endl;
	std::cout << c1 << std::endl;
	std::cout << "empty? " << c1.empty() << " size: " << c1.size() << " capacity: " << c1.capacity() << std::endl;

}

void	v_compare_test(void)
{
	vector<int> compare_1;
	vector<int> compare_2;
	vector<int> compare_3;
	vector<int> compare_4;
	vector<int> compare_5;

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

void	vector_test(void)
{
	std::cout << "\t------- Create " << std::endl;
	v_create_test();
	std::cout << "\t------- Assign " << std::endl;
	v_assign_test();
	std::cout << "\t------- Access " << std::endl;
	v_access_test();
	std::cout << "\t------- Iterators " << std::endl;
	v_iterator_test();
	std::cout << "\t------- Capacity " << std::endl;
	v_capacity_test();
	std::cout << "\t------- Modifiers " << std::endl;
	v_modifiers_test();
	std::cout << "\t------- Compare " << std::endl;
	v_compare_test();
}