/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:24:24 by bbelen            #+#    #+#             */
/*   Updated: 2020/12/02 18:26:05 by bbelen           ###   ########.fr       */
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

void    shell_line(t_struct *conf)
{
    char    *line;
    int     status;

    status = 1;
    while (status)
    {
        if (conf->shell_line)
            free(conf->shell_line);
        conf->shell_line = get_shell_line(conf->env);
        ft_putstr_fd(conf->shell_line, 1);
        get_next_line(0, &line);
        if (ft_strcmp(line, "pwd") == 0)
        {
            pwd_command(conf->command);
        }
        //parser_line(line, conf); <---------------------------------вот здесь уходит в парсер и нужно добавить в структуру
        //status = run_command(conf); <---------------------------------------вот сюда пошла команда
        free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_struct    conf;

    printf("%d %s\n", argc, argv[0]);
    conf.shell_line = NULL;
    init_conf(&conf);
    conf.env = parser_env(envp);
    shell_line(&conf);
    return (0);
}