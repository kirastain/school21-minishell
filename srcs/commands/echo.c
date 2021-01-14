/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:32:08 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 15:40:32 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_flag_n(char **args, int *if_n)
{
	int i;

	i = 0;
	*if_n = 0;
	while (args[i])
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

void		echo_command(t_command *com, t_struct *conf)
{
	int		i;
	int		if_n;
	char	*response;

	i = 0;
	i = check_flag_n(com->args, &if_n);
	response = ft_strdup("");
	while (com->args[i])
	{
		if (com->args[i + 1])
			response = ft_strjoin(response, ft_strjoin(com->args[i], " "));
		else
			response = ft_strjoin(response, com->args[i]);
		i++;
	}
	if (if_n == 0)
		response = ft_strjoin(response, "\n");
	write_command(com, response, conf);
}
