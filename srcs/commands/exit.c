/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:41:09 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 19:29:21 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

void	exit_command(t_struct *conf)
{
	t_command	*com;
	int			error;

	g_error = "0";
	com = conf->command;
	if (ft_arrlen(com->args) > 1)
		error_quit("Too many arguments", conf);
	if (com->args[0])
	{
		if (is_numeric(com->args[0]))
			g_error = ft_strdup(com->args[0]);
		else
			error_quit("exit: numeric argument required", conf);
	}
	error = ft_atoi(g_error);
	clear_conf(conf);
	exit(error);
}
