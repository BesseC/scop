# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbesse <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 16:59:01 by cbesse            #+#    #+#              #
#    Updated: 2018/12/21 16:58:50 by cbesse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmat.a
SRC = set_mat4.c mat4_add.c mat4_sub.c mat4_mult.c
OBJ = $(SRC:.c=.o)
CC = cc -g3
FLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Compilation termine"

%.o : %.c
	@echo "\033[0;36m\033[1ACompilation de $@\033[0m"
	@$(CC) $(FLAGS) -I /includes -c $<

clean :
	@rm -rf $(OBJ)
	@echo "\033[1;32mSuppresion des objets ternime\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[1;32mSuppresion de la librairie\033[0m"

re : fclean all

test :
	gcc libmat.a main.c
