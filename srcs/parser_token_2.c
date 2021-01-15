/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:27:46 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 23:56:01 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_char(char *old, char c)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	i = 0;
	j = 0;
	if (!(new = (char*)malloc(sizeof(char) * (ft_strlen(old) + 2))))
		return (NULL);
	if (old)
	{
		while (old[i])
			new[j++] = old[i++];
	}
	new[j] = c;
	new[j + 1] = '\0';
	free(old);
	return (new);
}

int		add_env_var(char **old, char *tmp, char **env)
{
	char	*new;
	char	*env_var;
	char	*env_name;
	char	*old_str;
	int		i;

	i = 1;
	new = NULL;
	old_str = old[0];
	if (!old_str)
		old_str = ft_strdup("");
	while (tmp[i] && ft_isalnum(tmp[i]))
		i++;
	env_name = ft_substr(tmp, 1, i);
	env_var = get_env_var(env_name, env);
	if (env_var != NULL)
		new = ft_strjoin(old_str, env_var);
	else
	{
		new = ft_strdup("");
		new[1] = '\0';
	}
	free(old_str);
	*old = new;
	return (i);
}

int		if_slashes(char *tmp, int flag)
{
	int	i;

	i = 0;
	if (tmp[i + 1] && tmp[i] == '\\' &&
						tmp[i + 1] == '\'' && flag == 1)
		return (1);
	else if (tmp[i + 1] && tmp[i] == '\\' &&
						tmp[i + 1] == '\"' && flag == 2)
		return (1);
	return (0);
}

char	*edit_arg_2(char *token, char **env, int flag)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	new = NULL;
	tmp = token;
	if (flag == 1 || flag == 2)
		tmp = delete_quotes(tmp);
	while (tmp[i])
	{
		if (tmp[i + 1] && tmp[i] == '\\' && (tmp[i + 1] == '\\' ||
						tmp[i + 1] == '|' || tmp[i + 1] == ';'))
			new = add_char(new, tmp[++i]);
		else if (if_slashes(&tmp[i], flag))
			new = add_char(new, tmp[++i]);
		else if (tmp[i] == '$' && (flag == 0 || flag == 2))
			i += add_env_var(&new, &tmp[i], env);
		else
			new = add_char(new, tmp[i]);
		i++;
	}
	return (new);
}
