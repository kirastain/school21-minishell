/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:24:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 11:45:10 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char	*get_logname(char **env)
{
	int		i;
	char	*tmp;
	char	*temp;

	i = 0;
	tmp = NULL;
	while (env[i++])
	{
		if (ft_strcmp(env[i], "LOGNAME") == 0)
		{
			tmp = ft_strdup(env[++i]);
			break ;
		}
	}
	temp = ft_strjoin(tmp, ":");
	free(tmp);
	return (temp);
}

static char	*get_shell_line(char **env)
{
	char	*path;
	char	*tmp;
	int		j;

	tmp = NULL;
	tmp = get_logname(env);
	path = getcwd(NULL, 50);
	j = ft_strlen(path);
	j--;
	while (path[j--])
		if (path[j] == '/')
		{
			tmp = ft_strjoin_free(tmp, &path[++j]);
			break ;
		}
	if (path)
		free(path);
	tmp = ft_strjoin_free(tmp, "$> ");
	return (tmp);
}

int			if_line_empty(char *line)
{
	if (ft_strcmp(line, "") == 0)
		return (1);
	while (*line != '\0')
	{
		if (*line != ' ')
			return (0);
		line++;
	}
	return (1);
}

void		read_shell_line(t_struct *conf)
{
	char	*line;
	int		status;

	status = 1;
	while (status)
	{
		line = NULL;
		g_signal = 0;
		g_shell_line = get_shell_line(conf->env);
		ft_putstr_fd(g_shell_line, 1);
		gnl_shell(0, &line, conf);
		if (!if_line_empty(line))
		{
			parser_line(&line, conf);
			if (g_signal != 8)
				command_main(conf);
			clear_conf(conf);
		}
		if (conf->command)
			clear_conf(conf);
		if (g_shell_line)
			free(g_shell_line);
		free(line);
	}
}

int			main(int argc, char **argv, char **envp)
{
	t_struct	conf;

	g_signal = 0;
	g_error = "0";
	g_flag = 0;
	g_shell_line = NULL;
	if (argc == 1 && argv[0])
	{
		init_conf(&conf);
		conf.env = parser_env(envp);
		signal(SIGINT, work_signals);
		signal(SIGQUIT, work_signals);
		read_shell_line(&conf);
		return (0);
	}
}
