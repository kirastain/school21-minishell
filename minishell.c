/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:24:24 by bbelen            #+#    #+#             */
/*   Updated: 2020/11/18 21:31:06 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char *get_shell_line(char **env)
{
    char    *path;

    if(!env)
        return (NULL);
    printf("Gettingcwd\n");
    path = getcwd(NULL, 10);
    return (path);
}

void    shell_line(t_struct *conf)
{
    if (global_path)
        free(global_path);
    global_path = get_shell_line(conf->env);
    //printf("%s\n", conf->shell_line);
}

int main(int argc, char **argv, char **envp)
{
    t_struct    conf;

    if (!argc && !argv)
        return (0);
    global_path = NULL;
    init_conf(&conf);
    conf.env = parser_env(envp);
    shell_line(&conf);
    return (0);
}