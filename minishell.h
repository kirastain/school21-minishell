/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:12:57 by bbelen            #+#    #+#             */
/*   Updated: 2020/12/02 18:21:21 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct  s_command
{
    char                *name;
    char                **args;
    char                *file_in;
    char                *file_out;
    struct s_command    *next;
}               t_command;

typedef struct  s_struct
{
    char        **env; //массив переменных окружения
    char        *shell_line; //изначальная строка, которую считали
    int         signal;
    t_command   *command; //текущая команда
    t_command   **command_array; //массив команд (на случай пайплайна)

}               t_struct;

/*-------------inits-----------------*/

void    init_conf(t_struct *conf);
t_command    *init_command();

/*-------------utils---------------*/

int	    ft_arrlen(char **arr);
char	**ft_array_realloc(char **src, char *line);
void	ft_array_free(char **arr);

/*-------------parser---------------*/

char		**parser_env(char **env);

/*-------------commsnds-------------*/

void    pwd_command(t_command *com);

#endif