/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:24:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 01:38:56 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char	*get_logname(char **env)
{
	int	i;
	char	*tmp;

	i = 0;
    tmp = NULL;
	while(env[i++])
    {
        if (ft_strcmp(env[i], "LOGNAME") == 0)
        {
            if (tmp)
                free(tmp);
            tmp = ft_strdup(env[++i]);
            break ;
        }
    }
    tmp = ft_strjoin(tmp, ":");
	return (tmp);
}

static char *get_shell_line(char **env)
{
    char    *path;
    char    *tmp;
    int     j;

    tmp = NULL;
	tmp = get_logname(env);
    path = getcwd(NULL, 200);
    j = ft_strlen(path);
    j--;
	while (path[j--])
		if (path[j] == '/')
		{
			tmp = ft_strjoin(tmp, &path[++j]);
			break ;
		}
	if (path)
    	free(path);
	return (ft_strjoin(tmp, "$> "));
}

int     if_line_empty(char *line)
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

void    read_shell_line(t_struct *conf)
{
    char    *line;
    int     status;

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
			command_main(conf);
        }
		if (conf->tokens)
			clear_tokens(conf);
		if (conf->command)
			clear_command(conf->command);
        if (g_shell_line)
            free(g_shell_line);
		if (line)
			free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_struct    conf;

	g_signal = 0;
	conf.error = ft_strdup("0");
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