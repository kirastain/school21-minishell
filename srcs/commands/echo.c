/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:32:08 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/11 17:40:14 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
* Наличие флага -n. Таких может быть несколько подряд, но все должны быть до того, что выводить
*/
static int  check_flag_n(char **args, int *if_n)
{
    int i;

    i = 0;
    while(args[i])
    {
        if (ft_strcmp(args[i], "-n") == 0)
        {
            *if_n = 1;
            i++;
        }
        else
            break ;
    }
    return (i);
}

void    echo_command(t_command *com)
{
    int     i;
    int     if_n;
    char    *response;
    char    *tmp;

    i = 0;
    i = check_flag_n(com->args, &if_n);
    response = ft_strdup("");
    while (com->args[i])
    {
        tmp = response;
        response = ft_strjoin(response, com->args[i]);
        free(tmp);
        i++;
    }
    if (!if_n)
    {
        tmp = response;
        response = ft_strjoin(response, "\n");
        free(tmp);
    }
    write_command(com, response);
}
