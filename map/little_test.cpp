
#include <map>
#include "Map.hpp"
#include <iostream>

int main() {
	{
		// std::map<int, char*>		test;
		// test[1] = "manger des frites";
		// test[2] = "manger des moules";
		// test[3] = "manger des peches";
		// std::map<int, char*>::iterator	it = test.begin();
		//
//
		// std::map<int, char*>::value_compare  comp_obj = test.value_comp();
		// std::map<int, char*>::value_compare  comp_obj2(comp_obj);
		// comp_obj = comp_obj2;
//
		// std::cout << std::boolalpha;
		// std::cout << comp_obj(*(test.begin()), *test.rbegin()) << std::endl;
		// std::cout << comp_obj2(*(test.begin()), *test.rbegin()) << std::endl;
	}
	{
		std::cout << std::boolalpha;
		ft::map<int, std::string>			test;
		ft::map<int, std::string>::value_compare  comp_obj = test.value_comp();
		ft::map<int, std::string>::value_compare  comp_obj2(comp_obj);
		comp_obj = comp_obj2;

		test._create_tree_test("manger", "des", "frites");

		ft::map<int, std::string>::iterator	it = test.begin();
		while (it != test.end()) {
			std::cout << it->first << std::endl;
			std::cout << it->second << std::endl;
			++it;
		}
	} {
		ft::map<int, std::string>			test;
		test._create_tree_test("manger", "des", "frites");
		ft::map<int, std::string>::iterator	it = test.end();
		--it;
		while (it != test.begin()) {
			std::cout << it->first << std::endl;
			std::cout << it->second << std::endl;
			--it;
		}
	}{
		ft::map<int, std::string>			test;
		test._create_tree_test("manger", "des", "frites");
		ft::map<int, std::string>::reverse_iterator	it = test.rbegin();
		while (it != test.rend()) {
			std::cout << it->first << std::endl;
			std::cout << it->second << std::endl;
			++it;
		}
	}



}
