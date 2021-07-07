#include <iostream>
#include <vector>
#include <list>

#include <ft_iterator.hpp>
#include <iterator>

#ifdef USE_OS_VARIANT
	using namespace std;
#else
	using namespace ft;
#endif

 
template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    --n;
    while(n > 0) {
        typename iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
        n -= 2;
    }
}
 
void i_traits_test()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    my_reverse(v.begin(), v.end());
    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    std::list<int> l{1, 2, 3, 4, 5};
    my_reverse(l.begin(), l.end());
    for (auto n : l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    int a[] = {1, 2, 3, 4, 5};
    my_reverse(a, a+5);
    for (int i=0; i<5; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
}

void	i_construct_base_test()
{
    const int a1[] {666, 1, 2, 3};
 
	reverse_iterator<const int *> it1(std::cbegin(a1));
	reverse_iterator<const int *> it2(it1);
	reverse_iterator<const int *> it3 = it1;
	reverse_iterator<const int *> it4;

	it4 = it1;

	std::cout << *it1.base() << " " << *it2.base() << " " << *it3.base() << " " << *it4.base() << std::endl;
	std::cout << (it1.base() == it2.base() && it3.base() == it4.base() && it1.base() == it3.base()) << std::endl;
}

void	i_access_test()
{
    // int a1[] {666, 1, 2};
	// reverse_iterator<const int *> it(std::cbegin(a1));
	// for (size_t i = 0; i != 3; i++)
	// 	std::cout << it[i] << " " << std::endl;
	// std::cout << std::endl;

    // std::vector<int> v;
	// v.push_back(10);
	// v.push_back(11);
	// v.push_back(12);
	// v.push_back(13);

	// reverse_iterator<std::vector<int>::iterator> vit(std::rbegin(v));
	// for (size_t i = 0; i != v.size(); i++)
	// {
	// 	vit[i] += 1;
	// 	std::cout << vit[i] << " " << std::endl;
	// }
	// std::cout << std::endl;
}

void	reverse_iterator_test()
{
	i_construct_base_test();
	i_access_test();
}

void	iterator_test(void)
{
	i_traits_test();
	reverse_iterator_test();

}