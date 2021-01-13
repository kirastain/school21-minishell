/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:24:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 02:16:58 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char *get_shell_line(char **env)
{
    char    *path;
    int     i;
    char    *tmp;
    int     j;

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
    path = getcwd(NULL, 50); //понять бы с размерностью, ибо если выделено меньше байт, то возвращает null
    j = ft_strlen(path);
    j--;
	while (path[j--])
    {
		if (path[j] == '/')
		{
			tmp = ft_strjoin(tmp, &path[++j]);
			break ;
		}
    }
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
		if (conf->tokens)
			clear_tokens(conf);
		if (conf->command_array)
			clear_command(conf->command_array);
        if (g_shell_line)
            free(g_shell_line);
		g_signal = 0;
        g_shell_line = get_shell_line(conf->env);
        ft_putstr_fd(g_shell_line, 1);
        gnl_shell(0, &line, conf);
        if (!if_line_empty(line))
        {
			printf("go into parser\n");
            parser_line(line, conf); // <---------------------вот здесь уходит в парсер и нужно добавить в структуру
			printf("---------------------ok\n");
			command_main(conf);
        }
        free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_struct    conf;

	g_signal = 0;
	conf.error = '0';
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