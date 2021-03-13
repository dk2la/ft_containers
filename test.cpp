#include <map>
#include <iostream>

int		main() {
	std::map<int, int> a;
	std::map<int, int>::iterator it1 = a.begin();
	std::map<int, int>::iterator it2 = a.eend();

	std::cout << (it1 == it2) << std::endl;
	return 0;
}