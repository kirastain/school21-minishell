/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:12:57 by bbelen            #+#    #+#             */
/*   Updated: 2020/11/22 19:02:41 by bbelen           ###   ########.fr       */
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
    char    *name;
    char    **flags;
}               t_command;

typedef struct  s_struct
{
    char        **env;
    char        *shell_line;
    int         signal;
    t_command   *command;
}               t_struct;

/*-------------inits-----------------*/

void    init_conf(t_struct *conf);

/*-------------utils---------------*/

int	    ft_arrlen(char **arr);
char	**ft_array_realloc(char **src, char *line);
void	ft_array_free(char **arr);

/*-------------parser---------------*/

char		**parser_env(char **env);

#endif