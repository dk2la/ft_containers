#include "../srcs/map.hpp"

#define RED "\033[1;31m"
#define GREEN "\033[1;33m"
#define RESET "\033[0m"

int     list_test(void);
int     vector_test(void);
int     map_test(void);
int     stack_test(void);
int     queue_test(void);

int     main(void) {

	int a;

	while (true)
	{
		std::cout << GREEN << "Выберите тест: " << RED << "1. list, \
2. Vector, 3. Map, 4. Stack, 5. Queue, 6. exit" << RESET << std::endl;
		std::cin >> a;
//		if (a == 1)
//			list_test();
//		else if (a == 2)
//			vector_test();
		if (a == 3)
			map_test();
//		else if (a == 4)
//			stack_test();
//		else if (a == 5)
//			queue_test();
		else if (a == 6)
			return (0);
		else
			continue;
	}
}