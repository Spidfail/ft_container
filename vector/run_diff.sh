# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_diff.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:29:11 by guhernan          #+#    #+#              #
#    Updated: 2022/01/27 00:41:32 by guhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


rm -f gunner_results/details_*/*

clang++ -Wall -Werror -Wextra -Wshadow main.cpp VectorTester.hpp ITester.hpp IteratorVector.hpp  IteratorTraits.hpp && ./a.out

echo TEST CONSTRUCTOR
vimdiff gunner_results/details_ft/vector_constructor_results_ft0 gunner_results/details_std/vector_constructor_results_std0

echo TEST CAPACITY
vimdiff gunner_results/details_ft/vector_capacity_results_ft0 gunner_results/details_std/vector_capacity_results_std0

echo TEST ACCESSORS
vimdiff gunner_results/details_ft/vector_accessors_results_ft0 gunner_results/details_std/vector_accessors_results_std0

echo TEST MODIFIERS
vimdiff gunner_results/details_ft/vector_modifiers_results_ft0 gunner_results/details_std/vector_modifiers_results_std0

echo TEST ITERATORS
vimdiff gunner_results/details_ft/vector_iterators_results_ft0 gunner_results/details_std/vector_iterators_results_std0

