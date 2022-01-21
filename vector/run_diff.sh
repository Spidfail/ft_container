# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_diff.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:29:11 by guhernan          #+#    #+#              #
#    Updated: 2022/01/21 18:04:15 by guhernan         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


rm -f gunner_results/details_*/*

clang++ -Wall -Werror -Wextra -Wshadow -fsanitize=address -g3 main.cpp main.hpp ITester.hpp && ./a.out

diff gunner_results/details_ft/vector_constructor_results_ft0 gunner_results/details_std/vector_constructor_results_std0

diff gunner_results/details_ft/vector_capacity_results_ft0 gunner_results/details_std/vector_capacity_results_std0

diff gunner_results/details_ft/vector_accessors_results_ft0 gunner_results/details_std/vector_accessors_results_std0

diff gunner_results/details_ft/vector_modifiers_results_ft0 gunner_results/details_std/vector_modifiers_results_std0

