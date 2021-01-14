/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:04:41 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 00:43:47 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arrow_from(int fd, char **args, pid_t curr_pid, int *p_fd)
{
	int status;

	close(p_fd[0]);
	p_fd[0] = fd;
	if (curr_pid == 0)
	{
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		close(p_fd[1]);
		execve(args[0], args, NULL);
	}
	else
	{
		close(p_fd[1]);
		waitpid(curr_pid, &status, WUNTRACED);
	}
}

void	arrow_to(int fd, char **args, pid_t curr_pid, int *p_fd)
{
	int status;

	close(p_fd[1]);
	p_fd[1] = fd;
	if (curr_pid == 0)
	{
		dup2(p_fd[1], 1);
		close(p_fd[0]);
		close(p_fd[1]);
		execve(args[0], args, NULL);
	}
	else
	{
		close(p_fd[0]);
		waitpid(curr_pid, &status, WUNTRACED);
	}
}

void	redirect_fork(char *file, char *sym, char **args)
{
	pid_t	curr_pid;
	int		p_fd[2];
	int		fd;

	if (ft_strcmp(sym, ">") == 0)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	else if (ft_strcmp(sym, ">>") == 0)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else if (ft_strcmp(sym, "<") == 0)
		fd = open(file, O_RDONLY);
	curr_pid = fork();
	pipe(p_fd);
	if (ft_strcmp(sym, ">") == 0 || ft_strcmp(sym, ">>") == 0)
		arrow_to(fd, args, curr_pid, p_fd);
	else if (ft_strcmp(sym, "<") == 0)
		arrow_from(fd, args, curr_pid, p_fd);
}

void	do_fork(t_command *com, char **args, t_struct *conf)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		status;

	errno = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, NULL);
	}
	else if (pid == -1)
	{
		error_code(com->name, errno, conf);
	}
	else
	{
		wait_pid = waitpid(pid, &status, WUNTRACED);
	}
	kill(pid, SIGKILL);
}

void	do_forks(t_command *com, char **args, int flag, t_struct *conf)
{
	int i;

	i = 0;
	if (flag == 1 && com->file[i] != NULL)
		while (com->file[i])
		{
			redirect_fork(com->file[i], com->arrows[i], args);
			i++;
		}
	else if (flag == 1 && com->file[i] == NULL)
		do_fork(com, args, conf);
	else
	{
		conf->error = ft_strdup("1");
		if (flag == 0)
		{
			error_code(com->name, 13, conf);
		}
	}
}