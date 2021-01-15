/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:03:13 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 19:56:16 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_join(char *path, char *curr_path, int flag)
{
	char *new_path;

	new_path = NULL;
	new_path = ft_strdup(curr_path);
	if (curr_path)
		free(curr_path);
	if (flag == 0)
	{
		new_path = ft_strjoin(new_path, "/");
		new_path = ft_strjoin(new_path, path);
	}
	else
		new_path = ft_strjoin(new_path, &path[1]);
	if (path)
		free(path);
	return (new_path);
}

char	*path_new(char *path, char *curr_path, int i)
{
	char	*new_path;

	new_path = NULL;
	new_path = ft_strdup(curr_path);
	if (curr_path)
		free(curr_path);
	new_path = ft_strjoin(new_path, "/");
	new_path = ft_strjoin(new_path, &path[i]);
	return (new_path);
}

char	*path_doubledot(char *path, char *curr_path)
{
	int		i;
	int		j;
	char	*new_path;

	i = 0;
	j = ft_strlen(curr_path) - 1;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
		{
			while (curr_path[j] != '/')
				j--;
			curr_path[j] = '\0';
			j--;
			i += 3;
			continue ;
		}
		else if (path[i] == '.' && path[i + 1] == '.' &&
									path[i + 2] != '/')
			return (NULL);
		else
			break ;
	}
	new_path = path_new(path, curr_path, i);
	return (new_path);
}

int		get_fd(t_command *com, t_struct *conf)
{
	int	fd;
	int	flag;

	if (com->arrows[0] == NULL)
		return (0);
	if (ft_strcmp(com->arrows[0], ">>") == 0)
		flag = O_RDWR | O_CREAT | O_APPEND;
	else if (ft_strcmp(com->arrows[0], ">") == 0)
		flag = O_RDWR | O_CREAT | O_TRUNC;
	else
		flag = O_RDONLY;
	if ((fd = open(com->file[0], flag, 0666)) == -1)
	{
		g_error = "1";
		error_code(com->name, -1, conf);
		return (-1);
	}
	return (fd);
}

char	*outsource_relative(char *path, t_struct *conf)
{
	char	*curr_path;
	char	*new_path;

	new_path = NULL;
	if (!(curr_path = getcwd(NULL, 50)))
		error_quit("Cannot get path", conf);
	if (path[0] == '.' && path[1] == '.')
	{
		new_path = path_doubledot(path, curr_path);
	}
	else if (path[0] == '.' && path[1] == '/')
	{
		new_path = path_join(path, curr_path, 1);
	}
	else
	{
		new_path = path_join(path, curr_path, 0);
	}
	return (new_path);
}
