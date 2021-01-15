/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outsource.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:10:13 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 20:38:17 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*path_com(char *name, char **env)
{
	char	**path;
	int		i;
	int		j;

	i = 0;
	while (env[i] && ft_strcmp(env[i], "PATH") != 0)
		i++;
	if (env[i] && env[++i])
	{
		path = ft_split(env[i], ':');
		j = -1;
		while (path[++j])
		{
			path[j] = ft_strjoin(path[j], "/");
			path[j] = ft_strjoin(path[j], name);
			if (open(path[j], O_RDONLY) != -1)
			{
				name = ft_strdup(path[j]);
				break ;
			}
		}
		ft_array_free(path);
	}
	return (name);
}

void	get_com_path(t_struct *conf, char **args, int *name)
{
	*name = 0;
	if (args[0][0] == '/')
		*name = 0;
	else if (is_in(args[0], '/'))
		args[0] = outsource_relative(args[0], conf);
	else
	{
		args[0] = path_com(args[0], conf->env);
		*name = 1;
	}
}

int		check_outsource(char *file, t_command *com, int name, t_struct *conf)
{
	int			flag;
	int			fd;
	struct stat	buffer;

	flag = 0;
	if ((fd = open(file, O_RDONLY)) == (-1))
	{
		if (name == 1)
		{
			g_error = "127";
		}
		else
			g_error = "1";
		error_code(com->name, -5, conf);
		flag = -1;
		return (flag);
	}
	fstat(fd, &buffer);
	if ((buffer.st_mode & S_IRWXU) == (S_IXUSR) ||
	(buffer.st_mode & S_IRWXU) == (S_IXUSR + S_IWUSR) ||
	(buffer.st_mode & S_IRWXU) == (S_IXUSR + S_IRUSR) ||
	(buffer.st_mode & S_IRWXU) == (S_IXUSR + S_IRUSR + S_IWUSR))
		flag = 1;
	close(fd);
	return (flag);
}

char	**outsouce_arr(t_command *com, t_struct *conf)
{
	char	**args;
	int		name;
	int		flag;
	int		i;

	i = 0;
	if (!(args = (char**)malloc(sizeof(char*))))
		error_quit("Memory issue", conf);
	args[0] = NULL;
	args = ft_array_realloc(args, com->name);
	while (com->args[i])
		args = ft_array_realloc(args, com->name);
	get_com_path(conf, args, &name);
	g_flag = 1;
	g_error = "0";
	flag = check_outsource(args[0], com, name, conf);
	return (args);
}

void	outsource(t_command *com, t_struct *conf)
{
	char	**args;
	int		i;
	int		name;
	int		flag;

	i = 0;
	if (!(args = (char**)malloc(sizeof(char*))))
		error_quit("Memory issue", conf);
	args[0] = NULL;
	args = ft_array_realloc(args, com->name);
	while (com->args[i])
		args = ft_array_realloc(args, com->args[i++]);
	get_com_path(conf, args, &name);
	g_flag = 1;
	g_error = "0";
	flag = check_outsource(args[0], com, name, conf);
	do_forks(com, args, flag, conf);
	ft_array_free(args);
}
