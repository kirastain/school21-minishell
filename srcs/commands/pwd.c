/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:49:43 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 15:43:19 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_command(t_command *com, t_struct *conf)
{
	char	*line;
	char	*tmp;

	if (com->args[0] != NULL)
		error_quit("pwd: Too many arguments", conf);
	else
	{
		errno = 0;
		if (!(line = getcwd(NULL, 50)))
			error_quit("Cannot get path", 0);
		else
		{
			tmp = line;
			line = ft_strjoin(line, "\n");
			free(tmp);
		}
		write_command(com, line, conf);
	}
}
