#ifndef FT_IS_INTERGRAL_HPP
#define FT_IS_INTERGRAL_HPP

namespace ft
{

template< class T >
struct integral_test
{
    static const bool value = false;
};

template<> struct integral_test<int> { static const bool value = true;};
template<> struct integral_test<char> { static const bool value = true;};
template<> struct integral_test<bool> { static const bool value = true;};
template<> struct integral_test<char16_t> { static const bool value = true;};
template<> struct integral_test<char32_t> { static const bool value = true;};
template<> struct integral_test<wchar_t> { static const bool value = true;};
template<> struct integral_test<short> { static const bool value = true;};
template<> struct integral_test<long> { static const bool value = true;};
template<> struct integral_test<long long> { static const bool value = true;};

template<> struct integral_test<const int> { static const bool value = true;};
template<> struct integral_test<const char> { static const bool value = true;};
template<> struct integral_test<const bool> { static const bool value = true;};
template<> struct integral_test<const char16_t> { static const bool value = true;};
template<> struct integral_test<const char32_t> { static const bool value = true;};
template<> struct integral_test<const wchar_t> { static const bool value = true;};
template<> struct integral_test<const short> { static const bool value = true;};
template<> struct integral_test<const long> { static const bool value = true;};
template<> struct integral_test<const long long> { static const bool value = true;};

template< class T >
struct is_integral : public integral_test<T>
{
	static const bool value = integral_test<T>::value;
	operator bool() const { return value;}
};

};

#endif