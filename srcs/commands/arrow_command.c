/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:56:54 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 20:07:53 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	arrow_command(t_command *com, t_struct *conf)
{
	int	fd;

	if (ft_strcmp(com->arrows[0], "<") == 0 ||
		ft_strcmp(com->arrows[0], ">>") == 0)
		return ;
	if ((fd = open(com->file[0], O_TRUNC)) == -1)
	{
		g_error = "1";
		error_quit("file invalid", conf);
	}
	close(fd);
}
