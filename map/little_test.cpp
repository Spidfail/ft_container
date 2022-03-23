
#include <algorithm>
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
	std::cout << std::endl;
	{
		// typedef		ft::map<int, std::string>::iterator				iterator_type;
		typedef		std::vector<int>::iterator				iterator_vector;
		std::cout << "//////////////////////////CRASHING INSERT ?" << std::endl;
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
			std::cout << "//////////////////////////INSERT BEGINING" << std::endl;
			ft::map<int, std::string>			test2;
			for (iterator_vector it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test2.insert(value_type(*it, "lol"));
				print_content(test2, false);
				std::cout << " IS VALID ? : " <<  test2._is_valid() << std::endl;
			}
		}
		std::cout << std::endl;

	}
	std::cout << "//////////////////////////RANDOM INSERT" << std::endl;
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
		std::cout << std::endl;
	}

	std::cout << "//////////////////////////LOOKUP////////////////////////////////" << std::endl;
	{
		std::cout << "//////////////////////////COUNT" << std::endl;
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
		std::cout << std::endl;
	}

	{
		std::cout << "//////////////////////////FIND" << std::endl;
		std::map<int, std::string>			test_off;
		ft::map<int, std::string>			test;
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
			std::cout << "########## find on : " << stack.top() << std::endl;
			{
				std::cout << "iterators : " << std::endl;
				std::map<int, std::string>::iterator		it2 =	test_off.find(stack.top());
				ft::map<int, std::string>::iterator		it =	test.find(stack.top());
				std::cout << " Reverse order [";
				for ( ; it2 != test_off.begin() && it != test.begin() ; --it, --it2)
					std::cout << " | " << it2->first << " " << it->first;
				std::cout << "] " << std::endl;
				std::cout << " Ordered [";
				for ( ; it2 != test_off.end() && it != test.end() ; ++it, ++it2)
					std::cout << " | " << it2->first << " " << it->first;
				std::cout << "]" << std::endl;
			} {
				std::cout << "const_iterators : " << std::endl;
				std::map<int, std::string>::const_iterator		it2 =	test_off.find(stack.top());
				ft::map<int, std::string>::const_iterator		it =	test.find(stack.top());
				std::cout << " Reverse order [";
				for ( ; it2 != test_off.begin() && it != test.begin() ; --it, --it2)
					std::cout << " | " << it2->first << " " << it->first;
				std::cout << "] " << std::endl;
				std::cout << " Ordered [";
				for ( ; it2 != test_off.end() && it != test.end() ; ++it, ++it2)
					std::cout << " | " << it2->first << " " << it->first;
				std::cout << "]" << std::endl;
			}
			stack.pop();
			std::cout << std::endl << std::endl;
		}
	}

	{
		std::cout << "//////////////////////////EQUAL RANGE" << std::endl;
		typedef		std::map<int, std::string>::iterator			iterator_off;
		typedef		ft::map<int, std::string>::iterator				iterator;
		typedef		std::map<int, std::string>::const_iterator		const_iterator_off;
		typedef		ft::map<int, std::string>::const_iterator		const_iterator;
		std::map<int, std::string>				test_off;
		ft::map<int, std::string>				test;
		std::stack<int>							stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			test_off[new_nb] = "mdr2";
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			{
				std::cout << "########## equal range on : " << stack.top() << std::endl;
				std::cout << " iterators : ";
				std::pair<iterator_off, iterator_off>	pair_off =	test_off.equal_range(stack.top());
				ft::pair<iterator, iterator>			pair =	test.equal_range(stack.top());
				std::cout << " [";
				for ( ;  pair_off.first != pair_off.second && pair.first != pair.second
						; ++pair_off.first, ++pair.first)
					if (pair_off.second != test_off.end() && pair.second != test.end())
						std::cout << " | " <<  pair_off.second->first << " " << pair.second->first;
					else
						std::cout << " | " << " END " ;
				std::cout << "] ";
			} {
				std::cout << " const_iterators : ";
				std::pair<const_iterator_off, const_iterator_off>	pair_off =	test_off.equal_range(stack.top());
				ft::pair<const_iterator, const_iterator>			pair =	test.equal_range(stack.top());
				std::cout << " [";
				for ( ;  pair_off.first != pair_off.second && pair.first != pair.second
						; ++pair_off.first, ++pair.first)
					if (pair_off.second != test_off.end() && pair.second != test.end())
						std::cout << " | " <<  pair_off.second->first << " " << pair.second->first;
					else
						std::cout << " | " << " END " ;
				std::cout << "] " << std::endl;
			}
			stack.pop();
			std::cout << std::endl;
		}
	}

	{
		std::cout << "//////////////////////////Upper Bound" << std::endl;
		typedef		std::map<int, std::string>::iterator			iterator_off;
		typedef		ft::map<int, std::string>::iterator				iterator;
		typedef		std::map<int, std::string>::const_iterator		const_iterator_off;
		typedef		ft::map<int, std::string>::const_iterator		const_iterator;
		std::map<int, std::string>				test_off;
		ft::map<int, std::string>				test;
		std::stack<int>							stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			test_off[new_nb] = "mdr2";
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			{
				std::cout << "########## Upper Bound : " << stack.top() << std::endl;
				std::cout << " iterators : ";
				iterator_off	it_off =	test_off.upper_bound(stack.top());
				iterator	it =	test.upper_bound(stack.top());
				std::cout << " [";
				for ( ;  it_off != test_off.end() && it != test.end() 
						; ++it_off, ++it)
					std::cout << " | " <<  it_off->first << " " << it->first;
				std::cout << "] " << std::endl;
			} {
				std::cout << " const_iterators : ";
				const_iterator_off	it_off =	test_off.upper_bound(stack.top());
				const_iterator		it =	test.upper_bound(stack.top());
				std::cout << " [";
				for ( ;  it_off != test_off.end() && it != test.end() 
						; ++it_off, ++it)
					std::cout << " | " <<  it_off->first << " " << it->first;
				std::cout << "] " << std::endl;
			}
			stack.pop();
			std::cout << std::endl;
		}
	}

	{
		std::cout << "//////////////////////////Lower Bound" << std::endl;
		typedef		std::map<int, std::string>::iterator			iterator_off;
		typedef		ft::map<int, std::string>::iterator				iterator;
		typedef		std::map<int, std::string>::const_iterator		const_iterator_off;
		typedef		ft::map<int, std::string>::const_iterator		const_iterator;
		std::map<int, std::string>				test_off;
		ft::map<int, std::string>				test;
		std::stack<int>							stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			test_off[new_nb] = "mdr2";
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			{
				std::cout << "########## Lower Bound : " << stack.top() << std::endl;
				std::cout << " iterators : ";
				iterator_off	it_off =	test_off.lower_bound(stack.top());
				iterator	it =	test.lower_bound(stack.top());
				std::cout << " [";
				for ( ;  it_off != test_off.end() && it != test.end() 
						; ++it_off, ++it)
					std::cout << " | " <<  it_off->first << " " << it->first;
				std::cout << "] " << std::endl;
			} {
				std::cout << " const_iterators : ";
				const_iterator_off	it_off =	test_off.lower_bound(stack.top());
				const_iterator		it =	test.lower_bound(stack.top());
				std::cout << " [";
				for ( ;  it_off != test_off.end() && it != test.end() 
						; ++it_off, ++it)
					std::cout << " | " <<  it_off->first << " " << it->first;
				std::cout << "] " << std::endl;
			}
			stack.pop();
			std::cout << std::endl;
		}
	}

	std::cout << "//////////////////////////ERASE/////////////////////////////////" << std::endl;
	{
		srand(time(NULL));
		ft::map<int, std::string>			test;
		std::map<int, std::string>			test_off;
		// // RANDOM INSERT
		// ft::vector<int>					vec_keys;
		// for (int i = 1 ; i < 10 ; ++i) {
			// int	new_nb = rand() % 20 + 1;
			// vec_keys.push_back(new_nb);
			// std::cout << " #### insert " << new_nb << " : ";
			// test[new_nb] = "mdr";
			// test_off[new_nb] = "mdr";
			// print_content(test, false);
			// std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
		// }
		// std::random_shuffle(vec_keys.begin(), vec_keys.end());
		// ft::vector<int>::iterator	it = vec_keys.begin();

		// for (; it != vec_keys.end() ; ++it) {
			// std::cout << *it << " ";
		// }
		std::cout << std::endl;

		int	array[] = {8, 2, 10, 16, 5, 15, 17};
		int	nb_to_erase = 8;

		std::vector<int> vec_values(array, array + sizeof(array) / sizeof(array[0]));
		for (std::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
			test.insert(ft::make_pair(*it, "manger des chips"));
			print_content(test, false);
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
		}

		std::cout << "///////////////////////////////// ONE ELEMENT" << std::endl;
		std::cout << " ERASE ONE ELEMENT :" << nb_to_erase << std::endl;
		test.erase(test.find(nb_to_erase));
		std::cout << " IS VALID ? : " << test._is_valid() << std::endl;
		test.print_tree();
	}

}
