# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    basic_run.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 22:30:55 by guhernan          #+#    #+#              #
#    Updated: 2022/03/30 23:54:00 by guhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

std_time=0
ft_time=0

rand_nb=`expr $RANDOM`

time $(./ft_container rand_nb > diff_ft)
echo "-> TIME FT CONTAINERS"

time $(./std_container rand_nb > diff_std)
echo "-> TIME STD CONTAINERS"

vimdiff diff_ft diff_std
