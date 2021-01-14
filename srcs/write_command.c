/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:37:04 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 16:14:34 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_fail(char *name, int errnum, char *response, t_struct *conf)
{
	conf->error = ft_strdup("1");
	free(response);
	error_code(name, errnum, conf);
}

static int	return_fd_flag(char *arrow)
{
	int	flag;

	if (ft_strcmp(arrow, ">>") == 0)
		flag = O_RDWR | O_CREAT | O_APPEND;
	else if (ft_strcmp(arrow, ">") == 0)
		flag = O_RDWR | O_CREAT | O_TRUNC;
	else
		flag = O_RDONLY;
	return (flag);
}

void		write_command(t_command *com, char *response, t_struct *conf)
{
	int i;
	int flag;
	int fd;

	i = -1;
	errno = 0;
	printf("write_command\n");
	conf->error = ft_strdup("0");
	if (com->pipe_sc == '|')
		ft_putstr_fd(response, 1);
	else
	{
		if (com->arrows[0] == NULL)
			ft_putstr_fd(response, 1);
		while (com->arrows[++i])
		{
			flag = return_fd_flag(com->arrows[i]);
			if ((fd = open(com->file[i], flag, 0666)) == -1)
				return (write_fail(com->name, errno, response, conf));
			ft_putstr_fd(response, fd);
			if (close(fd) == -1)
				return (write_fail(com->name, errno, response, conf));
		}
	}
	free(response);
}
