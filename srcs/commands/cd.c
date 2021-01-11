/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:37:58 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/11 17:49:48 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_pwd(char **cwd, t_struct *conf)
{
	int i;

	i = 0;
	while (conf->env[i] && ft_strcmp(conf->env[i], "OLDPWD") != 0)
		i++;
	if (!(conf->env[i]))
	{
		conf->env = ft_realloc_mass(conf->env, "OLDPWD");
		conf->env = ft_realloc_mass(conf->env, "");
	}
	free(conf->env[++i]);
	conf->env[i] = ft_strdup(*cwd);
	free(*cwd);
	*cwd = getcwd(NULL, 10);
	i = 0;
	while (conf->env[i] && ft_strcmp(conf->env[i], "PWD") != 0)
		i++;
	if (!(conf->env[i]))
	{
		conf->env = ft_array_realloc(conf->env, "PWD");
		conf->env = ft_array_realloc(conf->env, "");
	}
	free(conf->env[++i]);
	conf->env[i] = ft_strdup(*cwd);
}

int		fail_cd(t_struct *conf, char **cwd, char **path)
{
	free(*cwd);
	if (*path)
		free(*path);
	error_quit("cd: Too many arguments\n", conf);
	return (1);
}

int		reset_cd(char *cwd, char *path, t_command *command)
{
	free(cwd);
	free(path);
	write_in_file(command, ft_strdup(""));
	return (0);
}

int		cd_command(t_command *com, t_struct *conf)
{
	int			len;
	int			i;
	char		*path;
	char		*cwd;

	errno = 0;
	len = ft_arrlen(com->args);
	cwd = getcwd(NULL, 10);
	path = NULL;
	if (len > 1)
		return (fail_cd(conf, &cwd, &path));
	if (len == 0)
	{
		i = 0;
		while (conf->env[i] && ft_strcmp(conf->env[i], "HOME") != 0)
			i++;
		path = conf->env[i] ? ft_strdup(conf->env[++i]) : ft_strdup(cwd);
	}
	else
		path = ft_strdup(com->args[0]);
	if (chdir(path) != 0)
		return (fail_cd(conf, &cwd, &path));
	else
		change_pwd(&cwd, conf);
	return (reset_cd(cwd, path, com));
}