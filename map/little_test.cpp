
#include <map>
#include "Map.hpp"
#include <iostream>

int main() {
	{
		std::map<int, char*>		test;
		test[1] = "manger des frites";
		test[2] = "manger des moules";
		test[3] = "manger des peches";

		std::map<int, char*>::value_compare  comp_obj = test.value_comp();
		std::map<int, char*>::value_compare  comp_obj2(comp_obj);

		std::cout << std::boolalpha;
		std::cout << comp_obj(*(test.begin()), *test.rbegin()) << std::endl;
		std::cout << comp_obj2(*(test.begin()), *test.rbegin()) << std::endl;
	}
	{
		ft::map<int, char*>		test;
		ft::map<int, char*>::value_compare  comp_obj = test.value_comp();
		ft::map<int, char*>::value_compare  comp_obj2(comp_obj);

		std::cout << std::boolalpha;
	}

}
