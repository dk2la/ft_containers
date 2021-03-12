#include "../srcs/list.hpp"
#include <iostream>
#include <list>

#define RED "\033[1;31m"
#define GREEN "\033[1;33m"
#define RESET "\033[0m"

template<typename T>
bool compare(const T &x, const T& y)
{
	return (x < y);
}

bool cmp(int i) {

	return (i == 1000);

}

bool cmp_2(int i, int j) {

	return (i == j);

}

void print_two (std::list<int> &b, ft::list<int> &a)
{
	std::cout << "ft::list.size(): " << a.size() << std::endl;
	std::cout << "std::list.size(): " << b.size() << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Значения:" << std::endl;
	std::cout << "std::list: ";
	for (std::list<int>::iterator beg = b.begin(); beg != b.end(); beg++)
		std::cout << *beg << " ";
	std::cout << std::endl;
	std::cout << "ft::list:  ";
	for (ft::list<int>::iterator beg = a.begin(); beg != a.end(); beg++)
		std::cout << *beg << " ";
	std::cout << std::endl;
	std::cout << "-------------------------" << std::endl;
}

void print_4 (std::list<int> &b, std::list<int> &bb, ft::list<int> &a, ft::list<int> &aa)
{
	std::cout << "std::list: size(b) " << b.size() << std::endl;
	std::cout << "std::list: size(bb) " << bb.size() << std::endl;
	std::cout << "ft::list: size(a) " << a.size() << std::endl;
	std::cout << "ft::list: size(aa) " << aa.size() << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "std::list: ";
	std::list<int>::iterator beg1 = b.begin();
	for (; beg1 != b.end(); beg1++)
		std::cout << *beg1 << " ";
	std::cout << std::endl;
	std::cout << "ft::list:  ";
	ft::list<int>::iterator beg2 = a.begin();
	for (; beg2 != a.end(); beg2++)
		std::cout << *beg2 << " ";
	std::cout << std::endl;
	std::cout << "std::list: ";
	std::list<int>::iterator beg3 = bb.begin();
	for (; beg3 != bb.end(); beg3++)
		std::cout << *beg3 << " ";
	std::cout << std::endl;
	std::cout << "ft::list:  ";
	ft::list<int>::iterator beg4 = aa.begin();
	for (; beg4 != aa.end(); beg4++)
		std::cout << *beg4 << " ";
	std::cout << std::endl;

	std::cout << "------------------" << std::endl;
}
void print_cmp(std::list<int> &b, std::list<int> &bb, ft::list<int> &a, ft::list<int> &aa)
{
	std::cout << "------------------" << std::endl;
	std::cout << "ft::list  == " << (a == aa) << std::endl;
	std::cout << "std::list == " << (b == bb) << std::endl;
	std::cout << "ft::list  != " << (a != aa) << std::endl;
	std::cout << "std::list != " << (b != bb) << std::endl;
	std::cout << "ft::list  <  " << (a < aa) << std::endl;
	std::cout << "std::list <  " << (b < bb) << std::endl;
	std::cout << "ft::list  <= " << (a <= aa) << std::endl;
	std::cout << "std::list <= " << (b <= bb) << std::endl;
	std::cout << "ft::list  >  " << (a > aa) << std::endl;
	std::cout << "std::list >  " << (b > bb) << std::endl;
	std::cout << "ft::list  >= " << (a >= aa) << std::endl;
	std::cout << "std::list >= " << (b >= bb) << std::endl;
	std::cout << "------------------" << std::endl;
}

int		list_test(void)
{
	{
		std::cout <<  "\033c";
		std::cout << GREEN << "I. Constructors and assignation" << RESET << std::endl << std::endl;
		std::cout << RED << "Создание без аргументов" << RESET << std::endl;
		ft::list<int> a;
		std::list<int> b;

		std::cout << "ft::list.size(): " << a.size() << std::endl;
		std::cout << "std::list.size(): " << b.size() << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "explicit list(const Allocator &alloc): _length(0)"<< RESET << std::endl;

		std::allocator<int> Alloc;

		ft::list<int> a(Alloc);
		std::list<int> b(Alloc);

		std::cout << "ft::list.size(): " << a.size() << std::endl;
		std::cout << "std::list.size(): " << b.size() << std::endl;

		std::cout << "После добавления элемента: " << std::endl;
		a.push_back(12);
		b.push_back(24);
		std::cout << "ft::list.size(): " << a.size() << std::endl;
		std::cout << "std::list.size(): " << b.size() << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "explicit list(size_type count, const T &value = T(), const Allocator &alloc = Allocator())" << RESET << std::endl;

		std::cout << "Count: 10" << std::endl;
		ft::list<int> a(10);

		std::list<int> b(10);

		print_two(b, a);

		std::cout << "Count: 0" << std::endl;
		ft::list<int> a1(0);
		std::list<int> b1(0);

		std::cout << "ft::list.size(): " << a1.size() << std::endl;
		std::cout << "std::list.size(): " << b1.size() << std::endl;

	}
	{
		std::cout << std::endl << "Count: 100, value 42" << std::endl;
		ft::list<int> a(100, 42);
		std::list<int> b(100, 42);

		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "list(InputIt first, InputIt last, const Allocator &alloc = Allocator())" << RESET << std::endl;

		std::list<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::list<int> a(c.begin(), c.end());
		std::list<int> b(c.begin(), c.end());

		print_two(b, a);
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << RED << "list (const list &other)" << RESET << std::endl;

		std::list<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::list<int> d;

		d.push_back(10);
		d.push_back(20);
		d.push_back(30);
		d.push_back(40);
		d.push_back(50);
		d.push_back(60);

		ft::list<int> a(d);
		std::list<int> b(c);

		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
		std::cout << "I AM HERE" << std::endl;

	}
	{
		std::cout << std::endl << RED << "list &operator=(const list &other)" << RESET << std::endl;

		std::list<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::list<int> d;

		d.push_back(10);
		d.push_back(20);
		d.push_back(30);
		d.push_back(40);
		d.push_back(50);
		d.push_back(60);

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До =: " << std::endl;
		print_two(b, a);

		a = d;
		b = c;

		std::cout << "После =: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void assign( size_type count, const T& value )" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;
		print_two(b, a);

		a.assign(10, 150);
		b.assign(10, 150);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void assign( InputIt first, InputIt last )" << RESET << std::endl;

		std::list<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;
		print_two(b, a);

		a.assign(c.begin(), c.end());
		b.assign(c.begin(), c.end());

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout <<  std::endl << GREEN <<  "II. Elements access" << RESET << std::endl << std::endl;
		std::cout << RED << "reference front(void)" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		b.push_back(1000);
		std::cout << "std::list: " << a.front() << std::endl;
		std::cout << "ft::list: " << b.front() << std::endl;

		a.push_front(1500);
		b.push_front(1500);

		std::cout << "std::list: " << a.front() << std::endl;
		std::cout << "ft::list: " << b.front() << std::endl;

		a.push_front(2000);
		b.push_front(2000);

		std::cout << "std::list: " << a.front() << std::endl;
		std::cout << "ft::list: " << b.front() << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "const_reference front(void) const" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		b.push_back(1000);
		const int &aa = a.front();
		const int &bb = b.front();
		std::cout << "std::list: " << aa << std::endl;
		std::cout << "ft::list: " << bb << std::endl;

		a.push_front(1500);
		b.push_front(1500);
		const int &aaa = a.front();
		const int &bbb = b.front();
		std::cout << "std::list: " << aaa << std::endl;
		std::cout << "ft::list: " << bbb << std::endl;

		a.push_front(2000);
		b.push_front(2000);
		const int &aaaa = a.front();
		const int &bbbb = b.front();
		std::cout << "std::list: " << aaaa << std::endl;
		std::cout << "ft::list: " << bbbb << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "reference back(void)" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		b.push_back(1000);
		std::cout << "std::list: " << a.back() << std::endl;
		std::cout << "ft::list: " << b.back() << std::endl;

		a.push_back(1500);
		b.push_back(1500);

		std::cout << "std::list: " << a.back() << std::endl;
		std::cout << "ft::list: " << b.back() << std::endl;

		a.push_back(2000);
		b.push_back(2000);

		std::cout << "std::list: " << a.back() << std::endl;
		std::cout << "ft::list: " << b.back() << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "const_reference back(void) const" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		b.push_back(1000);
		const int &aa = a.back();
		const int &bb = b.back();
		std::cout << "std::list: " << aa << std::endl;
		std::cout << "ft::list: " << bb << std::endl;

		a.push_back(1500);
		b.push_back(1500);
		const int &aaa = a.back();
		const int &bbb = b.back();
		std::cout << "std::list: " << aaa << std::endl;
		std::cout << "ft::list: " << bbb << std::endl;

		a.push_back(2000);
		b.push_back(2000);
		const int &aaaa = a.back();
		const int &bbbb = b.back();
		std::cout << "std::list: " << aaaa << std::endl;
		std::cout << "ft::list: " << bbbb << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout  << std::endl << GREEN << "III. Iterators" << RESET << std::endl << std::endl;
		std::cout << RED << "begin, end" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "std::list: ";
		for (std::list<int>::iterator beg = b.begin(); beg != b.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		for (ft::list<int>::iterator beg = a.begin(); beg != a.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;

		std::cout << std::endl << "rbegin, rend" << std::endl;
		std::cout << "std::list: ";
		for (std::list<int>::iterator beg = b.begin(); beg != b.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		for (ft::list<int>::iterator beg = a.begin(); beg != a.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << RED << "const begin, const end" << RESET << std::endl;

		ft::list< int > a;
		std::list< int > b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "std::list: ";
		for (std::list< int>::const_iterator beg = b.begin(); beg != b.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		for (ft::list< int>::const_iterator beg = a.begin(); beg != a.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;

		std::cout << std::endl << "rbegin, rend" << std::endl;
		std::cout << "std::list: ";
		for (std::list< int>::reverse_iterator beg = b.rbegin(); beg != b.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		for (ft::list< int>::reverse_iterator beg = a.rbegin(); beg != a.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;

		std::cout << std::endl << "const rbegin, const rend" << std::endl;
		std::cout << "std::list: ";
		for (std::list< int>::const_reverse_iterator beg = b.rbegin(); beg != b.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		for (ft::list< int>::const_reverse_iterator beg = a.rbegin(); beg != a.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << GREEN << "IV. Capacity" << RESET << std::endl << std::endl;
		std::cout << RED << "empty, size, maxsize" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		std::cout << "std::list: empty " << b.empty() << std::endl;
		std::cout << "ft::list: empty " << a.empty() << std::endl;

		std::cout << "std::list: size " << b.size() << std::endl;
		std::cout << "ft::list: size " << a.size() << std::endl;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "std::list: empty " << b.empty() << std::endl;
		std::cout << "ft::list: empty " << a.empty() << std::endl;
		std::cout << "std::list: size " << b.size() << std::endl;
		std::cout << "ft::list: size " << a.size() << std::endl;

		std::cout << "std::list: max_size " << b.max_size() << std::endl;
		std::cout << "ft::list: max_size " << a.max_size() << std::endl;
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << GREEN << "V. Modifiers" << RESET << std::endl << std::endl;
		std::cout << RED << "void clear(void)" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		a.clear();
		b.clear();

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << RED << "iterator insert( iterator pos, const T& value )" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size " << b.size() << std::endl;
		std::cout << "ft::list: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "------------------" << std::endl;
		beg1++;
		beg2++;

		b.insert(beg1, 10000);
		a.insert(beg2, 10000);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << RED << "void insert( iterator pos, size_type count, const T& value )" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;


		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size " << b.size() << std::endl;
		std::cout << "ft::list: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "------------------" << std::endl;

		beg1++;
		beg2++;

		b.insert(beg1, 20, 10000);
		a.insert(beg2, 20, 10000);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);

		b.insert(b.end(), 20, 9999);
		a.insert(a.end(), 20, 9999);
		std::cout << "Добавление в конец: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void insert( iterator pos, InputIt first, InputIt last)" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;
		std::list<int> c;

		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);
		c.push_back(10);

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "Значения для вставки: size " << c.size() << std::endl;
		std::cout << "std::list: ";
		for (std::list<int>::iterator beg = c.begin(); beg != c.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;

		std::cout << "До вызова: " << std::endl;
		std::cout << "std::list: size " << b.size() << std::endl;
		std::cout << "ft::list: size " << a.size() << std::endl;
		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "------------------" << std::endl;
		beg1++;
		beg2++;

		b.insert(beg1, c.begin(), c.end());
		a.insert(beg2, c.begin(), c.end());

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "iterator erase( iterator pos )" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size " << b.size() << std::endl;
		std::cout << "ft::list: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;
		beg1++;
		beg2++;

		b.erase(beg1);
		a.erase(beg2);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "iterator erase( iterator first, iterator last )" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size " << b.size() << std::endl;
		std::cout << "ft::list: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;
		beg1++;
		beg1++;
		beg2++;
		beg2++;

		b.erase(beg1, b.end());
		a.erase(beg2, a.end());

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "pop_back pop_front" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		b.pop_back();
		b.pop_front();
		a.pop_back();
		a.pop_front();

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);

		b.pop_back();
		b.pop_front();
		b.pop_back();
		a.pop_back();
		a.pop_front();
		a.pop_back();

		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void resize( size_type count, T value = T() )" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		a.resize(10);
		b.resize(10);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);

		a.resize(2);
		b.resize(2);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void swap (list &other)" << RESET << std::endl;

		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		a.push_back(1);
		a.push_back(1);
		a.push_back(1);
		a.push_back(1);
		a.push_back(1);

		aa.push_back(2);
		aa.push_back(2);
		aa.push_back(2);
		aa.push_back(2);
		aa.push_back(2);

		b.push_back(1);
		b.push_back(1);
		b.push_back(1);
		b.push_back(1);
		b.push_back(1);

		bb.push_back(2);
		bb.push_back(2);
		bb.push_back(2);
		bb.push_back(2);
		bb.push_back(2);

		std::cout << "До вызова: " << std::endl;

		print_4 (b, bb, a, aa);

		a.swap(aa);
		b.swap(bb);

		std::cout << "После вызова: " << std::endl;
		print_4 (b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void merge (list &other)" << RESET << std::endl;

		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		a.push_back(1);
		a.push_back(1);
		a.push_back(2);
		a.push_back(3);
		a.push_back(4);

		aa.push_back(1);
		aa.push_back(2);
		aa.push_back(3);
		aa.push_back(4);
		aa.push_back(5);

		b.push_back(1);
		b.push_back(1);
		b.push_back(2);
		b.push_back(3);
		b.push_back(4);

		bb.push_back(1);
		bb.push_back(2);
		bb.push_back(3);
		bb.push_back(4);
		bb.push_back(5);

		std::cout << "До вызова: " << std::endl;

		print_4 (b, bb, a, aa);

		a.merge(aa);
		b.merge(bb);

		std::cout << "После вызова: " << std::endl;
		print_4 (b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void merge( list& other, Compare comp )" << RESET << std::endl;

		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		a.push_back(10);
		a.push_back(100);
		a.push_back(22);
		a.push_back(3);
		a.push_back(48);

		aa.push_back(99);
		aa.push_back(87);
		aa.push_back(1015);
		aa.push_back(9999);
		aa.push_back(1);

		b.push_back(10);
		b.push_back(100);
		b.push_back(22);
		b.push_back(3);
		b.push_back(48);

		bb.push_back(99);
		bb.push_back(87);
		bb.push_back(1015);
		bb.push_back(9999);
		bb.push_back(1);

		a.sort();
		aa.sort();
		b.sort();
		bb.sort();

		std::cout << "До вызова: " << std::endl;

		print_4 (b, bb, a, aa);

		a.merge(aa, compare<int>);
		b.merge(bb, compare<int>);

		std::cout << "После вызова: " << std::endl;
		print_4 (b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void splice( const_iterator pos, list& other )" << RESET << std::endl;

		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		aa.push_back(99);
		aa.push_back(87);
		aa.push_back(1015);
		aa.push_back(9999);
		aa.push_back(1);

		bb.push_back(99);
		bb.push_back(87);
		bb.push_back(1015);
		bb.push_back(9999);
		bb.push_back(1);

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size(b) " << b.size() << std::endl;
		std::cout << "std::list: size(bb) " << bb.size() << std::endl;
		std::cout << "ft::list: size(a) " << a.size() << std::endl;
		std::cout << "ft::list: size(aa) " << aa.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg3 = bb.begin();
		for (; beg3 != bb.end(); beg3++)
			std::cout << *beg3 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg4 = aa.begin();
		for (; beg4 != aa.end(); beg4++)
			std::cout << *beg4 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;

		beg1++;
		beg1++;
		beg2++;
		beg2++;

		b.splice(beg1, bb);
		a.splice(beg2, aa);

		std::cout << "После вызова: " << std::endl;
		print_4 (b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void splice( const_iterator pos, list& other, const_iterator it )" << RESET << std::endl;

		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		aa.push_back(99);
		aa.push_back(87);
		aa.push_back(1015);
		aa.push_back(9999);
		aa.push_back(1);

		bb.push_back(99);
		bb.push_back(87);
		bb.push_back(1015);
		bb.push_back(9999);
		bb.push_back(1);

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		std::cout << "std::list: size(b) " << b.size() << std::endl;
		std::cout << "std::list: size(bb) " << bb.size() << std::endl;
		std::cout << "ft::list: size(a) " << a.size() << std::endl;
		std::cout << "ft::list: size(aa) " << aa.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "std::list: ";
		std::list<int>::iterator beg3 = bb.begin();
		for (; beg3 != bb.end(); beg3++)
			std::cout << *beg3 << " ";
		std::cout << std::endl;
		std::cout << "ft::list:  ";
		ft::list<int>::iterator beg4 = aa.begin();
		for (; beg4 != aa.end(); beg4++)
			std::cout << *beg4 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;

		beg1++;
		beg2++;
		beg3++;
		beg4++;

		b.splice(beg1, bb, beg3);
		a.splice(beg2, aa, beg4);

		std::cout << "После вызова: " << std::endl;
		print_4 (b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "remove if, remove" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		a.remove_if(cmp);
		b.remove_if(cmp);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);

		a.remove(2500);
		b.remove(2500);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);

		a.remove(20);
		b.remove(20);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void unique(void)" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1000);
		a.push_back(1000);
		a.push_back(1500);
		a.push_back(1000);
		a.push_back(1000);
		a.push_back(2000);
		a.push_back(2000);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1000);
		b.push_back(1000);
		b.push_back(1500);
		b.push_back(1000);
		b.push_back(1000);
		b.push_back(2000);
		b.push_back(2000);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		a.unique();
		b.unique();

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void unique( BinaryPredicate p )" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(1000);
		a.push_back(1000);
		a.push_back(1000);
		a.push_back(1500);
		a.push_back(1000);
		a.push_back(1000);
		a.push_back(2000);
		a.push_back(2000);
		a.push_back(2000);
		a.push_back(2500);
		a.push_back(3000);

		b.push_back(1000);
		b.push_back(1000);
		b.push_back(1000);
		b.push_back(1500);
		b.push_back(1000);
		b.push_back(1000);
		b.push_back(2000);
		b.push_back(2000);
		b.push_back(2000);
		b.push_back(2500);
		b.push_back(3000);


		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		a.unique(cmp_2);
		b.unique(cmp_2);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void sort(void)" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(999);
		a.push_back(1256);
		a.push_back(1000);
		a.push_back(1500);
		a.push_back(433);
		a.push_back(1);
		a.push_back(487);
		a.push_back(2589);
		a.push_back(30);

		b.push_back(999);
		b.push_back(1256);
		b.push_back(1000);
		b.push_back(1500);
		b.push_back(433);
		b.push_back(1);
		b.push_back(487);
		b.push_back(2589);
		b.push_back(30);


		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		a.sort();
		b.sort();

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void sort(Compare comp)" << RESET << std::endl;

		ft::list<int> a;
		std::list<int> b;

		a.push_back(999);
		a.push_back(1256);
		a.push_back(1000);
		a.push_back(1500);
		a.push_back(433);
		a.push_back(1);
		a.push_back(487);
		a.push_back(2589);
		a.push_back(30);

		b.push_back(999);
		b.push_back(1256);
		b.push_back(1000);
		b.push_back(1500);
		b.push_back(433);
		b.push_back(1);
		b.push_back(487);
		b.push_back(2589);
		b.push_back(30);


		std::cout << "До вызова: " << std::endl;

		print_two(b, a);

		a.sort(compare<int>);
		b.sort(compare<int>);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << GREEN "Non member overload: == != < <= > >=" << RESET << std::endl;
		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		print_4(b, bb, a, aa);

		std::cout << "------------------" << std::endl;
		std::cout << "ft::list  == " << (a == aa) << std::endl;
		std::cout << "std::list == " << (b == bb) << std::endl;
		std::cout << "ft::list  != " << (a != aa) << std::endl;
		std::cout << "std::list != " << (b != bb) << std::endl;
		std::cout << "ft::list  <  " << (a < aa) << std::endl;
		std::cout << "std::list <  " << (b < bb) << std::endl;
		std::cout << "ft::list  <= " << (a <= aa) << std::endl;
		std::cout << "std::list <= " << (b <= bb) << std::endl;
		std::cout << "ft::list  >  " << (a > aa) << std::endl;
		std::cout << "std::list >  " << (b > bb) << std::endl;
		std::cout << "ft::list  >= " << (a >= aa) << std::endl;
		std::cout << "std::list >= " << (b >= bb) << std::endl;
		std::cout << "------------------" << std::endl;
		getchar();
		std::cout <<  "\033c";

		a.push_back(10);
		a.push_back(10);

		b.push_back(10);
		b.push_back(10);

		aa.push_back(10);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		std::cout << "------------------" << std::endl;
		std::cout << "ft::list  == " << (a == aa) << std::endl;
		std::cout << "std::list == " << (b == bb) << std::endl;
		std::cout << "ft::list  != " << (a != aa) << std::endl;
		std::cout << "std::list != " << (b != bb) << std::endl;
		std::cout << "ft::list  <  " << (a < aa) << std::endl;
		std::cout << "std::list <  " << (b < bb) << std::endl;
		std::cout << "ft::list  <= " << (a <= aa) << std::endl;
		std::cout << "std::list <= " << (b <= bb) << std::endl;
		std::cout << "ft::list  >  " << (a > aa) << std::endl;
		std::cout << "std::list >  " << (b > bb) << std::endl;
		std::cout << "ft::list  >= " << (a >= aa) << std::endl;
		std::cout << "std::list >= " << (b >= bb) << std::endl;
		std::cout << "------------------" << std::endl;
		getchar();
		std::cout <<  "\033c";

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();
		a.push_back(10);
		a.push_back(10);
		a.push_back(10);

		b.push_back(10);
		b.push_back(10);
		b.push_back(10);

		aa.push_back(10);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		std::cout << "------------------" << std::endl;
		std::cout << "ft::list  == " << (a == aa) << std::endl;
		std::cout << "std::list == " << (b == bb) << std::endl;
		std::cout << "ft::list  != " << (a != aa) << std::endl;
		std::cout << "std::list != " << (b != bb) << std::endl;
		std::cout << "ft::list  <  " << (a < aa) << std::endl;
		std::cout << "std::list <  " << (b < bb) << std::endl;
		std::cout << "ft::list  <= " << (a <= aa) << std::endl;
		std::cout << "std::list <= " << (b <= bb) << std::endl;
		std::cout << "ft::list  >  " << (a > aa) << std::endl;
		std::cout << "std::list >  " << (b > bb) << std::endl;
		std::cout << "ft::list  >= " << (a >= aa) << std::endl;
		std::cout << "std::list >= " << (b >= bb) << std::endl;
		std::cout << "------------------" << std::endl;
		getchar();
		std::cout <<  "\033c";

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();

		a.push_back(10);
		a.push_back(100);

		b.push_back(10);
		b.push_back(100);

		aa.push_back(10);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		print_cmp(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();

		a.push_back(10);
		a.push_back(100);
		a.push_back(10);

		b.push_back(10);
		b.push_back(100);
		b.push_back(10);

		aa.push_back(10);
		aa.push_back(10);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(10);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		print_cmp(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();

		a.push_back(10);
		a.push_back(10);

		b.push_back(10);
		b.push_back(10);

		aa.push_back(10);
		aa.push_back(100);

		bb.push_back(10);
		bb.push_back(100);

		print_4(b, bb, a, aa);

		print_cmp(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();

		a.push_back(10);
		a.push_back(10);
		a.push_back(10);

		b.push_back(10);
		b.push_back(10);
		b.push_back(10);

		aa.push_back(10);
		aa.push_back(100);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(100);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		print_cmp(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();

		aa.push_back(10);
		aa.push_back(100);
		aa.push_back(10);

		bb.push_back(10);
		bb.push_back(100);
		bb.push_back(10);

		print_4(b, bb, a, aa);

		print_cmp(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";

		a.clear();
		b.clear();
		aa.clear();
		bb.clear();

		a.push_back(10);
		a.push_back(100);
		a.push_back(10);

		b.push_back(10);
		b.push_back(100);
		b.push_back(10);

		print_4(b, bb, a, aa);

		print_cmp(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << GREEN << "NONMEMBER swap" << RESET << std::endl;

		ft::list<int> a;
		ft::list<int> aa;
		std::list<int> b;
		std::list<int> bb;

		a.push_back(1);
		a.push_back(1);
		a.push_back(1);
		a.push_back(1);
		a.push_back(1);

		aa.push_back(2);
		aa.push_back(2);
		aa.push_back(2);
		aa.push_back(2);
		aa.push_back(2);

		b.push_back(1);
		b.push_back(1);
		b.push_back(1);
		b.push_back(1);
		b.push_back(1);

		bb.push_back(2);
		bb.push_back(2);
		bb.push_back(2);
		bb.push_back(2);
		bb.push_back(2);

		std::cout << "До вызова: " << std::endl;

		print_4(b, bb, a, aa);

		ft::swap(a, aa);
		swap(b, bb);

		std::cout << "После вызова: " << std::endl;

		print_4(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
		return (0);
	}

}