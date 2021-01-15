/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:04:58 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 16:10:39 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		redirect_pipefork(t_struct *conf, int fid,
					char **args, t_command *command_array)
{
	pid_t	curr_pid;
	int		fd[2];
	int		status;

	pipe(fd);
	curr_pid = fork();
	if (curr_pid == 0)
	{
		dup2(fid, fd[1]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (args != NULL)
			execve(args[0], args, conf->env);
		else
			command_hub(command_array, conf);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else if (curr_pid < 0)
	{
		error_quit("FORK", conf);
		exit(1);
	}
	else
		waitpid(curr_pid, &status, WUNTRACED);
}

void		next_pipe(t_struct *conf, int *fd, int pipe_from, int i)
{
	if (pipe_from != STDIN_FILENO)
	{
		dup2(pipe_from, STDIN_FILENO);
		close(pipe_from);
	}
	if (conf->arr_int[i] != 0)
		redirect_pipefork(conf, conf->arr_int[i], conf->arr[i],
			conf->command_array[i]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (conf->arr[i] != NULL)
		execve(conf->arr[i][0], conf->arr[i], NULL);
	else
		command_hub(conf->command_array[i], conf);
	exit(0);
}

void		do_pipes(t_struct *conf, int pipes)
{
	pid_t	pid;
	int		i;
	int		fd[2];
	int		status;
	int		pipe_from;

	pipe_from = dup(STDIN_FILENO);
	i = 0;
	while (i < pipes)
	{
		if (i < pipes - 1)
			pipe(fd);
		pid = fork();
		if (pid < 0)
			error_code("FORK", errno, conf);
		else if (pid == 0)
			next_pipe(conf, fd, pipe_from, i);
		else
			waitpid(pid, &status, WUNTRACED);
		close(fd[1]);
		close(pipe_from);
		pipe_from = fd[0];
		i++;
	}
}

t_command	*pipes_command(t_struct *conf, t_command *com)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (!flag)
	{
		if (if_internal(com->name) == 0)
		{
			conf->arr[i] = outsouce_arr(com, conf);
			conf->command_array[i] = NULL;
		}
		else
		{
			conf->arr[i] = NULL;
			conf->command_array[i] = com;
		}
		conf->arr_int[i++] = get_fd(com, conf);
		flag = 1;
		if (com->pipe_sc == '|')
			flag = 0;
		com = com->next;
	}
	return (com);
}
