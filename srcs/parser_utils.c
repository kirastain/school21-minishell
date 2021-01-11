/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 23:41:15 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/12 01:05:19 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*delete_quotes(t_list *token, t_struct *conf)
{
	char	*new;
	char	*old;
	int		len;

	old = token->content;
	len = ft_strlen(old);
	if (!(new = (char*)malloc(sizeof(char) * (len - 1))))
		error_quit("Memory issue", conf);
	ft_strlcpy(new, &old[1], len + 1);
	free(token->content);
	token->content = new;
}

void	replace_env_var(char *arg, t_struct *conf, char **env)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	if (arg[1] == '?')
	{
		new = ft_strdup(&arg[2]);
		tmp = new;
		new = ft_strjoin(conf->error, new);
		free(tmp);
	}
	else
	{
		new = ft_strdup(&arg[1]);
		while (env[i] && ft_strcmp(env[i], new) != 0)
			i++;
		tmp = arg;
		arg = ft_strdup(env[i + 1]);
		free(tmp);
	}
}