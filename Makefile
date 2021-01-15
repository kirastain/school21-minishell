# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 23:04:16 by bbelen            #+#    #+#              #
#    Updated: 2021/01/15 23:00:45 by bbelen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC = ./srcs/inits.c ./minishell.c ./srcs/parser.c ./srcs/utils.c \
		./srcs/commands/pwd.c ./srcs/write_command.c ./srcs/commands/echo.c \
		./srcs/commands/env.c ./srcs/commands/unset.c \
		./srcs/checks.c ./srcs/parser_line.c ./srcs/errors.c \
		./srcs/signals.c ./srcs/free.c ./srcs/commands/exit.c \
		./srcs/commands/export_utils.c ./srcs/commands/export.c \
		./srcs/get_next_line_shell.c ./srcs/commands/command_main.c \
		./srcs/commands/cd.c ./srcs/commands/outsource.c \
		./srcs/tokens.c ./srcs/tokens_utils.c ./srcs/file.c ./srcs/forks.c \
		./srcs/commands/redirect.c ./srcs/pipes.c ./srcs/parser_token.c \
		./srcs/parser_token_2.c ./srcs/checks_quotes.c ./srcs/parser_utils.c
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