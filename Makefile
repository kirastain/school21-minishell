# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 23:04:16 by bbelen            #+#    #+#              #
#    Updated: 2020/12/10 19:07:48 by bbelen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC = ./srcs/inits.c ./minishell.c ./srcs/parser.c ./srcs/utils.c \
		./srcs/commands/pwd.c ./srcs/write_command.c ./srcs/commands/echo.c \
		./srcs/commands/env.c
HEADER = ./minishell.h
CC = clang
OBJS = $(SRC:.c=.o) 

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@cd libft && $(MAKE) bonus
	@cp libft/libft.a ./libft.a
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) libft.a
	@echo minishell compiled

%.o: %.c 
	@$(CC) $(FLAGS) -o $@ -c $< 

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C ./libft
	@echo files cleaned

fclean: clean
	@rm -f $(NAME)
	@rm -f libft.a
	@$(MAKE) fclean -C ./libft
	@echo files cleaned and minishell deleted

re: fclean all

.PHONY: all clean fclean re