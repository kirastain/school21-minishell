/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:41:09 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 10:10:33 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_command(t_struct *conf)
{
	t_command	*com;

	com = conf->command;
	if (ft_arrlen(com->args) > 1)
		error_quit("Too many arguments", conf);
	clear_conf(conf);
	exit(0);
}
