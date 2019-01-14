# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbesse <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 16:59:01 by cbesse            #+#    #+#              #
#    Updated: 2019/01/07 16:33:21 by cbesse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmat.a
SRC = set_mat4.c mat4_add.c mat4_sub.c mat4_mult.c mat4_rot.c mat4_scale.c mat4_translate.c vec3_add.c vec3_mult.c vec3_set.c vec3_cross.c vec3_negate.c vec3_sub.c vec3_div.c vec3_norm.c vec3_dot.c vec3_normalize.c
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
