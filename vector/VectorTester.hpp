/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorTester.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:17:28 by guhernan          #+#    #+#             */
/*   Updated: 2022/02/08 13:08:23 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

#include "ITester.hpp"

#include <iostream>
#include <filesystem>

#include <algorithm>
#include <vector>

#include <cstdlib>
#include <time.h>

#include "ft_random.hpp"
#include "Vector.hpp"

#include "VectorConstructorTests.hpp"
#include "VectorCapacityTests.hpp"
#include "VectorAccessorsTests.hpp"
#include "VectorModifiersTests.hpp"
#include "VectorIteratorsTests.hpp"

template < typename T = int, class Allocator = std::allocator<T> >
class VectorTester : public ft::ITester {

	public:
		typedef		typename std::vector< T, Allocator >		vector_original;
		typedef		typename ft::vector< T, Allocator >			vector_custom;
		typedef		typename ft::ITester::Folder				type_folder;
		typedef		T											type_value;

		typedef		ft::UnitestConstructor<vector_custom, std::ofstream, type_value>	constructor_custom;
		typedef		ft::UnitestConstructor<vector_original, std::ofstream, type_value>	constructor_original;
		typedef		ft::UnitestCapacity<vector_custom, std::ofstream, type_value>		capacity_custom;
		typedef		ft::UnitestCapacity<vector_original, std::ofstream, type_value>		capacity_original;
		typedef		ft::UnitestAccessors<vector_custom, std::ofstream, type_value>		accessors_custom;
		typedef		ft::UnitestAccessors<vector_original, std::ofstream, type_value>	accessors_original;
		typedef		ft::UnitestModifiers<vector_custom, std::ofstream, type_value>		modifiers_custom;
		typedef		ft::UnitestModifiers<vector_original, std::ofstream, type_value>	modifiers_original;
		typedef		ft::UnitestIterators<vector_custom, std::ofstream, type_value>		iterators_custom;
		typedef		ft::UnitestIterators<vector_original, std::ofstream, type_value>	iterators_original;

	protected:
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

	public:
		VectorTester()
			: ft::ITester() { std::cout << std::boolalpha; }

		VectorTester(const VectorTester &source)
			: ft::ITester(source) { *this = source; }

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
		//////////////////////////////////////INITIALISATION////////////////////////////////
		//
		void		init() {
			_init_files();
			_init_exec_time();
		}
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////GETTERS///////////////////////////////////////
		//
		int									get_test_nb() { return this->_test_nb; }

		type_folder							&get_folder_std() { return *this->_folder_std; }
		type_folder							&get_folder_ft() { return *this->_folder_ft; }

		type_exec_time						&get_exec_time() { return this->_exec_time; }
		type_duration						&get_exec_time(const std::string &key) { return this->_exec_time[key]; }

		void								get_status() {
			{
				ft::ITester::iterator_files_names	it = get_folder_std().begin_files_names();
				ft::ITester::iterator_files			it2 = get_folder_std().begin_files();
				ft::ITester::iterator_exec_time		it3 = get_exec_time().begin();

				while (it != get_folder_std().end_files_names() && it2 != get_folder_std().end_files()
						&& it3 != get_exec_time().end()) {
					std::cout << "	" << it->second;
					std::cout << "	||	IS_OPEN   " << it2->second->is_open();
					std::cout << "	||	EXEC_TIME   " << it3->second.count() << std::endl;
					++it;
				}
				std::cout << " Number of tests passed : " << _test_nb << std::endl;
			} {
				ft::ITester::iterator_files_names	it = get_folder_ft().begin_files_names();
				ft::ITester::iterator_files			it2 = get_folder_ft().begin_files();
				ft::ITester::iterator_exec_time		it3 = get_exec_time().begin();

				while (it != get_folder_ft().end_files_names() && it2 != get_folder_ft().end_files()
						&& it3 != get_exec_time().end()) {
					std::cout << "	" << it->second;
					std::cout << "	||	IS_OPEN   " << it2->second->is_open();
					std::cout << "	||	EXEC_TIME   " << it3->second.count() << std::endl;
					++it;
				}
				std::cout << " Number of tests passed : " << _test_nb << std::endl;
			}
		}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////TESTS///////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CONSTRUCTORS//////////////////////////////////
		//
		void		launch_constructor() {

			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_file		os_std = this->get_folder_std().get_file("constructor");
			type_file		os_ft = this->get_folder_ft().get_file("constructor");

			constructor_original::vector_fill(*os_std, random_value);
			constructor_custom::vector_fill(*os_ft, random_value);
			constructor_original::vector_range(*os_std, random_value);
			constructor_custom::vector_range(*os_ft, random_value);
			constructor_original::operator_equal(*os_std, random_value);
			constructor_custom::operator_equal(*os_ft, random_value);
		}

		
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CAPACITY//////////////////////////////////////
		//
		void				launch_capacity() {


			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_file		os_std = this->get_folder_std().get_file("capacity");
			type_file		os_ft = this->get_folder_ft().get_file("capacity");

			capacity_original::max_size(*os_std);
			capacity_custom::max_size(*os_ft);
			capacity_original::size(*os_std, random_value);
			capacity_custom::size(*os_ft, random_value);
			capacity_original::empty(*os_std, random_value);
			capacity_custom::empty(*os_ft, random_value);
			capacity_original::capacity(*os_std, random_value);
			capacity_custom::capacity(*os_ft, random_value);
			capacity_original::reserve(*os_std, random_value);
			capacity_custom::reserve(*os_ft, random_value);
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ACCESSORS/////////////////////////////////////
		//
		void				launch_accessors() {

			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());

			type_file		os_std = get_folder_std().get_file("accessors");
			type_file		os_ft = get_folder_ft().get_file("accessors");

			accessors_original::operator_bracket(*os_std, random_value);
			accessors_custom::operator_bracket(*os_ft, random_value);
			accessors_original::at(*os_std, random_value);
			accessors_custom::at(*os_ft, random_value);
			accessors_original::front(*os_std, random_value);
			accessors_custom::front(*os_ft, random_value);
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MODIFIERS/////////////////////////////////////
		//
		void				launch_modifiers() {
			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_value		replacement = random.generate(type_value()) / 2;

			type_file		os_std = get_folder_std().get_file("modifiers");
			type_file		os_ft = get_folder_ft().get_file("modifiers");
			modifiers_original::assign(*os_std, random_value, replacement);
			modifiers_custom::assign(*os_ft, random_value, replacement);
			modifiers_original::clear(*os_std, random_value, replacement);
			modifiers_custom::clear(*os_ft, random_value, replacement);
			modifiers_original::insert(*os_std, random_value, replacement);
			modifiers_custom::insert(*os_ft, random_value, replacement);
			modifiers_original::push_back(*os_std, random_value, replacement);
			modifiers_custom::push_back(*os_ft, random_value, replacement);
			modifiers_original::pop_back(*os_std, random_value, replacement);
			modifiers_custom::pop_back(*os_ft, random_value, replacement);
			modifiers_original::swap(*os_std, random_value, replacement);
			modifiers_custom::swap(*os_ft, random_value, replacement);
			modifiers_original::erase(*os_std, random_value, replacement);
			modifiers_custom::erase(*os_ft, random_value, replacement);
			modifiers_original::resize(*os_std, random_value, replacement);
			modifiers_custom::resize(*os_ft, random_value, replacement);
		}

		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ITERATORS/////////////////////////////////////
		//
		void				launch_iterators() {
			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_value		replacement = random.generate(type_value()) / 2;

			type_file		os_std = get_folder_std().get_file("iterators");
			type_file		os_ft = get_folder_ft().get_file("iterators");

			iterators_original::constructors(*os_std, random_value, replacement);
			iterators_custom::constructors(*os_ft, random_value, replacement);
			iterators_original::accessors(*os_std, random_value, replacement);
			iterators_custom::accessors(*os_ft, random_value, replacement);
			iterators_original::increment_decrement(*os_std, random_value, replacement);
			iterators_custom::increment_decrement(*os_ft, random_value, replacement);
			iterators_original::comparison(*os_std, random_value, replacement);
			iterators_custom::comparison(*os_ft, random_value, replacement);
			iterators_original::arithmetic(*os_std, random_value, replacement);
			iterators_custom::arithmetic(*os_ft, random_value, replacement);
			iterators_original::assignation(*os_std, random_value, replacement);
			iterators_custom::assignation(*os_ft, random_value, replacement);
			iterators_original::methods(*os_std, random_value, replacement);
			iterators_custom::methods(*os_ft, random_value, replacement);
		}
};
////////////////////////////////////////////////////////////////////////////////////////////
//

#endif
