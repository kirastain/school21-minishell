/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:49:43 by bbelen            #+#    #+#             */
/*   Updated: 2020/12/02 18:25:28 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    pwd_command(t_command *com)
{
    char    *line;

    if (com->args[0] != NULL)
    {
        ft_putstr_fd("Error: pwd: Too many arguments\n", 0);
        return ;
    }
    else
    {
        errno = 0;
        if (!(line = getcwd(NULL, 50)))
            ft_putstr_fd("Error\n", 0);
        else
        {
            ft_putstr_fd(line, 0);
        }
        if (line)
            free(line);
    }
}
