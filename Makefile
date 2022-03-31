# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guhernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 21:33:48 by guhernan          #+#    #+#              #
#    Updated: 2022/03/31 13:55:58 by guhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_STD 		:=		std_container
NAME_FT 		:=		ft_container
CC				:=		c++
CSAN			:=		-fsanitize=address
CFLAGS			:=		-Wall -Wextra -Werror -std=c++98
MAIN			:=		main.cpp

MAP_DIR			:=		map
STACK_DIR		:=		stack
VECTOR_DIR		:=		vector
UTILS_DIR		:=		utils

SRCS_DIR		:=		$(MAP_DIR) $(STACK_DIR) $(VECTOR_DIR) $(UTILS_DIR)

UTILS_SRCS 		:=
MAP_SRCS 		:=
VECTOR_SRCS 	:=
STACK_SRCS		:=

include utils/Include.mk
include map/Include.mk
include vector/Include.mk
include stack/Include.mk

UTILS_FILE		:= 		$(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))
MAP_FILE		:= 		$(addprefix $(MAP_DIR)/, $(MAP_SRCS))
VECTOR_FILE		:= 		$(addprefix $(VECTOR_DIR)/, $(VECTOR_SRCS))
STACK_FILE		:= 		$(addprefix $(STACK_DIR)/, $(STACK_SRCS))

INC_FILE		:= 		$(UTILS_FILE) $(MAP_FILE) $(VECTOR_FILE) $(STACK_FILE)

INC				:= 		$(addprefix -I,$(SRCS_DIR))
SRCS			:= 		$(MAIN)

################################################################################

.PHONY: all clean fclean re basic_run 

all :		$(NAME_STD) $(NAME_FT)

$(NAME_STD) :	$(MAIN) $(INC_FILE)
	$(CC) $(CFLAGS) $(INC) -D COMP=0 $< -o $@

$(NAME_FT) :	$(MAIN) $(INC_FILE)
	$(CC) $(CFLAGS) $(INC) -D COMP=1 $< -o $@

basic_run : all
	./basic_run.sh

################################

clean:
	$(RM) $(OBJS) diff_ft diff_std

fclean: clean
	$(RM) $(NAME_STD) $(NAME_FT)

re: fclean all
