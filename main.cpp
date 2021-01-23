#include <iostream>
//#include "list.hpp"
#include "vector.hpp"
//#include "map.hpp"
//#include "stack.hpp"
//#include "queue.hpp"
//#include <stack>

///*	LIST COMPILES	*/
//
//void ftList() {
//	ft::list<std::string> f;
//
//	f.push_back("LIST ");
//	f.push_back("compiles ");
//	f.push_back("successfully! ");
//	f.push_back("Go ");
//	f.push_back("check ");
//	f.push_back("unit ");
//	f.push_back("tests!");
//
//	ft::list<std::string>::iterator itf;
//	ft::list<std::string>::iterator itfe = f.end();
//	for (itf = f.begin(); itf != itfe; ++itf) {
//		std::cout << *itf;
//	}
//	std::cout << std::endl << std::endl;
//}
//
/*	VECTOR COMPILES	*/

void ftVector() {
	ft::vector<std::string> v;

//	std::cout << "HERE: " << std::endl;
//	v.push_back("VECTOR ");
//	std::cout << "HERE: " << std::endl;
//	v.push_back("compiles ");
//	std::cout << "HERE: "  << std::endl;
//	v.push_back("successfully! ");
//	std::cout << "HERE: "  << std::endl;
//	v.push_back("Go ");
//	std::cout << "HERE: "  << std::endl;
//	v.push_back("check ");
//	std::cout << "HERE: "  << std::endl;
//	v.push_back("unit ");
//	std::cout << "HERE: "  << std::endl;
//	v.push_back("tests!");
//	std::cout << "HERE: "  << std::endl;
	v.push_back("VECTOR ");
	std::cout << v.size() << std::endl;
	v.push_back("compiles ");
	std::cout << "HERE: " << v.back() << std::endl;
	v.push_back("successfully! ");
	std::cout << "HERE: " << v.back() << std::endl;
	v.push_back("Go ");
	std::cout << "HERE: " << v.back() << std::endl;
	v.push_back("check ");
	std::cout << "HERE: " << v.back() << std::endl;
	v.push_back("unit ");
	std::cout << "HERE: " << v.back() << std::endl;
	v.push_back("tests!");
	std::cout << "HERE: " << v.back() << std::endl;
	v.insert(3, "lol");

	ft::vector<std::string>::iterator itv;
	ft::vector<std::string>::iterator itve = v.end();
	for (itv = v.begin(); itv != itve; ++itv)
	{
		std::cout << *itv;
	}
	std::cout << std::endl << std::endl;
}

///*	MAP COMPILES	*/
//
//void ftMap() {
//	ft::map<int, std::string> m;
//
//	m.insert(std::make_pair(1, "MAP "));
//	m.insert(std::make_pair(2, "compiles "));
//	m.insert(std::make_pair(3, "successfully! "));
//	m.insert(std::make_pair(4, "Go "));
//	m.insert(std::make_pair(5, "check "));
//	m.insert(std::make_pair(6, "unit "));
//	m.insert(std::make_pair(7, "tests!"));
//
//	ft::map<int, std::string>::iterator itm;
//	ft::map<int, std::string>::iterator itme = m.end();
//	for (itm = m.begin(); itm != itme; ++itm) {
//		std::cout << itm->second;
//	}
//	std::cout << std::endl << std::endl;
//}
//
///*	STACK COMPILES	*/
//
//void ftStack() {
//	ft::stack<std::string> s;
//	std::stack<std::string> s1;
//
//	s.push("STACK ");
//	std::cout << "HERE: " << s.top() << std::endl;
//	s.push("compiles ");
//	std::cout << "HERE: " << s.top() << std::endl;
//	s.push("successfully! ");
//	std::cout << "HERE: " << s.top() << std::endl;
//	s.push("Go ");
//	std::cout << "HERE: " << s.top() << std::endl;
//	s.push("check ");
//	std::cout << "HERE: " << s.top() << std::endl;
//	s.push("unit ");
//	std::cout << "HERE: " << s.top() << std::endl;
//	s.push("tests!");
//	std::cout << "HERE: " << s.top() << std::endl;
//
//	while (!s.empty()) {
//		std::cout << "HERE: " << s.top() << std::endl;
//		std::cout << s.top();
//		s.pop();
//	}
//	std::cout << std::endl << std::endl;
//
//	s1.push("STACK ");
//	s1.push("compiles ");
//	s1.push("successfully! ");
//	s1.push("Go ");
//	s1.push("check ");
//	s1.push("unit ");
//	s1.push("tests!");
//
//	while (!s1.empty()) {
//		std::cout << s1.top();
//		s1.pop();
//	}
//	std::cout << std::endl << std::endl;
//}

/*	QUEUE COMPILES	*/

//void ftQueue() {
//	ft::queue<std::string> q;
//
//	q.push("QUEUE ");
//	std::cout << "HERE: " << q.back() << std::endl;
//	q.push("compiles ");
//	std::cout << "HERE: " << q.back() << std::endl;
//	q.push("successfully! ");
//	std::cout << "HERE: " << q.back() << std::endl;
//	q.push("Go ");
//	std::cout << "HERE: " << q.back() << std::endl;
//	q.push("check ");
//	std::cout << "HERE: " << q.back() << std::endl;
//	q.push("unit ");
//	std::cout << "HERE: " << q.back() << std::endl;
//	q.push("tests!");
//	std::cout << "HERE: " << q.back() << std::endl;
//
//	while (!q.empty()) {
//		std::cout << q.front();
//		q.pop();
//	}
//	std::cout << std::endl;
//}

int main()
{
//	ftList();
	ftVector();
//	ftMap();
//	ftStack();
//	ftQueue();

	return 0;
}