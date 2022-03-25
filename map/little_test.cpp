
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
	srand(time(NULL));

	std::cout << "//////////////////////////INSERT////////////////////////////////" << std::endl;
	typedef		ft::map<int, std::string>::value_type			value_type;
	{
		ft::map<int, std::string>			test;
		test.insert(value_type(3, "caca"));
		std::cout << "#### First state : ";
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
		std::cout << "//////////////////////////CRASHING INSERT ?" << std::endl;
		typedef		std::vector<int>::iterator				iterator_vector;

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
	std::cout << "//////////////////////////RANDOM INSERT [1 - 20]" << std::endl;
	{
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

		std::cout << "//////////////////////////RANDOM INSERT RANGE [1 - 20]" << std::endl;
		ft::map<int, std::string>			test2;
		std::map<int, std::string>				test_off2;
		test_off2.insert(test_off.begin(), test_off.end());
		test2.insert(test.begin(), test.end());
		print_content(test2, false);
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
		int	array[] = {8, 2, 10, 16, 5, 15, 17, 1, 6, 9};
		{
			std::cout << "////////////// TEST WITH DEFINE TREE : SHUFFLED RANGE" << std::endl;
			ft::map<int, std::string>			test;
			std::map<int, std::string>			test_off;
			// RANDOM INSERT
			ft::vector<int>						vec_keys;
			for (int i = 1 ; i < 20 ; ++i) {
				int	new_nb = rand() % 20 + 1;
				vec_keys.push_back(new_nb);
				std::cout << " #### insert " << new_nb << " : ";
				test[new_nb] = "mdr";
				test_off[new_nb] = "mdr";
				std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			}

			for (ft::vector<int>::iterator it = vec_keys.begin() ; it != vec_keys.end() ; ++it) {
				std::cout << *it << " ";
			}

			std::random_shuffle(vec_keys.begin(), vec_keys.end());
			// ft::vector<int>::iterator	it = vec_keys.begin();

			std::cout << std::endl;
			for (ft::vector<int>::iterator it = vec_keys.begin() ;
					it != vec_keys.end() ; ++it) {
				std::cout << " ## Erase : " << *it << std::endl;
				test.erase(*it);
				if (*it)
					test.print_tree();
				std::cout << " IS VALID ? " << test._is_valid() << std::endl << std::endl;
			}
			std::cout << std::endl;
		}

		{
			std::cout << "////////////////////////////////////////////////////////////" << std::endl;
			std::cout << "////////////// TEST WITH DEFINE TREE : SAFE ITERATOR" << std::endl << std::endl;
			ft::map<int, std::string>			test;
			std::map<int, std::string>			test_off;

			// Create an vector from a static array.
			// The called constructor use 'array' pointers to instantiate template,
			// then copy the array's content.
			ft::vector<int> vec_values(array, array + sizeof(array) / sizeof(array[0]));
			int	nb_safe = 5;

			std::cout << "///////////// Tree building" << std::endl;
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test.insert(ft::make_pair(*it, "manger des chips"));
				test_off.insert(std::make_pair(*it, "bidule"));
				print_content(test, false);
				std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			}
			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;


			std::cout << std::endl << "//////////// TEST ERASE AND ITERATOR - no print" << std::endl << std::endl;

			std::cout << " ERASE RANGE, EXCEPT :" << nb_safe << ", with address = " << &(*safe_it) << std::endl;
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				if (*it != nb_safe) {
					test.erase(*it);
					test_off.erase(*it);
				}
				std::cout << " ERASE " << *it << " -- IS VALID ? : " << test._is_valid() << std::endl;
			}
			// Print map to check it's final content
			std::cout << "Check map content : " << std::endl;
			std::cout << "  Custom = ";
			for (ft::map<int, std::string>::iterator	it = test.begin() ;
					it != test.end() ; ++it) {
				std::cout << it->first << " ";
			}
			std::cout << "  Official = ";
			for (std::map<int, std::string>::iterator	it = test_off.begin() ;
					it != test_off.end() ; ++it) {
				std::cout << it->first << " ";
			}
			std::cout << std::endl;
		}

		{
			// Same test 
			std::cout << std::endl << "//////////// TEST ERASE AND ITERATOR - Print" << std::endl;
			std::cout << std::endl;
			ft::map<int, std::string>			test;
			std::map<int, std::string>			test_off;

			// Create an vector from a static array.
			// The called constructor use 'array' pointers to instantiate template,
			// then copy the array's content.
			ft::vector<int> vec_values(array, array + sizeof(array) / sizeof(array[0]));
			// Safe number within the range, randomly selected.
			int	nb_safe = array[rand() % 10];

			std::cout << " RANGE = ";
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;

			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test.insert(ft::make_pair(*it, "manger des chips"));
				test_off.insert(std::make_pair(*it, "bidule"));
				// print_content(test, false);
			}
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			std::cout << std::endl;

			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;

			std::random_shuffle(vec_values.begin(), vec_values.end());
			std::cout << "   SHUFFLED RANGE : ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.end() ; ++it_map)
				std::cout << it_map->first << " ";
			std::cout << " | ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.begin() ; --it_map)
				std::cout << it_map->first << " ";
			std::cout << std::endl << std::endl;

			std::cout << " ERASE RANGE, EXCEPT :" << nb_safe << ", with address = " << &(*safe_it) << std::endl;

			// TEST
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				if (*it != nb_safe) {
					std::cout << "----Erase : " << *it << std::endl;
					test.erase(*it);
					test_off.erase(*it);
				}
				std::cout << "   IS VALID ? : " << test._is_valid() << std::endl;
				// Check by printing content
				std::cout << "   Print value : ";
				for (ft::map<int, std::string>::iterator it_map = safe_it ;
						it_map != test.end() ; ++it_map)
					std::cout << it_map->first << " ";
				std::cout << " | ";
				for (ft::map<int, std::string>::iterator it_map = safe_it ;
						it_map != test.begin() ; --it_map)
					std::cout << it_map->first << " ";
				std::cout << std::endl;
			}
			std::cout << std::endl;

			// Print map to check it's final content
			std::cout << "Check map content : " << std::endl;
			std::cout << "  Custom = ";
			for (ft::map<int, std::string>::iterator	it = test.begin() ;
					it != test.end() ; ++it) {
				std::cout << it->first << " ";
			}
			std::cout << "  Official = ";
			for (std::map<int, std::string>::iterator	it = test_off.begin() ;
					it != test_off.end() ; ++it) {
				std::cout << it->first << " ";
			}
			std::cout << std::endl;
		}

		{
			// Same test 
			std::cout << std::endl << "//////////// TEST ERASE AND ITERATOR - Random & Print" << std::endl;
			std::cout << std::endl;
			ft::map<int, std::string>			test;
			std::map<int, std::string>			test_off;

			ft::vector<int>						vec_values;
			std::cout << " RANGE [1-20] = ";
			for (int i = 1 ; i < 30 ; ++i) {
				int	new_nb = rand() % 20 + 1;
				vec_values.push_back(new_nb);
				std::cout << new_nb << " ";
			}
			int	nb_safe = vec_values[rand() % 29];
			std::cout << std::endl;

			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test.insert(ft::make_pair(*it, "manger des chips"));
				test_off.insert(std::make_pair(*it, "bidule"));
				// print_content(test, false);
			}
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
			std::cout << std::endl;

			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;

			std::random_shuffle(vec_values.begin(), vec_values.end());
			std::cout << "   SHUFFLED RANGE : ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.end() ; ++it_map)
				std::cout << it_map->first << " ";
			std::cout << " | ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.begin() ; --it_map)
				std::cout << it_map->first << " ";
			std::cout << std::endl << std::endl;

			std::cout << " ERASE, EXCEPT :" << nb_safe << ", with address = " << &(*safe_it) << std::endl;

			// TEST
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				if (*it != nb_safe) {
					std::cout << "----Erase : " << *it << std::endl;
					test.erase(*it);
					test_off.erase(*it);
				}
				std::cout << "   IS VALID ? : " << test._is_valid() << std::endl;
				// Check by printing content
				std::cout << "   Print value : ";
				for (ft::map<int, std::string>::iterator it_map = safe_it ;
						it_map != test.end() ; ++it_map)
					std::cout << it_map->first << " ";
				std::cout << " | ";
				std::cout.flush();
				for (ft::map<int, std::string>::iterator it_map = safe_it ;
						it_map != test.begin() ; --it_map)
					std::cout << it_map->first << " ";
				std::cout << std::endl;
				test.print_tree();
			}
			std::cout << " ERASE SAFE NUMBER : ";
			test.erase(nb_safe);
			test_off.erase(nb_safe);
			std::cout << std::endl;
		}
		{
			// Same test 
			std::cout << std::endl << "//////////// TEST ERASE RANGE AND ITERATOR - Random Range !" << std::endl;
			std::cout << std::endl;
			ft::map<int, std::string>			test;
			std::map<int, std::string>			test_off;

			ft::vector<int>						vec_values;
			std::cout << " RANGE [1-20] = ";
			for (int i = 1 ; i < 30 ; ++i) {
				int	new_nb = rand() % 20 + 1;
				vec_values.push_back(new_nb);
				std::cout << new_nb << " ";
			}
			int	nb_safe = vec_values[rand() % 29];
			std::cout << std::endl;

			// Insert range, print content, check if the tree is balanced, print tree.
			std::cout << "   RANGE INSERTED : ";
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test.insert(ft::make_pair(*it, "manger des chips"));
				test_off.insert(std::make_pair(*it, "bidule"));
				// print_content(test, false);
			}
			for (ft::map<int, std::string>::iterator it = test.begin() ;
					it != test.end() ; ++it)
				std::cout << it->first << " ";
			std::cout << std::endl << " IS VALID ? : " <<  test._is_valid() << std::endl;
			test.print_tree();
			std::cout << std::endl;

			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;


			std::cout << " ERASE, EXCEPT :" << nb_safe << ", with address = " << &(*safe_it) << std::endl;

			std::cout << "-----Range to erase : ";
			for (ft::map<int, std::string>::iterator it = test.begin() ; it != safe_it ; ++it)
				std::cout << it->first << " ";
			std::cout << std::endl;

			std::cout << "-----Erase the range !" << std::endl;
			test.erase(test.begin(), safe_it);

			std::cout << "   Print value : ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.end() ; ++it_map)
				std::cout << it_map->first << " ";
			std::cout << " | ";
			std::cout.flush();
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.begin() ; --it_map)
				std::cout << it_map->first << " ";
			std::cout << std::endl;
			test.print_tree();
			std::cout << std::endl;

			std::cout << "-----Range to erase : ";
			{
				ft::map<int, std::string>::iterator it = safe_it;
				++it;
				for ( ; it != test.end() ; ++it)
					std::cout << it->first << " ";
				std::cout << std::endl;
			}

			std::cout << "-----Erase the range !" << std::endl;
			test.erase(++(ft::map<int, std::string>::iterator(safe_it)), test.end());

			// Finale print
			std::cout << "   Print value : ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.end() ; ++it_map)
				std::cout << it_map->first << " ";
			std::cout << " | ";
			std::cout.flush();
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.begin() ; --it_map)
				std::cout << it_map->first << " ";
			std::cout << std::endl;
			test.print_tree();

			std::cout << " ERASE SAFE NUMBER ";
			test.erase(nb_safe);
			test_off.erase(nb_safe);
			std::cout << std::endl;
		}

	}

}
