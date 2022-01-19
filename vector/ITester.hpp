/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITester.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:38:05 by guhernan          #+#    #+#             */
/*   Updated: 2022/01/19 20:40:58 by guhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITESTER_HPP
# define ITESTER_HPP

#include <string>
#include <memory>
#include <chrono>
#include <fstream>
#include <map>
#include <iostream>

namespace ft {

	class ITester {

		public:
			typedef		typename std::ofstream	*							type_file;
			typedef		typename std::map< std::string, type_file>			type_f_map;
			typedef		typename std::map< std::string, std::string >		type_fnames_map;

			typedef		typename type_f_map::iterator						iterator_files;
			typedef		typename type_fnames_map::iterator					iterator_files_names;

			typedef		typename std::chrono::duration< int >				type_duration;
			typedef		typename std::map< std::string, type_duration >		type_exec_time;
			typedef		typename type_exec_time::iterator					iterator_exec_time;

			////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////NESTED CLASSES/////////////////////////////////////////////////////
			//
			class Folder {

				private:
					Folder() : _files(), _files_names(), _container_name(), _end_id(), _turn_in_directory() {
					}

				protected:
					type_f_map			_files;
					type_fnames_map		_files_names;
					std::string			_container_name;
					std::string			_end_id;
					std::string			_turn_in_directory;


				public:
					///////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////CONSTRUCTORS////////////////////////////////////////////////
					//
					Folder(const Folder &source)
						: _files(source._files), _files_names(source._files_names),
						_container_name(source._container_name), _end_id(source._end_id),
						_turn_in_directory(source._turn_in_directory) {
						}

					Folder(const std::string &container_name, const std::string &end_id)
						: _files(), _files_names(), _container_name(container_name), _end_id(end_id),
						_turn_in_directory("./gunner_results/") {
						}

					Folder(const std::string &container_name, const std::string &end_id, const std::string &dir_path)
						: _files(), _files_names(), _container_name(container_name), _end_id(end_id),
						_turn_in_directory(dir_path) {
						}

					virtual ~Folder() {
						for (iterator_files it = _files.begin() ; it != _files.end() ; it++) {
							it->second->close();
						}
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////INITIALISATION//////////////////////////////////////////////
					//
					virtual Folder		&_init_folder() {

						this->_files_names["constructor"]=_container_name + "_constructor_results_";
						this->_files_names["accessors"]=_container_name + "_accessors_results_";
						this->_files_names["iterators"]=_container_name + "_iterators_results_";
						this->_files_names["capacity"]=_container_name + "_capacity_results_";
						this->_files_names["modifiers"]=_container_name + "_modifiers_results_";

						// Test if the file exists
						// If true : increment the end_id then try with bigger number
						// Repeat until the file id does doesn't exists
						// // (can be changed)
						for (iterator_files_names it = this->_files_names.begin() ;
								it != this->_files_names.end() ; it++) {
							std::string		test_filename = it->second
								+ _end_id + std::to_string(0);

							std::ifstream	test_file(this->_turn_in_directory + test_filename);

							for (int end_id = 0 ; test_file.is_open() ; ++end_id) {
								test_file.close();
								test_filename = it->second;
								test_filename.append(_end_id + std::to_string(end_id));
								test_file.open(this->_turn_in_directory + test_filename);
							}
							it->second = test_filename;

							this->_files[it->first]= new std::ofstream(this->_turn_in_directory + it->second);
						}
						return *this;
					}

					///////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////OPERATORS///////////////////////////////////////////////////
					//
					Folder	&operator=(const Folder &source) {
						this->_files = source._files;
						this->_files = source._files;
						this->_files_names = source._files_names;
						this->_files_names = source._files_names;
						return *this;
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////ACCESSORS///////////////////////////////////////////////////
					//
					Folder					*get_data() {
						return this;
					}

					std::string				get_file_name(const std::string &key) {
						return _files_names[key];
					}

					type_file				get_file(const std::string &key) {
						return _files[key];
					}

					std::string				get_directory_name() {
						return this->_turn_in_directory;
					}

					std::string				&get_end_id() {
						return this->_end_id;
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////ITERATORS///////////////////////////////////////////////////
					//
					iterator_files			begin_files() {
						return this->_files.begin();
					}

					iterator_files_names	begin_files_names() {
						return this->_files_names.begin();
					}

					iterator_files			end_files() {
						return this->_files.end();
					}

					iterator_files_names	end_files_names() {
						return this->_files_names.end();
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////
			};
			//
			////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////
			//
		protected:
			int					_test_nb;
			type_exec_time		_exec_time;
			Folder				*_folder_std;
			Folder				*_folder_ft;

			ITester() 
				: _test_nb(0), _exec_time(), _folder_std(NULL), _folder_ft(NULL) {
				}

			ITester(const ITester &source)
				: _test_nb(source._test_nb), _exec_time(source._exec_time),
				_folder_std(NULL), _folder_ft(NULL) {
				}

			virtual ~ITester() {
			}


			virtual void		_init_files(std::string container_name = "vector", std::string dir_path = "./gunner_results/") = 0;
			virtual void		_init_exec_time() = 0;

		public:
			////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////INIT//////////////////////////////////////////
			//
			virtual void		init() = 0;
			////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////CONSTRUCTORS//////////////////////////////////
			//
			virtual void		unitest_constructor_empty() = 0;
			virtual void		unitest_constructor_range() = 0;
			virtual void		unitest_constructor_copy() = 0;
			virtual void		unitest_constructor_all() = 0;
			////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////ACCESSORS/////////////////////////////////////
			//
			virtual type_exec_time		&get_exec_time() = 0;
			virtual type_duration		&get_exec_time(const std::string &key) = 0;
			virtual int					get_test_nb() = 0;
			virtual void				get_status() = 0;

			virtual void				unitest_accessors_all() = 0;
			////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////CAPACITY//////////////////////////////////////
			//
			virtual void							unitest_capacity_all() = 0;
			////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////MODIFIERS/////////////////////////////////////
			//
			virtual void							unitest_modifiers_all() = 0;
	};

}

#endif
