/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:17:28 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/20 19:53:06 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

#include "ITester.hpp"

#include <iostream>
#include <filesystem>

#include <algorithm>
#include <vector>
#include "ft_vector.hpp"

#include <cstdlib>
#include <time.h>

template < typename T = int, class Allocator = std::allocator<T> >
class VectorTester : public ft::ITester {


	public:
		typedef		typename std::vector< T, Allocator >		vector_original;
		typedef		typename ft::vector< T, Allocator >			vector_custom;
		typedef		typename ft::ITester::Folder				type_folder;
		typedef		T											type_value;

	protected:
			type_value		_rand_collection;

		void		_init_files(std::string container_name = "vector", std::string dir_path = "./gunner_results/") {
			this->_folder_std = new type_folder(container_name, "std", dir_path + "details_std/");
			this->_folder_ft = new type_folder(container_name, "ft", dir_path + "details_ft/");
			this->_folder_std->_init_folder();
			this->_folder_ft->_init_folder();
		}

		void		_init_exec_time() {
			for (ft::ITester::iterator_files_names	it = _folder_ft->begin_files_names() ;
					it != _folder_ft->end_files_names(); it++) {
				std::pair< std::string, type_duration >		pair_exec_time(it->first, type_duration());
				this->_exec_time.insert(pair_exec_time);
			}
		}

		void				_init_collection_random(type_value);

	public:
		/////////////////////////////////////////////////////////////////////////////////////
		VectorTester() : ft::ITester() {
			std::cout << std::boolalpha;
		}

		VectorTester(const VectorTester &source)
			: ft::ITester(source) {
		}

		VectorTester		&operator=(const VectorTester &source) {
			this->_test_nb = source._test_nb;
			this->_files_org = source._files_org;
			this->_files_cust = source._files_cust;
			this->_files_names_org = source._files_names_org;
			this->_files_names_cust = source._files_names_cust;
			this->_exec_time = source._exec_time;
			this->_turn_in_directory = source._turn_in_directory;
			return *this;
		}

		virtual ~VectorTester() {
			delete this->_folder_std;
			delete this->_folder_ft;
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////UTILS/////////////////////////////////////////
		//
		type_value		random_generator( type_value, unsigned short int len = 0);
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////INITIALISATION////////////////////////////////
		//
		void		init() {
			_init_files();
			_init_exec_time();
		}
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////GETTERS///////////////////////////////////////
		//
		int									get_test_nb() {
			return this->_test_nb;
		}

		type_folder							&get_folder_std() {
			return *this->_folder_std;
		}

		type_folder							&get_folder_ft() {
			return *this->_folder_ft;
		}

		type_exec_time		&get_exec_time() {
			return this->_exec_time;
		}

		type_duration		&get_exec_time(const std::string &key) {
			return this->_exec_time[key];
		}

		void								get_status() {
			ft::ITester::iterator_files_names	it = get_folder_std().begin_files_names();
			ft::ITester::iterator_files			it2 = get_folder_std().begin_files();
			ft::ITester::iterator_exec_time		it3 = get_exec_time().begin();

			while (it != get_folder_std().end_files_names() && it2 != get_folder_std().end_files()
					&& it3 != get_exec_time().end()) {
				std::cout << "	" << it->second;
				std::cout << "	||	IS_OPEN   " << it2->second->is_open();
				std::cout << "	||	EXEC_TIME   " << it3->second.count() << std::endl;
				it++;
			}
			std::cout << " Number of tests passed : " << _test_nb << std::endl;
		}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////TESTS///////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CONSTRUCTORS//////////////////////////////////
		//
		void		unitest_constructor_empty() { }

		void		unitest_constructor_range() { }

		void		unitest_constructor_copy() { }

		void		unitest_constructor_all() { }
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CAPACITY//////////////////////////////////////
		//
		void				unitest_capacity_all() {
			type_file		os_std = get_folder_std().get_file("capacity");
			type_file		os_ft = get_folder_ft().get_file("capacity");

			unitest_max_size<vector_custom>(*os_std);
			unitest_max_size<vector_original>(*os_ft);
			unitest_size<vector_custom>(*os_std);
			unitest_size<vector_original>(*os_ft);
			unitest_capacity<vector_custom>(*os_std);
			unitest_capacity<vector_original>(*os_ft);
			unitest_reserve<vector_custom>(*os_std);
			unitest_reserve<vector_original>(*os_ft);
		}

		template <class Ct>
		void				unitest_max_size(std::ofstream &os) {
			Ct	vec;
			os << vec.max_size() << " ";
			os << std::endl;
		}

		template <class Ct>
		void				unitest_size(std::ofstream &os) {
			{
				Ct	vec;
				os << vec.size() << " ";
			}
			{
				Ct	vecfill(20, random_generator(type_value()));
				os << vecfill.size() << " ";
			}
			os << std::endl;
		}

		template <class Ct>
		void				unitest_capacity(std::ofstream &os) {
			{
				Ct	vec;
				os << vec.capacity() << " ";
			}
			{
				Ct	vecfill(20, random_generator(type_value()));
				os << vecfill.capacity() << " ";
			}
			// {
				// Ct	vec;
				// for (int i = 0 ; i < 100 ; i++) {
					// vec.push_back(random_generator(type_value()));
					// os << vec.capacity() << std::endl;
				// }
				// while (vec.empty()) {
					// vec.pop_back(random_generator(type_value()));
					// os << vec.capacity() << std::endl;
				// }
			// }
			// {
				// Ct	vec;
				// for (int i = 0 ; i < 100 ; i++) {
					// vec.push_back(random_generator(type_value()));
					// os << vec.capacity() << std::endl;
					// vec.pop_back(random_generator(type_value()));
					// os << vec.capacity() << std::endl;
				// }
			// }
			os << std::endl;
		}

		template <class Ct>
		void				unitest_reserve(std::ofstream &os) {
			{
				Ct	vec;
				vec.reserve(100);
				os << vec.capacity() << " " ;
			}
			{
				Ct	vecfill(20, random_generator(type_value()));
				vecfill.reserve(100);
				os << vecfill.capacity() << " " ;
			}
			{
				Ct	vecfill(200, random_generator(type_value()));
				vecfill.reserve(100);
				os << vecfill.capacity() << " " ;
			}
			{
				Ct	vecfill(20, random_generator(type_value()));
				vecfill.reserve(vecfill.max_size() + 1);
				os << vecfill.capacity() << " " ;
			}
			os << std::endl;
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ACCESSORS/////////////////////////////////////
		//
		void				unitest_accessors_all() {
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MODIFIERS/////////////////////////////////////
		//
		void				unitest_modifiers_all() {
		}


};

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FUNCTION TEMPLATE SPECIALISATION/////////////////////////
//
/////////////////////////////////////////////RANDOMISATION//////////////////////////////////
//
template <> void			VectorTester<std::string>::_init_collection_random(std::string) {
	_rand_collection.reserve(127 - 33);
	std::string::iterator	it = _rand_collection.begin();

	for (int c = 33 ; it != _rand_collection.end() && c < 127 ; it++, c++) {
		*it = c;
	}
}

template <> void			VectorTester<int>::_init_collection_random(int) {
	_rand_collection = 100000;
}

template <> std::string		VectorTester<std::string>::random_generator(std::string, unsigned short int len) {
			std::string		tmp;
			tmp.reserve(len);

			for (int i = 0; i < len; ++i) {
				tmp += this->_rand_collection[std::rand() % (sizeof(_rand_collection) - 1)];
			}
			return tmp;
		}

template <> int				VectorTester<int>::random_generator(int, unsigned short int len) {
	(void)len;
	std::srand(time(NULL));

	return rand() % _rand_collection + 1;
}
////////////////////////////////////////////////////////////////////////////////////////////
//

#endif
