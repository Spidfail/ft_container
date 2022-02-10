# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    include.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 17:08:38 by guhernan          #+#    #+#              #
#    Updated: 2022/02/10 17:19:39 by guhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_SRCS_GUNNER 		:= VectorTester.hpp \
					   VectorTesterUtils.hpp \
					   ITester.hpp \
					   ft_random.hpp 

_SRCS_GUNNER_PATH	:= $(addprefix $(SRCS_DIR)/, $(_SRCS_GUNNER_LIST))
