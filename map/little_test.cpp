
#include <map>
#include "Map.hpp"
#include <iostream>

int main() {
	std::cout << std::boolalpha;

	{
		ft::map<int, std::string>			test;
		test._create_tree_test("manger", "des", "frites");

		ft::map<int, std::string>::iterator	it = test.begin();
		while (it != test.end()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		--it;
		while (it != test.begin()) {
			std::cout << it->first << " " << it->second << std::endl;
			--it;
		}
		std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
	} {
		ft::map<int, std::string>			test;
		test._create_tree_test("manger", "des", "frites");
		ft::map<int, std::string>::iterator	it = test.end();
		--it;
		while (it != test.begin()) {
			std::cout << it->first << " " << it->second << std::endl;
			it--;
		}
		std::cout << it->first << " " << it->second << std::endl;
		while (it != test.end()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;

	} {
		ft::map<int, std::string>			test;
		test._create_tree_test("manger", "des", "frites");
		ft::map<int, std::string>::reverse_iterator	it = test.rbegin();
		while (it != test.rend()) {
			std::cout << it->first << " " << it->second << std::endl;
			it++;
		}
		while (it != test.rbegin()) {
			std::cout << it->first << " " << it->second << std::endl;
			--it;
		}
		std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
	} {
		ft::map<int, std::string>			test;
		test._create_tree_test("manger", "des", "frites");
		ft::map<int, std::string>::reverse_iterator	it = test.rend();
		it--;
		while (it != test.rbegin()) {
			std::cout << it->first << " " << it->second << std::endl;
			--it;
		}
		std::cout << it->first << " " << it->second << std::endl;
		while (it != test.rend()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;
	}
	std::cout << "////////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "//////////////////////////DOUBLETREE////////////////////////////" << std::endl;
	std::cout << "//////////////////////////PREDECESSOR///////////////////////////" << std::endl;
	{
		std::cout << "  In Order " << std::endl;
		ft::map<int, std::string>			test;

		test._create_double_tree_predecessor_test("manger", "des", "frites");

		ft::map<int, std::string>::iterator	it = test.begin();
		while (it != test.end()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;
	}
		std::cout << "  Reverse order from end() - 1 to begin() " << std::endl;
	{
		ft::map<int, std::string>			test;
		test._create_double_tree_predecessor_test("manger", "des", "frites");
		ft::map<int, std::string>::iterator	it = test.end();
		--it;
		while (it != test.begin()) {
			std::cout << it->first << " " << it->second << std::endl;
			--it;
		}
		std::cout << std::endl;
	}
		std::cout << "  In Order with reverse_iterator " << std::endl;
	{
		ft::map<int, std::string>			test;
		test._create_double_tree_predecessor_test("manger", "des", "frites");
		ft::map<int, std::string>::reverse_iterator	it = test.rbegin();
		while (it != test.rend()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;
	}
		std::cout << "  Reverse order from rend() - 1 to rbegin() " << std::endl;
	{
		ft::map<int, std::string>			test;
		test._create_double_tree_predecessor_test("manger", "des", "frites");
		ft::map<int, std::string>::reverse_iterator	it = test.rend();
		--it;
		while (it != test.rbegin()) {
			std::cout << it->first << " " << it->second << std::endl;
			--it;
		}
		std::cout << std::endl;
	}
	std::cout << "//////////////////////////SUCCESSOR/////////////////////////////" << std::endl;
	{
		std::cout << "  In Order " << std::endl;

		ft::map<int, std::string>			test;
		test._create_double_tree_successor_test("manger", "des", "frites");
		ft::map<int, std::string>::iterator	it = test.begin();
		while (it != test.end()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;
	}
		std::cout << "  Reverse order from end() - 1 to begin() " << std::endl;
	{
		ft::map<int, std::string>			test;
		test._create_double_tree_successor_test("manger", "des", "frites");
		ft::map<int, std::string>::iterator	it = test.end();
		--it;
		while (it != test.begin()) {
			std::cout << it->first << " " << it->second << std::endl;
			--it;
		}
		std::cout << std::endl;
	}
		std::cout << "  In Order with reverse_iterator " << std::endl;
	{
		ft::map<int, std::string>			test;
		test._create_double_tree_successor_test("manger", "des", "frites");
		ft::map<int, std::string>::reverse_iterator	it = test.rbegin();
		while (it != test.rend()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;
	}
		std::cout << "  Reverse order from rend() - 1 to rbegin() " << std::endl;
	{
		ft::map<int, std::string>			test;
		test._create_double_tree_successor_test("manger", "des", "frites");
		ft::map<int, std::string>::reverse_iterator	it = test.rend();
		--it;
		while (it != test.rbegin()) {
			std::cout << it->first << " " << it->second << std::endl;
			--it;
		}
		std::cout << std::endl;
	}

	std::cout << "//////////////////////////INSERT////////////////////////////////" << std::endl;
	{
		typedef		ft::map<int, std::string>::value_type	value_type;
		ft::map<int, std::string>			test;
		test._create_tree_test("manger", "des", "frites");
		ft::map<int, std::string>::iterator		it = test.begin();
		test.insert(value_type(8, "caca"));
		while (it != test.end()) {
			std::cout << it->first << " " << it->second << std::endl;
			++it;
		}
		test.print_tree();
	}

}
