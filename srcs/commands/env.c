/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:49:04 by bbelen            #+#    #+#             */
/*   Updated: 2020/12/10 19:02:20 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    env_command(t_command *com, char **env)
{
    int     i;
    char    *response;

    i = 0;
    response = ft_strdup("");
    if (com->args[0] != NULL)
    {
        ft_putstr_fd("Error: env: Too many arguments\n", 0);
        return ;
    }
    else
    {
        while (env[i])
        {
            response = ft_strjoin(response, env[i++]);
            response = ft_strjoin(response, "=");
			response = ft_strjoin(response, env[i++]);
			response = ft_strjoin(response, "\n");
        }
    }
    write_command(com, response);    
}
