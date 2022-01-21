/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:17:28 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/21 22:17:19 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

#include "ITester.hpp"

#include <iostream>
#include <filesystem>

#include <algorithm>
#include <vector>

#include "ft_random.hpp"
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
		void		launch_constructor() { }

		//
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////MEMBERS///////////////////////////////////////
		//

		
		////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////CAPACITY//////////////////////////////////////
		//
		template <class Ct, typename Os>
		struct UnitestCapacity {

			typedef typename Ct::size_type	size_type;

				static void				empty(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.empty() << " ";
					}
					{
						Ct	vecfill(20, random_value);
						os << vecfill.empty() << " ";
						//
						//// To implement with iterators
						//
						// vecfill.erase(vecfill.begin() + 5);
						// os << vecfill.empty() << " ";
						// vecfill.erase(vecfill.begin() + 5, vecfill.begin() + 9);
						// os << vecfill.empty() << " ";
						// vecfill.erase(vecfill.begin(), vecfill.end() + 9);
						// os << vecfill.empty() << " ";
					}
				}

				static void				size(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.size() << " ";
					}
					{
						Ct	vecfill(20, random_value);
						os << vecfill.size() << " ";
					}
					os << std::endl;
				}

				static void				reserve(Os &os, type_value random_value) {
					{
						Ct	vec;
						vec.reserve(100);
						os << vec.capacity() << " " ;
					}
					{
						Ct	vecfill(20, random_value);
						vecfill.reserve(100);
						os << vecfill.capacity() << " " ;
					}
					{
						Ct	vecfill(200, random_value);
						vecfill.reserve(100);
						os << vecfill.capacity() << " " ;
					}
					try {
						Ct	vecfill(20, random_value);
						vecfill.reserve(vecfill.max_size() + 1);
						os << vecfill.capacity() << " WRONG : AN EXCEPTION MUST BE THROWN " ;
					}
					catch (std::exception &e) {
						os << e.what() << " ";
					}
					os << std::endl;
				}

				static void				max_size(Os &os) {
					Ct	vec;
					os << vec.max_size() << " ";
					os << std::endl;
				}

				static void				capacity(Os &os, type_value random_value) {
					{
						Ct	vec;
						os << vec.capacity() << " ";
					}
					{
						Ct	vecfill(20, random_value);
						os << vecfill.capacity() << " ";
					}
					//
					//// To implement with iterators
					//
					// {
					// Ct	vec;
					// for (int i = 0 ; i < 100 ; i++) {
					// vec.push_back(this->random_value);
					// os << vec.capacity() << std::endl;
					// }
					// while (vec.empty()) {
					// vec.pop_back(this->random_value);
					// os << vec.capacity() << std::endl;
					// }
					// }
					// {
					// Ct	vec;
					// for (int i = 0 ; i < 100 ; i++) {
					// vec.push_back(this->random_value);
					// os << vec.capacity() << std::endl;
					// vec.pop_back(this->random_value);
					// os << vec.capacity() << std::endl;
					// }
					// }
					os << std::endl;
				}
		};


		void				launch_capacity() {

			typedef		UnitestCapacity<vector_custom, std::ofstream>		capacity_custom;
			typedef		UnitestCapacity<vector_original, std::ofstream>		capacity_original;

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
		template <class Ct, typename Os>


			struct UnitestAccessors {

			typedef typename Ct::size_type	size_type;

				static void				operator_bracket(Os &os, type_value random_value) {
					for (int j = 0 ; j < 100 ; j++) {
						Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill[i] << " ";}
					}
					for (int j = 0 ; j < 10 ; j++) {
						const Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill[i] << " ";}
					}
					os << std::endl;
				}

				static void				at(Os &os, type_value random_value) {
					for (int j = 0 ; j < 100 ; j++) {
						Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill.at(i) << " ";}
					}
					for (int j = 0 ; j < 10 ; j++) {
						const Ct	vecfill(j, random_value);
						for (int i = 0 ; i < j ; i++) {os << vecfill.at(i) << " ";}
					}
					os << std::endl;
				}

				static void				front(Os &os, type_value random_value) {
					{
						Ct	vecfill(100, random_value); os << vecfill.front() << " "; 
					} {
						Ct	const vecfill(100, random_value);
						os << vecfill.front() << " ";
					}
					os << std::endl;
				}

				static void				back(Os &os, type_value random_value) {
					{
						Ct	vecfill(100, random_value); os << vecfill.back() << " "; 
					} {
						Ct	const vecfill(100, random_value);
						os << vecfill.back() << " ";
					}
					os << std::endl;
				}
			};

		void				launch_accessors() {

			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			typedef		UnitestAccessors<vector_custom, std::ofstream>		accessors_custom;
			typedef		UnitestAccessors<vector_original, std::ofstream>		accessors_original;

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

		template <class Ct, typename Os>
		struct UnitestModifiers {

			typedef typename Ct::size_type	size_type;

			static void					assign(Os &os, type_value random_value, type_value replacement) {
				{
					Ct	vec;
					vec.assign(20, random_value);
					for (size_type i = 0 ; i < vec.size() ; i++) { os << vec[i] << " "; }
					vec.assign(50, replacement);
					for (size_type i = 0 ; i < vec.size() ; i++) { os << vec[i] << " "; }
					vec.assign(10, random_value);
					for (size_type i = 0 ; i < vec.size() ; i++) { os << vec[i] << " "; }
				} {
					Ct	vecfill(10, random_value);
					vecfill.assign(10, random_value);
					vecfill.assign(20, replacement);
					for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
				} {
					Ct	vecfill(20, random_value);
					vecfill.assign(20, replacement);
					vecfill.assign(30, replacement);
					for (size_type i = 0 ; i < vecfill.size() ; i++) { os << vecfill[i] << " "; }
				}
				os << std::endl;
			}
		};

		void				launch_modifiers() {
			ft::Random<type_value>	random;
			type_value		random_value = random.generate(type_value());
			type_value		replacement = random.generate(type_value());
			typedef		UnitestModifiers<vector_custom, std::ofstream>		modifiers_custom;
			typedef		UnitestModifiers<vector_original, std::ofstream>		modifiers_original;

			type_file		os_std = get_folder_std().get_file("modifiers");
			type_file		os_ft = get_folder_ft().get_file("modifiers");
			modifiers_original::assign(*os_std, random_value, replacement);
			modifiers_custom::assign(*os_ft, random_value, replacement);
		}

};
////////////////////////////////////////////////////////////////////////////////////////////
//

#endif
