#include <iostream>
#include <queue>
#include "../srcs/queue.hpp"

#define RED "\033[1;31m"
#define GREEN "\033[1;33m"
#define RESET "\033[0m"

void pop_2(std::queue <int> a, ft::queue <int> b) {

	std::cout << "std size: " << a.size() << std::endl;
	std::cout << "ft size: " << b.size() << std::endl;
	std::cout << "std empty: " << a.empty() << std::endl;
	std::cout << "ft empty: " << b.empty() << std::endl << std::endl;
	std::cout << "std::queue: ";
	while (a.size())
	{
		std::cout << "front: " << a.front() << " back: " << a.back() << " | ";
		a.pop();
	}
	std::cout << std::endl;
	std::cout << "ft::queue:  ";
	while (b.size())
	{
		std::cout << "front: " << b.front() << " back: " << b.back() << " | ";
		b.pop();
	}
	std::cout << std::endl;
	std::cout << "std empty: " << a.empty() << std::endl;
	std::cout << "ft empty: " << b.empty() << std::endl;
}

int queue_test(void) {
	{
		std::cout <<  "\033c";
		std::cout << GREEN << "*** QUEUE ***" << RESET << std::endl;
		std::cout << RED << "Создание без аргументов" << RESET << std::endl;
		std::queue <int> a;
		ft::queue <int> b;

		a.push(10);
		a.push(20);
		a.push(30);
		a.push(40);
		a.push(50);
		a.push(60);

		b.push(10);
		b.push(20);
		b.push(30);
		b.push(40);
		b.push(50);
		b.push(60);

		pop_2(a, b);
		getchar();
		getchar();
		std::cout <<  "\033c";

	}
	{
		std::cout << std::endl << GREEN << "Non member overloads test: == != > >= < <=" << RESET << std::endl;
		std::queue <int> a;
		std::queue <int> aa;
		ft::queue <int> b;
		ft::queue <int> bb;

		a.push(10);
		a.push(20);
		a.push(30);
		a.push(40);
		a.push(50);
		a.push(60);
		aa.push(10);
		aa.push(20);
		aa.push(30);
		aa.push(40);
		aa.push(50);
		aa.push(60);

		b.push(10);
		b.push(20);
		b.push(30);
		b.push(40);
		b.push(50);
		b.push(60);
		bb.push(10);
		bb.push(20);
		bb.push(30);
		bb.push(40);
		bb.push(50);
		bb.push(60);

		std::cout << "std::queue: == " << (a == aa) << std::endl;
		std::cout << "ft::queue:  == " << (a == aa) << std::endl;
		std::cout << "std::queue: >  " << (a > aa) << std::endl;
		std::cout << "ft::queue:  >  " << (a > aa) << std::endl;
		std::cout << "std::queue: >= " << (a >= aa) << std::endl;
		std::cout << "ft::queue:  >= " << (a >= aa) << std::endl;
		std::cout << "std::queue: <  " << (a < aa) << std::endl;
		std::cout << "ft::queue:  <  " << (a < aa) << std::endl;
		std::cout << "std::queue: <= " << (a <= aa) << std::endl;
		std::cout << "ft::queue:  <= " << (a <= aa) << std::endl;
		std::cout << "std::queue: != " << (a != aa) << std::endl;
		std::cout << "ft::queue:  != " << (a != aa) << std::endl;

		std::cout << std::endl << "Первые значения: " << std::endl;
		pop_2(a, b);
		std::cout << std::endl << "Вторые значения: " << std::endl;
		pop_2(aa, bb);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << "----------" << std::endl;
		std::queue <int> a;
		std::queue <int> aa;
		ft::queue <int> b;
		ft::queue <int> bb;

		a.push(10);
		a.push(20);
		a.push(30);
		a.push(40);
		a.push(50);
		a.push(60);
		aa.push(10);
		aa.push(10);
		aa.push(30);
		aa.push(40);
		aa.push(50);
		aa.push(60);

		b.push(10);
		b.push(20);
		b.push(30);
		b.push(40);
		b.push(50);
		b.push(60);
		bb.push(10);
		bb.push(10);
		bb.push(30);
		bb.push(40);
		bb.push(50);
		bb.push(60);

		std::cout << "std::queue: == " << (a == aa) << std::endl;
		std::cout << "ft::queue:  == " << (a == aa) << std::endl;
		std::cout << "std::queue: >  " << (a > aa) << std::endl;
		std::cout << "ft::queue:  >  " << (a > aa) << std::endl;
		std::cout << "std::queue: >= " << (a >= aa) << std::endl;
		std::cout << "ft::queue:  >= " << (a >= aa) << std::endl;
		std::cout << "std::queue: <  " << (a < aa) << std::endl;
		std::cout << "ft::queue:  <  " << (a < aa) << std::endl;
		std::cout << "std::queue: <= " << (a <= aa) << std::endl;
		std::cout << "ft::queue:  <= " << (a <= aa) << std::endl;
		std::cout << "std::queue: != " << (a != aa) << std::endl;
		std::cout << "ft::queue:  != " << (a != aa) << std::endl;

		std::cout << std::endl << "Первые значения: " << std::endl;
		pop_2(a, b);
		std::cout << std::endl << "Вторые значения: " << std::endl;
		pop_2(aa, bb);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << "----------" << std::endl;
		std::queue <int> a;
		std::queue <int> aa;
		ft::queue <int> b;
		ft::queue <int> bb;

		std::cout << "std::queue: == " << (a == aa) << std::endl;
		std::cout << "ft::queue:  == " << (a == aa) << std::endl;
		std::cout << "std::queue: >  " << (a > aa) << std::endl;
		std::cout << "ft::queue:  >  " << (a > aa) << std::endl;
		std::cout << "std::queue: >= " << (a >= aa) << std::endl;
		std::cout << "ft::queue:  >= " << (a >= aa) << std::endl;
		std::cout << "std::queue: <  " << (a < aa) << std::endl;
		std::cout << "ft::queue:  <  " << (a < aa) << std::endl;
		std::cout << "std::queue: <= " << (a <= aa) << std::endl;
		std::cout << "ft::queue:  <= " << (a <= aa) << std::endl;
		std::cout << "std::queue: != " << (a != aa) << std::endl;
		std::cout << "ft::queue:  != " << (a != aa) << std::endl;

		std::cout << std::endl << "Первые значения: " << std::endl;
		pop_2(a, b);
		std::cout << std::endl << "Вторые значения: " << std::endl;
		pop_2(aa, bb);
		getchar();
		std::cout <<  "\033c";
	}
	{
		std::cout << std::endl << "----------" << std::endl;
		std::queue <int> a;
		std::queue <int> aa;
		ft::queue <int> b;
		ft::queue <int> bb;

		a.push(10);
		a.push(20);
		a.push(30);

		aa.push(10);
		aa.push(10);
		aa.push(30);
		aa.push(40);
		aa.push(50);
		aa.push(60);

		b.push(10);
		b.push(20);
		b.push(30);

		bb.push(10);
		bb.push(10);
		bb.push(30);
		bb.push(40);
		bb.push(50);
		bb.push(60);

		std::cout << "std::queue: == " << (a == aa) << std::endl;
		std::cout << "ft::queue:  == " << (a == aa) << std::endl;
		std::cout << "std::queue: >  " << (a > aa) << std::endl;
		std::cout << "ft::queue:  >  " << (a > aa) << std::endl;
		std::cout << "std::queue: >= " << (a >= aa) << std::endl;
		std::cout << "ft::queue:  >= " << (a >= aa) << std::endl;
		std::cout << "std::queue: <  " << (a < aa) << std::endl;
		std::cout << "ft::queue:  <  " << (a < aa) << std::endl;
		std::cout << "std::queue: <= " << (a <= aa) << std::endl;
		std::cout << "ft::queue:  <= " << (a <= aa) << std::endl;
		std::cout << "std::queue: != " << (a != aa) << std::endl;
		std::cout << "ft::queue:  != " << (a != aa) << std::endl;

		std::cout << std::endl << "Первые значения: " << std::endl;
		pop_2(a, b);
		std::cout << std::endl << "Вторые значения: " << std::endl;
		pop_2(aa, bb);
		getchar();
		std::cout << "\033c";
	}
	return 0;
}
