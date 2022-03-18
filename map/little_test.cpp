
#include <map>
#include "Map.hpp"
#include <iostream>
#include <ctime>
#include <random>
#include "../vector/Vector.hpp"
#include <stack>

template <class Ct>
void	print_content(Ct map, bool is_print) {
	typedef		typename Ct::iterator				iterator_type;

	map.print_tree();
	if (is_print)
		for (iterator_type it = map.begin() ; it != map.end() ; ++it)
			std::cout << it->first << " " << it->second << std::endl;
}

template <class Ct>
void	print_reverse_content(Ct map, bool is_print) {
	typedef		typename Ct::reverse_iterator		reverse_iterator_type;

	map.print_tree();
	if (is_print)
		for (reverse_iterator_type it = map.rbegin() ; it != map.rend() ; ++it)
			std::cout << it->first << " " << it->second << std::endl;
}

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
		it--;
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
test.print_tree();
		std::cout << std::endl;
	}

	std::cout << "//////////////////////////INSERT////////////////////////////////" << std::endl;
	typedef		ft::map<int, std::string>::value_type			value_type;
	{

		ft::map<int, std::string>			test;

		test.insert(value_type(3, "caca"));

		std::cout << "#### First state : "; test.print_tree();

		std::cout << "#### Insert 8: ";
		test.insert(value_type(8, "caca"));
		print_content(test, false);
		std::cout << std::endl;


		std::cout << "#### Insert 5: ";
		test.insert(value_type(5, "pipi"));
		print_reverse_content(test, false);
		std::cout << std::endl;

		 std::cout << "#### Insert 1: ";
		 test.insert(value_type(1, "crotte"));
		 print_reverse_content(test, false);
		 std::cout << std::endl;


		 std::cout << "#### Insert 2: ";
		 test.insert(value_type(2, "crotte"));
		 print_reverse_content(test, false);
		 std::cout << std::endl;

		 std::cout << "#### Insert 7: ";
		 test.insert(value_type(7, "zigouigoui"));
		 print_reverse_content(test, false);
		 std::cout << std::endl;

		 std::cout << "#### Insert 9: ";
		 test.insert(value_type(9, "popo"));
		 print_content(test, false);

		 std::cout << std::endl;

		 std::cout << "#### Insert 4: ";
		 test.insert(value_type(4, "popo"));
		 print_content(test, false);

		 std::cout << std::endl;

		 std::cout << "#### Insert 7: ";
		 test.insert(value_type(7, "popo"));
		 print_content(test, false);
		 std::cout << std::endl;

		 std::cout << "#### Insert 6: ";
		 test.insert(value_type(6, "popo"));
		 print_content(test, false);
	}
	{
		// typedef		ft::map<int, std::string>::iterator				iterator_type;
		typedef		std::vector<int>::iterator				iterator_vector;
		std::cout << "//////////////////////////CRASHING INSERT/////////////////////////" << std::endl;
		srand(time(NULL));

		ft::map<int, std::string>			test;
		int	array[] = {5, 11, 16, 1, 3, 7, 8, 10};

		std::vector<int> vec_values(array, array + sizeof(array) / sizeof(array[0]));

		for (iterator_vector it = vec_values.begin() ; it != vec_values.end() ; ++it) {
			test.insert(test.begin(), value_type(*it, "lol"));
			print_content(test, false);
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
		}
		{
			std::cout << "//////////////////////////INSERT BEGINING/////////////////////////" << std::endl;
			ft::map<int, std::string>			test2;
			for (iterator_vector it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test2.insert(value_type(*it, "lol"));
				print_content(test2, false);
				std::cout << " IS VALID ? : " <<  test2._is_valid() << std::endl;
			}
		}
	}
	std::cout << "//////////////////////////RANDOM INSERT/////////////////////////" << std::endl;
	{
		srand(time(NULL));
		ft::map<int, std::string>			test;
		std::map<int, std::string>				test_off;
		for (int i = 1 ; i < 50 ; ++i) {
			int	new_nb = rand() % 20 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			test_off[new_nb] = "mdr";
			print_content(test, false);
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
		}
		// Test segfault on end() iterator
		// std::map<int, std::string>::iterator	it_off = test_off.end();
		// std::cout << (it_off->second) << std::endl;
	}

	std::cout << "//////////////////////////LOOKUP////////////////////////////////" << std::endl;
	{
		// COUNT
		ft::map<int, std::string>			test;
		std::map<int, std::string>			test_off;
		std::stack<int>						stack;
		for (int i = 1 ; i < 20 ; ++i) {
			int	new_nb = rand() % 20 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			test_off[new_nb] = "mdr";
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			std::cout << " #### count on : " << stack.top() << " = ";
			std::cout << test.count(stack.top()) << " | ";
			std::cout << test_off.count(stack.top()) << std::endl;
			stack.pop();
		}
	} {
		// Find
		ft::map<int, std::string>			test;
		std::map<int, std::string>				test_off;
		std::stack<int>						stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			test_off[new_nb] = "mdr2";
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			std::cout << " #### find on : " << stack.top() << " = " << std::endl;
			ft::map<int, std::string>::iterator		it =	test.find(stack.top());
			std::map<int, std::string>::iterator	it2 =	test_off.find(stack.top());
			std::cout << " Reverse order [";
			for ( ; it != test.begin() ; --it, --it2)
				std::cout << " | " << it->first << " " << it2->first;
			std::cout << "] " << std::endl;
			std::cout << " Ordered [";
			for ( ; it != test.end() ; ++it, ++it2)
				std::cout << " | " << it->first << " " << it2->first;
			std::cout << "]" << std::endl;
			stack.pop();
		}
	} {
		// Find
		ft::map<int, std::string>			test;
		std::map<int, std::string>				test_off;
		std::stack<int>						stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			test_off[new_nb] = "mdr2";
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			std::cout << " #### find on : " << stack.top() << " = " << std::endl;
			ft::map<int, std::string>::const_iterator		it =	test.find(stack.top());
			std::map<int, std::string>::const_iterator		it2 =	test_off.find(stack.top());
			std::cout << " Reverse order [";
			for ( ; it != test.begin() ; --it, --it2)
				std::cout << " | " << it->first << " " << it2->first;
			std::cout << "] " << std::endl;
			std::cout << " Ordered [";
			for ( ; it != test.end() ; ++it, ++it2)
				std::cout << " | " << it->first << " " << it2->first;
			std::cout << "]" << std::endl;
			stack.pop();
		}
	}



}
