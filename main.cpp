#include <iostream>
#include <string>
#include <deque>
#if COMP == 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map/Map.hpp"
	#include "stack/Stack.hpp"
	#include "vector/Vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

template <class Ct>
void	print_content(Ct map, bool is_print) {
	typedef		typename Ct::iterator				iterator_type;
	if (is_print)
		for (iterator_type it = map.begin() ; it != map.end() ; ++it)
			std::cout << it->first << " " << it->second << std::endl;
}

template <class Ct>
void	print_reverse_content(Ct map, bool is_print) {
	typedef		typename Ct::reverse_iterator		reverse_iterator_type;
	if (is_print)
		for (reverse_iterator_type it = map.rbegin() ; it != map.rend() ; ++it)
			std::cout << it->first << " " << it->second << std::endl;
}


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	/////////////////////////////////////////// MY TESTS /////////////////////////////////////////////
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
		print_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 5: ";
		test.insert(value_type(5, "pipi"));
		print_reverse_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 1: ";
		test.insert(value_type(1, "crotte"));
		print_reverse_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 2: ";
		test.insert(value_type(2, "crotte"));
		print_reverse_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 7: ";
		test.insert(value_type(7, "zigouigoui"));
		print_reverse_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 9: ";
		test.insert(value_type(9, "popo"));
		print_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 4: ";
		test.insert(value_type(4, "popo"));
		print_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 7: ";
		test.insert(value_type(7, "popo"));
		print_content(test, true);
		std::cout << std::endl;
		std::cout << "#### Insert 6: ";
		test.insert(value_type(6, "popo"));
		print_content(test, true);
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
			print_content(test, true);
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
		}
		{
			std::cout << "//////////////////////////INSERT BEGINING" << std::endl;
			ft::map<int, std::string>			test2;
			for (iterator_vector it = vec_values.begin() ; it != vec_values.end() ; ++it) {
				test2.insert(value_type(*it, "lol"));
				print_content(test2, true);
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
			print_content(test, true);
#ifdef DEBUG
			std::cout << " IS VALID ? : " <<  test._is_valid() << std::endl;
#endif
		}
		std::cout << std::endl;

		std::cout << "//////////////////////////RANDOM INSERT RANGE [1 - 20]" << std::endl;
		ft::map<int, std::string>			test2;
		test2.insert(test.begin(), test.end());
		print_content(test2, true);
		std::cout << std::endl;
	}

	std::cout << "//////////////////////////LOOKUP////////////////////////////////" << std::endl;
	{
		std::cout << "//////////////////////////COUNT" << std::endl;
		ft::map<int, std::string>			test;
		ft::stack<int>						stack;
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
		ft::stack<int>						stack;
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
		ft::stack<int>							stack;
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
		ft::stack<int>							stack;
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
		ft::stack<int>							stack;
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
				print_content(test, true);
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
				// print_content(test, true);
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
				// print_content(test, true);
			}
			for (ft::map<int, std::string>::iterator it = test.begin() ;
					it != test.end() ; ++it)
				std::cout << it->first << " ";
#ifdef DEBUG
			std::cout << std::endl << " IS VALID ? : " <<  test._is_valid() << std::endl;
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

			std::cout << " ERASE SAFE NUMBER ";
			test.erase(nb_safe);
			std::cout << std::endl;
		}

			//////////////////STACK/////////////////////////////////////////
		{
			ft::stack<int>	stack;


			for (int i = 0 ; i < 20 ; ++i) {
				int	rand_numb = rand();
				stack.push(rand_numb);
			}

			while (!stack.empty()) {
				std::cout << "Content : ";
				std::cout << stack.top() << "  |  ";
				stack.pop();
			}
		}
	}

	return (0);
}
