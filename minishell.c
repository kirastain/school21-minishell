/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:24:24 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/12 01:31:57 by bbelen           ###   ########.fr       */
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

void    shell_line(t_struct *conf)
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
        if (conf->shell_line)
            free(conf->shell_line);
        conf->shell_line = get_shell_line(conf->env);
        ft_putstr_fd(conf->shell_line, 1);
        get_next_line(0, &line);
        if (!if_line_empty(line))
        {
           if (ft_strcmp(line, "pwd") == 0)
            {
                pwd_command(conf->command);
            }
            //check echo here
            else if (ft_strcmp(line, "env") == 0)
            {
                env_command(conf->command, conf->env);
            }
			else if (ft_strcmp(line, "export") == 0)
			{
				export_command(conf->command, conf);
			}
			else if (ft_strcmp(line, "exit") == 0)
			{
				exit_command(conf);
			}
            if (parser_line(line, conf)) // <---------------------вот здесь уходит в парсер и нужно добавить в структуру
            {
				printf("---------------------ok\n");
                //status = run_command(conf); <-------------------------------вот сюда пошла команда 
            }
        }
        free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_struct    conf;

	conf.signal = 0;
	if (argc == 1 && argv[0])
	{
    	conf.shell_line = NULL;
    	init_conf(&conf);
    	conf.env = parser_env(envp);
		signal(SIGINT, work_signals);
		signal(SIGQUIT, work_signals);
    	shell_line(&conf);
    	return (0);
	}
}