
#include <algorithm>
#include <iostream>
#include <ctime>
#include <random>
#include <stack>

#if COMP == 0
# include "Map.hpp"
# include "../vector/Vector.hpp"
#else
# include <map>
# include <vector>
namespace ft = std;
#endif


template <class Ct>
void	print_content(Ct map, bool is_print) {
	typedef		typename Ct::iterator				iterator_type;
#ifdef DEBUG
	map.print_tree();
#endif
	if (is_print)
		for (iterator_type it = map.begin() ; it != map.end() ; ++it)
			std::cout << it->first << " " << it->second << std::endl;
}

template <class Ct>
void	print_reverse_content(Ct map, bool is_print) {
	typedef		typename Ct::reverse_iterator		reverse_iterator_type;
#ifdef DEBUG
	map.print_tree();
#endif
	if (is_print)
		for (reverse_iterator_type it = map.rbegin() ; it != map.rend() ; ++it)
			std::cout << it->first << " " << it->second << std::endl;
}

int main() {
	std::cout << std::boolalpha;
	// srand(100000);

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
		typedef		ft::vector<int>::iterator				iterator_vector;

		ft::map<int, std::string>			test;
		int	array[] = {5, 11, 16, 1, 3, 7, 8, 10};

		ft::vector<int> vec_values(array, array + sizeof(array) / sizeof(array[0]));

		for (iterator_vector it = vec_values.begin() ; it != vec_values.end() ; ++it) {
			test.insert(test.begin(), value_type(*it, "lol"));
			print_content(test, false);
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
		}
		{
			std::cout << "//////////////////////////INSERT BEGINING" << std::endl;
			ft::map<int, std::string>			test2;
			for (iterator_vector it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test2.insert(value_type(*it, "lol"));
				print_content(test2, false);
#ifdef DEBUG
				std::cout << " IS VALID ? : " <<  test2._is_valid() << std::endl;
#endif
			}
		}
		std::cout << std::endl;

	}
	std::cout << "//////////////////////////RANDOM INSERT [1 - 20]" << std::endl;
	{
		ft::map<int, std::string>			test;
		for (int i = 1 ; i < 50 ; ++i) {
			int	new_nb = rand() % 20 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
			print_content(test, false);
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
		}
		std::cout << std::endl;

		std::cout << "//////////////////////////RANDOM INSERT RANGE [1 - 20]" << std::endl;
		ft::map<int, std::string>			test2;
		test2.insert(test.begin(), test.end());
		print_content(test2, false);
		std::cout << std::endl;
	}

	std::cout << "//////////////////////////LOOKUP////////////////////////////////" << std::endl;
	{
		std::cout << "//////////////////////////COUNT" << std::endl;
		ft::map<int, std::string>			test;
		std::stack<int>						stack;
		for (int i = 1 ; i < 20 ; ++i) {
			int	new_nb = rand() % 20 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			std::cout << " #### count on : " << stack.top() << " = ";
			std::cout << test.count(stack.top());
			stack.pop();
		}
		std::cout << std::endl;
	}

	{
		std::cout << "//////////////////////////FIND" << std::endl;
		ft::map<int, std::string>			test;
		std::stack<int>						stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			std::cout << "########## find on : " << stack.top() << std::endl;
			{
				std::cout << "iterators : " << std::endl;
				ft::map<int, std::string>::iterator		it =	test.find(stack.top());
				std::cout << " Reverse order [";
				for ( ; it != test.begin() ; --it)
					std::cout << " | " <<  " " << it->first;
				std::cout << "] " << std::endl;
				std::cout << " Ordered [";
				for ( ; it != test.end() ; ++it)
					std::cout << " | " <<  " " << it->first;
				std::cout << "]" << std::endl;
			} {
				std::cout << "const_iterators : " << std::endl;
				ft::map<int, std::string>::const_iterator		it =	test.find(stack.top());
				std::cout << " Reverse order [";
				for ( ; it != test.begin() ; --it)
					std::cout << " | " << " " << it->first;
				std::cout << "] " << std::endl;
				std::cout << " Ordered [";
				for ( ; it != test.end() ; ++it)
					std::cout << " | " << " " << it->first;
				std::cout << "]" << std::endl;
			}
			stack.pop();
			std::cout << std::endl << std::endl;
		}
	}

	{
		std::cout << "//////////////////////////EQUAL RANGE" << std::endl;
		typedef		ft::map<int, std::string>::iterator				iterator;
		typedef		ft::map<int, std::string>::const_iterator		const_iterator;
		ft::map<int, std::string>				test;
		std::stack<int>							stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			{
				std::cout << "########## equal range on : " << stack.top() << std::endl;
				std::cout << " iterators : ";
				ft::pair<iterator, iterator>			pair =	test.equal_range(stack.top());
				std::cout << " [";
				for ( ; pair.first != pair.second ;  ++pair.first)
					if (pair.second != test.end())
						std::cout << " | "  << pair.second->first;
					else
						std::cout << " | " << " END " ;
				std::cout << "] ";
			} {
				std::cout << " const_iterators : ";
				ft::pair<const_iterator, const_iterator>			pair =	test.equal_range(stack.top());
				std::cout << " [";
				for ( ; pair.first != pair.second ;  ++pair.first)
					if (pair.second != test.end())
						std::cout << " | "  << pair.second->first;
					else
						std::cout << " | " << " END " ;
				std::cout << "] ";
			}
			stack.pop();
			std::cout << std::endl;
		}
	}

	{
		std::cout << "//////////////////////////Upper Bound" << std::endl;
		typedef		ft::map<int, std::string>::iterator				iterator;
		typedef		ft::map<int, std::string>::const_iterator		const_iterator;
		ft::map<int, std::string>				test;
		std::stack<int>							stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			{
				std::cout << "########## Upper Bound : " << stack.top() << std::endl;
				std::cout << " iterators : ";
				iterator	it =	test.upper_bound(stack.top());
				std::cout << " [";
				for ( ; it != test.end() ; ++it)
					std::cout << " | " << it->first;
				std::cout << "] " << std::endl;
			} {
				std::cout << " const_iterators : ";
				const_iterator	it =	test.upper_bound(stack.top());
				std::cout << " [";
				for ( ; it != test.end() ; ++it)
					std::cout << " | " << it->first;
				std::cout << "] " << std::endl;
			}
			stack.pop();
			std::cout << std::endl;
		}
	}

	{
		std::cout << "//////////////////////////Lower Bound" << std::endl;
		typedef		ft::map<int, std::string>::iterator				iterator;
		typedef		ft::map<int, std::string>::const_iterator		const_iterator;
		ft::map<int, std::string>				test;
		std::stack<int>							stack;
		for (int i = 1 ; i < 10 ; ++i) {
			int	new_nb = rand() % 10 + 1;
			std::cout << " #### insert " << new_nb << " : ";
			test[new_nb] = "mdr";
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			stack.push(new_nb);
		}
		while (!stack.empty()) {
			{
				std::cout << "########## Upper Bound : " << stack.top() << std::endl;
				std::cout << " iterators : ";
				iterator	it =	test.lower_bound(stack.top());
				std::cout << " [";
				for ( ; it != test.end() ; ++it)
					std::cout << " | " << it->first;
				std::cout << "] " << std::endl;
			} {
				std::cout << " const_iterators : ";
				const_iterator	it =	test.lower_bound(stack.top());
				std::cout << " [";
				for ( ; it != test.end() ; ++it)
					std::cout << " | " << it->first;
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
			// RANDOM INSERT
			ft::vector<int>						vec_keys;
			for (int i = 1 ; i < 20 ; ++i) {
				int	new_nb = rand() % 20 + 1;
				vec_keys.push_back(new_nb);
				std::cout << " #### insert " << new_nb << " : ";
				test[new_nb] = "mdr";
#ifdef DEBUG
				std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			}

			for (ft::vector<int>::iterator it = vec_keys.begin() ; it != vec_keys.end() ; ++it) {
				std::cout << *it << " ";
			}

			// std::random_shuffle(vec_keys.begin(), vec_keys.end());

			std::cout << std::endl;
			for (ft::vector<int>::iterator it = vec_keys.begin() ;
					it != vec_keys.end() ; ++it) {
				std::cout << " ## Erase : " << *it << std::endl;
				test.erase(*it);
#ifdef DEBUG
				if (*it)
					test.print_tree();
				std::cout << " IS VALID ? " << test._is_valid() << std::endl << std::endl;
#endif
			}
			std::cout << std::endl;
		}

		{
			std::cout << "////////////////////////////////////////////////////////////" << std::endl;
			std::cout << "////////////// TEST WITH DEFINE TREE : SAFE ITERATOR" << std::endl << std::endl;
			ft::map<int, std::string>			test;

			// Create an vector from a static array.
			// The called constructor use 'array' pointers to instantiate template,
			// then copy the array's content.
			ft::vector<int> vec_values(array, array + sizeof(array) / sizeof(array[0]));
			int	nb_safe = 5;

			std::cout << "///////////// Tree building" << std::endl;
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test.insert(ft::make_pair(*it, "manger des chips"));
				print_content(test, false);
#ifdef DEBUG
				std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			}
			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;


			std::cout << std::endl << "//////////// TEST ERASE AND ITERATOR - no print" << std::endl << std::endl;

			std::cout << " ERASE RANGE, EXCEPT :" << nb_safe << std::endl;
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				if (*it != nb_safe) {
					test.erase(*it);
				}
#ifdef DEBUG
				std::cout << " ERASE " << *it << " -- IS VALID ? : " << test._is_valid() << std::endl;
#endif
			}
			// Print map to check it's final content
			std::cout << "Check map content : " << std::endl;
			std::cout << "  Custom = ";
			for (ft::map<int, std::string>::iterator	it = test.begin() ;
					it != test.end() ; ++it) {
				std::cout << it->first << " ";
			}
			std::cout << std::endl;
		}

		{
			// Same test 
			std::cout << std::endl << "//////////// TEST ERASE AND ITERATOR - Print" << std::endl;
			std::cout << std::endl;
			ft::map<int, std::string>			test;

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
			}
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			std::cout << std::endl;

			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;

			// std::random_shuffle(vec_values.begin(), vec_values.end());
			std::cout << "   SHUFFLED RANGE : ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.end() ; ++it_map)
				std::cout << it_map->first << " ";
			std::cout << " | ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.begin() ; --it_map)
				std::cout << it_map->first << " ";
			std::cout << std::endl << std::endl;

			std::cout << " ERASE RANGE, EXCEPT :" << nb_safe << std::endl;

			// TEST
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				if (*it != nb_safe) {
					std::cout << "----Erase : " << *it << std::endl;
					test.erase(*it);
				}
#ifdef DEBUG
				std::cout << "   IS VALID ? : " << test._is_valid() << std::endl;
#endif
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
			std::cout << std::endl;
		}

		{
			// Same test 
			std::cout << std::endl << "//////////// TEST ERASE AND ITERATOR - Random & Print" << std::endl;
			std::cout << std::endl;
			ft::map<int, std::string>			test;

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
				// print_content(test, false);
			}
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
			std::cout << std::endl;

			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;

			// std::random_shuffle(vec_values.begin(), vec_values.end());
			std::cout << "   SHUFFLED RANGE : ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.end() ; ++it_map)
				std::cout << it_map->first << " ";
			std::cout << " | ";
			for (ft::map<int, std::string>::iterator it_map = safe_it ;
					it_map != test.begin() ; --it_map)
				std::cout << it_map->first << " ";
			std::cout << std::endl << std::endl;

			std::cout << " ERASE RANGE, EXCEPT :" << nb_safe << std::endl;

			// TEST
			for (ft::vector<int>::iterator it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				if (*it != nb_safe) {
					std::cout << "----Erase : " << *it << std::endl;
					test.erase(*it);
				}
#ifdef DEBUG
				std::cout << "   IS VALID ? : " << test._is_valid() << std::endl;
#endif
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
#ifdef DEBUG
				test.print_tree();
#endif
			}
			std::cout << " ERASE SAFE NUMBER : ";
			test.erase(nb_safe);
			std::cout << std::endl;
		}
		{
			// Same test 
			std::cout << std::endl << "//////////// TEST ERASE RANGE AND ITERATOR - Random Range !" << std::endl;
			std::cout << std::endl;
			ft::map<int, std::string>			test;

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
				// print_content(test, false);
			}
			for (ft::map<int, std::string>::iterator it = test.begin() ;
					it != test.end() ; ++it)
				std::cout << it->first << " ";
#ifdef DEBUG
			std::cout << std::endl << " IS VALID ? : " <<  test._is_valid() << std::endl;
			test.print_tree();
#endif
			std::cout << std::endl;

			// Create safe iterator, shouldn't desappear
			ft::map<int, std::string>::iterator		safe_it = test.begin();
			while (safe_it->first != nb_safe)
				++safe_it;


			std::cout << " ERASE RANGE, EXCEPT :" << nb_safe << std::endl;

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
#ifdef DEBUG
			test.print_tree();
#endif
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
#ifdef DEBUG
			test.print_tree();
#endif

			std::cout << " ERASE SAFE NUMBER ";
			test.erase(nb_safe);
			std::cout << std::endl;
		}

	}

}
