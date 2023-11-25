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
\
CC = cc
WFLAG = -Wall -Wextra -Werror

DIR = ./
BASE = philo
SRC = $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ = $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)

%.o : %.c
	$(CC) $(WFLAG) -I $(dir $<) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : clean all

.PHONY : all clean fclean re

party :
	@printf "\033c"
	@echo "\n\033[35m♪┏(・o･)┛♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[1;33m♪┗(・o･)┓♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[36m♪┏(・o･)┛♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[34m♪┗(・o･)┓♪\n"