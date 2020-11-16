# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 23:04:16 by bbelen            #+#    #+#              #
#    Updated: 2020/11/16 23:14:26 by bbelen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC = ./srcs/*.c #убрать * позже
HEADER = ./minishell.h
CC = clang
OBJS = $(SRC:.s=.o) 

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs -o $(NAME) $(OBJS)
	@echo minishell compiled

%.o: %.s 
	@$(CC) $(FLAGS) -o $@ -c $< 

clean:
	@rm -f $(OBJS)
	@echo files cleaned

fclean: clean
	@rm -f $(NAME)
	@echo files cleaned and minishell deleted

re: fclean all

.PHONY: all clean fclean re