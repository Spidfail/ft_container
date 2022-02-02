# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_diff.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:29:11 by guhernan          #+#    #+#              #
#    Updated: 2022/02/02 21:16:57 by guhernan         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

if [ $# -eq 0 ]
then
	_NB=0
else
	_NB=$1
fi

_ID_STD=std
_ID_FT=ft

_DIR_STD_BEG="gunner_results/details_${_ID_STD}/vector"
_DIR_FT_BEG="gunner_results/details_${_ID_FT}/vector"

_DIR_STD_END="results_${_ID_STD}"
_DIR_FT_END="results_${_ID_FT}"

_CONSTRUCTOR=_constructor_
_CAPACITY=_capacity_
_ACCESSORS=_accessors_
_MODIFIERS=_modifiers_
_ITERATORS=_iterators_

test_diff() {
	if [ "$(diff ${_DIR_STD_BEG}$1${_DIR_STD_END}${_NB} ${_DIR_FT_BEG}$1${_DIR_FT_END}${_NB})" ]
	then
		vimdiff "${_DIR_STD_BEG}$1${_DIR_STD_END}${_NB}" "${_DIR_FT_BEG}$1${_DIR_FT_END}${_NB}"
	fi
}

rm -f gunner_results/details_*/*

clang++ -Wall -Werror -Wextra -Wshadow -fsanitize=address -g3 main.cpp VectorTester.hpp ITester.hpp IteratorVector.hpp  IteratorTraits.hpp && ./a.out \
&& test_diff ${_CONSTRUCTOR} \
&& test_diff ${_CAPACITY} \
&& test_diff ${_ACCESSORS} \
&& test_diff ${_MODIFIERS} \
&& test_diff ${_ITERATORS} 
