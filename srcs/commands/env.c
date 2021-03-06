/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:49:04 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 19:32:55 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_command(t_command *com, char **env, t_struct *conf)
{
	int		i;
	char	*response;

	i = 0;
	response = ft_strdup("");
	if (com->args[0] != NULL)
	{
		error_quit("too many arguments", conf);
		return ;
	}
	else
	{
		while (env[i])
		{
			response = ft_strjoin_free(response, env[i++]);
			response = ft_strjoin_free(response, "=");
			response = ft_strjoin_free(response, env[i++]);
			response = ft_strjoin_free(response, "\n");
		}
	}
	write_command(com, response);
}
