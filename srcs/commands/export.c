/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:46:48 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 23:14:18 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		check_arg(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '=' || ft_isdigit(args[i][0]))
			return (1);
		i++;
	}
	return (0);
}

void	export_command_2(t_struct *conf, t_command *com, int i)
{
	int		j;

	j = 0;
	while (com->args[i][j] && com->args[i][j] != '=')
		j++;
	if (com->args[i][j] != '\0')
	{
		if (check_arg_env(conf->env, com->args[i]) == 1)
			conf->env = change_exist_arg(conf->env, com->args[i]);
		else
			conf->env = add_arg_new(conf->env, com->args[i]);
	}
	else
		conf->export = ft_array_realloc(conf->export, com->args[i]);
}

void	export_command(t_command *com, t_struct *conf)
{
	int	i;

	i = 0;
	if (com->args[0] == NULL)
	{
		env_command(com, conf->env, conf);
		while (conf->export[i] != NULL)
		{
			ft_putstr_fd(conf->export[i], 1);
			ft_putstr_fd("=' '\n", 1);
			i++;
		}
	}
	else if ((check_arg(com->args)) == 1)
		error_quit("wrong identifier in export", conf);
	i = 0;
	while (com->args[i])
		export_command_2(conf, com, i++);
}
