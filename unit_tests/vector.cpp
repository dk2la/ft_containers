#include "../srcs/vector.hpp"
#include <iostream>
#include <vector>

#define RED "\033[1;31m"
#define GREEN "\033[1;33m"
#define RESET "\033[0m"

template<typename T>
bool compare(const T &x, const T& y)
{
	return (x < y);
}

void print_two (std::vector<int> &b, ft::vector<int> &a)
{
	std::cout << "ft::vector.size(): " << a.size() << std::endl;
	std::cout << "std::vector.size(): " << b.size() << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Значения:" << std::endl;
	std::cout << "std::vector: ";
	for (std::vector<int>::iterator beg = b.begin(); beg != b.end(); beg++)
		std::cout << *beg << " ";
	std::cout << std::endl;
	std::cout << "ft::vector:  ";
	for (ft::vector<int>::iterator beg = a.begin(); beg != a.end(); beg++)
		std::cout << *beg << " ";
	std::cout << std::endl;
	std::cout << "-------------------------" << std::endl;

}

void print_4 (std::vector<int> &b, std::vector<int> &bb, ft::vector<int> &a, ft::vector<int> &aa)
{
	std::cout << "std::vector: size(b) " << b.size() << std::endl;
	std::cout << "std::vector: size(bb) " << bb.size() << std::endl;
	std::cout << "ft::vector: size(a) " << a.size() << std::endl;
	std::cout << "ft::vector: size(aa) " << aa.size() << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "std::vector: ";
	std::vector<int>::iterator beg1 = b.begin();
	for (; beg1 != b.end(); beg1++)
		std::cout << *beg1 << " ";
	std::cout << std::endl;
	std::cout << "ft::vector:  ";
	ft::vector<int>::iterator beg2 = a.begin();
	for (; beg2 != a.end(); beg2++)
		std::cout << *beg2 << " ";
	std::cout << std::endl;
	std::cout << "std::vector: ";
	std::vector<int>::iterator beg3 = bb.begin();
	for (; beg3 != bb.end(); beg3++)
		std::cout << *beg3 << " ";
	std::cout << std::endl;
	std::cout << "ft::vector:  ";
	ft::vector<int>::iterator beg4 = aa.begin();
	for (; beg4 != aa.end(); beg4++)
		std::cout << *beg4 << " ";
	std::cout << std::endl;

	std::cout << "------------------" << std::endl;
}
void print_cmp(std::vector<int> &b, std::vector<int> &bb, ft::vector<int> &a, ft::vector<int> &aa)
{
	std::cout << "------------------" << std::endl;
	std::cout << "ft::vector  == " << (a == aa) << std::endl;
	std::cout << "std::vector == " << (b == bb) << std::endl;
	std::cout << "ft::vector  != " << (a != aa) << std::endl;
	std::cout << "std::vector != " << (b != bb) << std::endl;
	std::cout << "ft::vector  <  " << (a < aa) << std::endl;
	std::cout << "std::vector <  " << (b < bb) << std::endl;
	std::cout << "ft::vector  <= " << (a <= aa) << std::endl;
	std::cout << "std::vector <= " << (b <= bb) << std::endl;
	std::cout << "ft::vector  >  " << (a > aa) << std::endl;
	std::cout << "std::vector >  " << (b > bb) << std::endl;
	std::cout << "ft::vector  >= " << (a >= aa) << std::endl;
	std::cout << "std::vector >= " << (b >= bb) << std::endl;
	std::cout << "------------------" << std::endl;
}

int		vector_test(void)
{
	{
		std::cout <<  "\033c";
		std::cout << GREEN << "I. Constructors and assignation" << RESET << std::endl << std::endl;
		std::cout << RED << "Создание без аргументов" << RESET << std::endl;
		ft::vector<int> a;
		std::vector<int> b;

		std::cout << "ft::vector.size(): " << a.size() << std::endl;
		std::cout << "std::vector.size(): " << b.size() << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator())"<< RESET << std::endl;

		std::cout << "Count: 10" << std::endl;
		ft::vector<int> a(10);
		std::vector<int> b(10);

		print_two(b, a);

		std::cout << "Count: 0" << std::endl;
		ft::vector<int> a1(0);
		std::vector<int> b1(0);

		std::cout << "ft::vector.size(): " << a1.size() << std::endl;
		std::cout << "std::vector.size(): " << b1.size() << std::endl;

	}
	{
		std::cout  << std::endl  << "Count: 100, value 42" << std::endl;
		ft::vector<int> a(100, 42);
		std::vector<int> b(100, 42);

		print_two(b, a);
		getchar();
		std::cout << "\033c";
	}
	{
		std::cout << std::endl << RED << "vector(InputIt first, InputIt last, const Allocator &alloc = Allocator())" << RESET << std::endl;

		std::vector<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::vector<int> a(c.begin(), c.end());
		std::vector<int> b(c.begin(), c.end());

		print_two(b, a);
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << RED << "vector (const vector &x)" << RESET << std::endl;

		std::vector<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::vector<int> d;

		d.push_back(10);
		d.push_back(20);
		d.push_back(30);
		d.push_back(40);
		d.push_back(50);
		d.push_back(60);

		ft::vector<int> a(d);
		std::vector<int> b(c);

		print_two(b, a);
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << RED << "vector &operator=(const vector &other)" << RESET << std::endl;

		std::vector<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::vector<int> d;

		d.push_back(10);
		d.push_back(20);
		d.push_back(30);
		d.push_back(40);
		d.push_back(50);
		d.push_back(60);

		ft::vector<int> a;
		std::vector<int> b;

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
		std::cout << std::endl << RED << "void assign (size_type n, const value_type& val)" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;
		print_two(b, a);

		a.assign((size_t)10, 150);
		b.assign((size_t)10, 150);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void assign( InputIt first, InputIt last )" << RESET << std::endl;

		std::vector<int> c;

		c.push_back(10);
		c.push_back(20);
		c.push_back(30);
		c.push_back(40);
		c.push_back(50);
		c.push_back(60);

		ft::vector<int> a;
		std::vector<int> b;

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
		std::cout  << std::endl << GREEN << "II. Iterators" << RESET << std::endl << std::endl;
		std::cout << RED << "begin, end" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "std::vector: ";
		for (std::vector<int>::iterator beg = b.begin(); beg != b.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		for (ft::vector<int>::iterator beg = a.begin(); beg != a.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;

		std::cout << std::endl << RED  << "const begin, const end" << RESET << std::endl;
		std::vector<int>::const_iterator end = b.end();

		std::cout << "std::vector: ";
		for (std::vector<int>::const_iterator beg = b.begin(); beg != end; beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		for (ft::vector<int>::const_iterator beg = a.begin(); beg != a.end(); ++beg)
			std::cout << *beg << " ";

		std::cout << std::endl;
		std::cout << std::endl << RED << "rbegin, rend" << RESET << std::endl;
		std::cout << "std::vector: ";
		for (std::vector<int>::reverse_iterator beg = b.rbegin(); beg != b.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		for (ft::vector<int>::reverse_iterator beg = a.rbegin(); beg != a.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;

		std::cout << std::endl << RED << "const rbegin, const rend" << RESET << std::endl;
		std::cout << "std::vector: ";
		for (std::vector<int>::const_reverse_iterator beg = b.rbegin(); beg != b.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		for (ft::vector<int>::const_reverse_iterator beg = a.rbegin(); beg != a.rend(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << GREEN << "III. Capacity" << RESET << std::endl << std::endl;
		std::cout << RED << "empty, size, maxsize, capacity" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		std::cout << "std::vector: capacity " << b.capacity() << std::endl;
		std::cout << "ft::vector: capacity " << a.capacity() << std::endl;

		a.reserve(10);
		b.reserve(10);

		std::cout << "std::vector: capacity " << b.capacity() << std::endl;
		std::cout << "ft::vector: capacity " << a.capacity() << std::endl;


		a.reserve(10);
		b.reserve(10);

		std::cout << "std::vector: capacity " << b.capacity() << std::endl;
		std::cout << "ft::vector: capacity " << a.capacity() << std::endl;

		a.push_back(10);
		a.push_back(10);
		a.push_back(10);
		a.push_back(10);
		a.push_back(10);

		b.push_back(10);
		b.push_back(10);
		b.push_back(10);
		b.push_back(10);
		b.push_back(10);

		a.reserve(50);
		b.reserve(50);

		std::cout << "std::vector: capacity " << b.capacity() << std::endl;
		std::cout << "ft::vector: capacity " << a.capacity() << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}

	{
		std::cout <<  std::endl << GREEN << "IV. Elements access" << RESET << std::endl << std::endl;
		std::cout << RED << "reference front(void)" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		b.push_back(1000);
		std::cout << "std::vector: " << a.front() << std::endl;
		std::cout << "ft::vector: " << b.front() << std::endl;

		a.push_back(1500);
		b.push_back(1500);

		std::cout << "std::vector: " << a.front() << std::endl;
		std::cout << "ft::vector: " << b.front() << std::endl;

		a.push_back(2000);
		b.push_back(2000);

		std::cout << "std::vector: " << a.front() << std::endl;
		std::cout << "ft::vector: " << b.front() << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "const_reference front(void) const" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		b.push_back(1000);
		const int &aa = a.front();
		const int &bb = b.front();
		std::cout << "std::vector: " << aa << std::endl;
		std::cout << "ft::vector: " << bb << std::endl;

		a.push_back(1500);
		b.push_back(1500);
		const int &aaa = a.front();
		const int &bbb = b.front();
		std::cout << "std::vector: " << aaa << std::endl;
		std::cout << "ft::vector: " << bbb << std::endl;

		a.push_back(2000);
		b.push_back(2000);
		const int &aaaa = a.front();
		const int &bbbb = b.front();
		std::cout << "std::vector: " << aaaa << std::endl;
		std::cout << "ft::vector: " << bbbb << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "reference back(void)" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		b.push_back(1000);
		std::cout << "std::vector: " << a.back() << std::endl;
		std::cout << "ft::vector: " << b.back() << std::endl;

		a.push_back(1500);
		b.push_back(1500);

		std::cout << "std::vector: " << a.back() << std::endl;
		std::cout << "ft::vector: " << b.back() << std::endl;

		a.push_back(2000);
		b.push_back(2000);

		std::cout << "std::vector: " << a.back() << std::endl;
		std::cout << "ft::vector: " << b.back() << std::endl;
	}
	{
		std::cout << std::endl << RED << "const_reference back(void) const" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		b.push_back(1000);
		const int &aa = a.back();
		const int &bb = b.back();
		std::cout << "std::vector: " << aa << std::endl;
		std::cout << "ft::vector: " << bb << std::endl;

		a.push_back(1500);
		b.push_back(1500);
		const int &aaa = a.back();
		const int &bbb = b.back();
		std::cout << "std::vector: " << aaa << std::endl;
		std::cout << "ft::vector: " << bbb << std::endl;

		a.push_back(2000);
		b.push_back(2000);
		const int &aaaa = a.back();
		const int &bbbb = b.back();
		std::cout << "std::vector: " << aaaa << std::endl;
		std::cout << "ft::vector: " << bbbb << std::endl;
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "reference operator[](size_type i)" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);

		print_two(b, a);
		for (size_t i = 0; i < a.size(); i++)
			std::cout << "ft::vector [" << i << "] " << a[i] << std::endl;
		for (size_t i = 0; i < b.size(); i++)
			std::cout << "std::vector [" << i << "] " << b[i] << std::endl;
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << RED << "reference at (size_type n)" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);
		a.push_back(2500);
		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);
		b.push_back(2500);

		print_two(b, a);
		std::cout << "ft::vector " << a.at(2) << std::endl;
		std::cout << "std::vector " << b.at(2) << std::endl;

		const int &cref1 = a.at(2);
		const int &cref2 = b.at(2);

		std::cout << "ft::vector cref " << cref1 << std::endl;
		std::cout << "std::vector cref " << cref2 << std::endl;

		try
		{
			a.at(10);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		try
		{
			b.at(10);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << GREEN << "V. Modifiers" << RESET << std::endl << std::endl;
		std::cout << RED << "void clear(void)" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

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

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;

		std::cout << "std::vector: size " << b.size() << std::endl;
		std::cout << "ft::vector: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::vector: ";
		std::vector<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		ft::vector<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "------------------" << std::endl;

		b.insert(b.end(), 10000);
		a.insert(a.end(), 10000);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << RED << "void insert( iterator pos, size_type count, const T& value )" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;


		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;

		std::cout << "std::vector: size " << b.size() << std::endl;
		std::cout << "ft::vector: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::vector: ";
		std::vector<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		ft::vector<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "------------------" << std::endl;

		b.insert(b.begin(), 20, 10000);
		a.insert(a.begin(), 20, 10000);

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

		ft::vector<int> a;
		std::vector<int> b;
		std::vector<int> c;

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
		std::cout << "std::vector: ";
		for (std::vector<int>::iterator beg = c.begin(); beg != c.end(); beg++)
			std::cout << *beg << " ";
		std::cout << std::endl;

		std::cout << "До вызова: " << std::endl;
		std::cout << "std::vector: size " << b.size() << std::endl;
		std::cout << "ft::vector: size " << a.size() << std::endl;
		std::cout << "------------------" << std::endl;
		std::cout << "std::vector: ";
		std::vector<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		ft::vector<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;
		std::cout << "------------------" << std::endl;

		beg1 = b.begin();
		beg2 = a.begin();
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

		ft::vector<int> a;
		std::vector<int> b;

		a.push_back(1000);
		a.push_back(1500);
		a.push_back(2000);

		b.push_back(1000);
		b.push_back(1500);
		b.push_back(2000);

		std::cout << "До вызова: " << std::endl;

		std::cout << "std::vector: size " << b.size() << std::endl;
		std::cout << "ft::vector: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::vector: ";
		std::vector<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		ft::vector<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;

		b.erase(b.begin());
		a.erase(a.begin());

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "iterator erase( iterator first, iterator last )" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

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

		std::cout << "std::vector: size " << b.size() << std::endl;
		std::cout << "ft::vector: size " << a.size() << std::endl;

		std::cout << "------------------" << std::endl;
		std::cout << "std::vector: ";
		std::vector<int>::iterator beg1 = b.begin();
		for (; beg1 != b.end(); beg1++)
			std::cout << *beg1 << " ";
		std::cout << std::endl;
		std::cout << "ft::vector:  ";
		ft::vector<int>::iterator beg2 = a.begin();
		for (; beg2 != a.end(); beg2++)
			std::cout << *beg2 << " ";
		std::cout << std::endl;

		std::cout << "------------------" << std::endl;
		beg1 = b.begin();
		beg1++;
		beg2 = a.begin();
		beg2++;

		b.erase(beg1, b.end());
		a.erase(beg2, a.end());

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "pop_back" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

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
		a.pop_back();

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);

		b.pop_back();
		b.pop_back();
		a.pop_back();
		a.pop_back();

		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void resize( size_type count, T value = T() )" << RESET << std::endl;

		ft::vector<int> a;
		std::vector<int> b;

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

		a.resize((size_t)10);
		b.resize((size_t)10);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);

		a.resize((size_t)2);
		b.resize((size_t)2);

		std::cout << "После вызова: " << std::endl;
		print_two(b, a);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << RED << "void swap (vector &other)" << RESET << std::endl;

		ft::vector<int> a;
		ft::vector<int> aa;
		std::vector<int> b;
		std::vector<int> bb;

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
		std::cout << std::endl << GREEN << "Non member overload: == != < <= > >=" << RESET << std::endl;
		ft::vector<int> a;
		ft::vector<int> aa;
		std::vector<int> b;
		std::vector<int> bb;

		print_4(b, bb, a, aa);

		std::cout << "------------------" << std::endl;
		std::cout << "ft::vector  == " << (a == aa) << std::endl;
		std::cout << "std::vector == " << (b == bb) << std::endl;
		std::cout << "ft::vector  != " << (a != aa) << std::endl;
		std::cout << "std::vector != " << (b != bb) << std::endl;
		std::cout << "ft::vector  <  " << (a < aa) << std::endl;
		std::cout << "std::vector <  " << (b < bb) << std::endl;
		std::cout << "ft::vector  <= " << (a <= aa) << std::endl;
		std::cout << "std::vector <= " << (b <= bb) << std::endl;
		std::cout << "ft::vector  >  " << (a > aa) << std::endl;
		std::cout << "std::vector >  " << (b > bb) << std::endl;
		std::cout << "ft::vector  >= " << (a >= aa) << std::endl;
		std::cout << "std::vector >= " << (b >= bb) << std::endl;
		std::cout << "------------------" << std::endl;

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
		std::cout << "ft::vector  == " << (a == aa) << std::endl;
		std::cout << "std::vector == " << (b == bb) << std::endl;
		std::cout << "ft::vector  != " << (a != aa) << std::endl;
		std::cout << "std::vector != " << (b != bb) << std::endl;
		std::cout << "ft::vector  <  " << (a < aa) << std::endl;
		std::cout << "std::vector <  " << (b < bb) << std::endl;
		std::cout << "ft::vector  <= " << (a <= aa) << std::endl;
		std::cout << "std::vector <= " << (b <= bb) << std::endl;
		std::cout << "ft::vector  >  " << (a > aa) << std::endl;
		std::cout << "std::vector >  " << (b > bb) << std::endl;
		std::cout << "ft::vector  >= " << (a >= aa) << std::endl;
		std::cout << "std::vector >= " << (b >= bb) << std::endl;
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
		std::cout << "ft::vector  == " << (a == aa) << std::endl;
		std::cout << "std::vector == " << (b == bb) << std::endl;
		std::cout << "ft::vector  != " << (a != aa) << std::endl;
		std::cout << "std::vector != " << (b != bb) << std::endl;
		std::cout << "ft::vector  <  " << (a < aa) << std::endl;
		std::cout << "std::vector <  " << (b < bb) << std::endl;
		std::cout << "ft::vector  <= " << (a <= aa) << std::endl;
		std::cout << "std::vector <= " << (b <= bb) << std::endl;
		std::cout << "ft::vector  >  " << (a > aa) << std::endl;
		std::cout << "std::vector >  " << (b > bb) << std::endl;
		std::cout << "ft::vector  >= " << (a >= aa) << std::endl;
		std::cout << "std::vector >= " << (b >= bb) << std::endl;
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
		std::cout << "\033c";
	}
	{
		std::cout << std::endl << GREEN << "const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)" << RESET << std::endl;

		ft::vector<int> a;
		ft::vector<int> aa;
		std::vector<int> b;
		std::vector<int> bb;

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

		swap(a, aa);
		swap(b, bb);

		std::cout << "После вызова: " << std::endl;

		print_4(b, bb, a, aa);
		getchar();
		std::cout <<  "\033c";
		return (0);
	}

}