/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:49:43 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 19:36:00 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_command(t_command *com, t_struct *conf)
{
	char	*line;
	char	*tmp;

	if (!(line = getcwd(NULL, 50)))
		error_quit("Cannot get path", conf);
	else
	{
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
	}
	write_command(com, line);
}
