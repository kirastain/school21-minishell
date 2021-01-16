/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:37:58 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 12:48:46 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_pwd(char **path, t_struct *conf)
{
	int i;

	i = 0;
	while (conf->env[i] && ft_strcmp(conf->env[i], "OLDPWD") != 0)
		i++;
	if (!(conf->env[i]))
	{
		conf->env = ft_array_realloc(conf->env, "OLDPWD");
		conf->env = ft_array_realloc(conf->env, "");
	}
	free(conf->env[++i]);
	conf->env[i] = ft_strdup(*path);
	free(*path);
	*path = getcwd(NULL, 50);
	i = 0;
	while (conf->env[i] && ft_strcmp(conf->env[i], "PWD") != 0)
		i++;
	if (!(conf->env[i]))
	{
		conf->env = ft_array_realloc(conf->env, "PWD");
		conf->env = ft_array_realloc(conf->env, "");
	}
	free(conf->env[++i]);
	conf->env[i] = ft_strdup(*path);
}

int		error_cd(t_struct *conf, char **cwd, char **path)
{
	free(*cwd);
	if (*path)
		free(*path);
	error_quit("cd: no such file or directory", conf);
	return (1);
}

int		reset_cd(char *cwd, char *path, t_struct *conf)
{
	free(cwd);
	free(path);
	write_command(conf->command, ft_strdup(""), conf);
	return (0);
}

int		cd_command(t_command *com, t_struct *conf)
{
	int			len;
	int			i;
	char		*path;
	char		*cur_path;

	g_error = "0";
	len = ft_arrlen(com->args);
	cur_path = getcwd(NULL, 50);
	path = NULL;
	if (len > 1)
		return (error_cd(conf, &cur_path, &path));
	if (len == 0)
	{
		i = 0;
		while (conf->env[i] && ft_strcmp(conf->env[i], "HOME") != 0)
			i++;
		path = conf->env[i] ? ft_strdup(conf->env[++i]) : ft_strdup(cur_path);
	}
	else
		path = ft_strdup(com->args[0]);
	if (chdir(path) != 0)
		return (error_cd(conf, &cur_path, &path));
	else
		change_pwd(&cur_path, conf);
	return (reset_cd(cur_path, path, conf));
}
