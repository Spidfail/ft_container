/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:17:28 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/18 20:01:57 by guhernan         ###   ########.fr       */
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

template < typename T = int, class Allocator = std::allocator<T> >
class VectorTester : public ITester {

	public:
		typedef		typename std::vector< T, Allocator >				vector_original;
		typedef		typename ft::vector< T, Allocator >					vector_custom;
		typedef		typename ITester::Folder							type_folder;

////////////////////////////////////////////////////////////////////////////////////////////////
		VectorTester() : ITester() {
		}

		VectorTester(const VectorTester &source)
			: ITester(source) {
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

		~VectorTester() {
		}

		void		init_files() {
			if (_folder_std || _folder_ft)
				return ;
			_folder_std = new type_folder("vector", "std", "details_std");
			_folder_ft = new type_folder("vector", "ft", "details_ft");
			_folder_std->_init_folder();
			_folder_ft->_init_folder();
		}
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CONSTRUCTORS//////////////////////////////////
		//
		void		unitest_constructor_empty() {
		}
		void		unitest_constructor_range() {
		}
		void		unitest_constructor_copy() {
		}
		void		unitest_constructor_all() { }
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////ACCESSORS/////////////////////////////////////
		//
		int								get_test_nb() {
			return this->_test_nb;
		}

		std::ofstream					&get_folder_std(const std::string &key) {
		}

		std::ofstream					&get_folder_ft(const std::string &key) {
		}

		std::chrono::duration<int>		&get_exec_time(const std::string &key) {
			return this->_exec_time[key];
		}

		void							get_status() {
//             TO REFACTO
//
			// iterator_files itf = this->_files.begin();
			// iterator_files_names it = this->_files_names.begin();
			// iterator_exec_time itt = this->_exec_time.begin();
//
			// std::cout << " Available files :" << std::endl;
			// for (; it != this->_files_names.end() ; it++, itf++) {
				// std::cout << "	" << it->second;
				// std::cout << "	||	IS_OPEN   " << itf->second->is_open();
				// std::cout << "	||	EXEC_TIME   " << itt->second.count() << std::endl;
			// }
			// std::cout << " Number of tests passed : " << get_test_nb() << std::endl;
		}

		void				unitest_accessors_all() {
			std::ofstream	&os = this->_files["accessors"];

			unitest_size<vector_custom>(os);
			unitest_size<vector_original>(os);
		}

		template <class Ct>
		void				unitest_size(std::ofstream &os) {
			Ct		vec;
			vec.size();
		}
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CAPACITY//////////////////////////////////////
		//
		void				unitest_capacity_all() {
		}
		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MODIFIERS/////////////////////////////////////
		//
		void				unitest_modifiers_all() {
		}


};

#endif
