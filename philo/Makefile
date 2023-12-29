# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: michang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/25 16:09:17 by michang           #+#    #+#              #
#    Updated: 2023/11/25 16:09:18 by michang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAG = -Wall -Wextra -Werror

DIR = ./
BASE = main initialize philo_run philo_utils utils monitor
SRC = $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ = $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) -I $(dir $<) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -I $(dir $<) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : clean all

.PHONY : all clean fclean re

test : all clean
	./$(NAME) 4 410 200 200