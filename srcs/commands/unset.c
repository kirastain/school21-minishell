/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 19:14:10 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/10 16:10:55 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char **create_env(t_command *com, t_struct *conf)
{
    int i;
    int j;
    char    **env;

    i = 0;
    if (!(env = (char **)malloc(sizeof(char *) * 1)))
        return (NULL);
    env[0] = NULL;
    while (conf->env[i])
    {
        j = -1;
        while (com->args[++j])
        {
            if (ft_strcmp(com->args[j], conf->env[i]) == 0)
                break ;
        }
        if (com->args[j] != NULL)
            i = i + 2;
        else
        {
            env = ft_array_realloc(env, conf->env[i++]);
            env = ft_array_realloc(env, conf->env[i++]);
        }
    }
    return (env);
}

void    unset_command(t_command *com, t_struct *conf)
{
    char    **new_env;

    if (!(com->args[0]))
    {
        ft_putstr_fd("Error: unset: Not enough arguments\n", 0);
        return ;
    }
    if (!(new_env = create_env(com, conf)))
    {
        ft_putstr_fd("Error: unset: Can't allocate memory\n", 0);
        return ;
    }
    ft_array_free(conf->env);
    conf->env = NULL; //пришлось вынести сюда из-зз 25 строк в другой
    conf->env = new_env;
}
