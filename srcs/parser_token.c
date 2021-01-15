/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:07:50 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 19:38:59 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*char	*get_env_var_2(char *arg, char **env)
{
	char	*value;
	char 	*str;
	int		i;

	i = 0;
	value = ft_calloc(sizeof(char), 2);
	while (env[i])
	{
		if (ft_strncmp(arg, env[i], ft_strlen(arg)) == 0)
		{	
			str = ft_strchr(env[i], '=');
			str++;
			free(value);
			value = ft_strdup(str);
			return (value);
		}
		i++;
	}
	return (value);
}*/

char			*quotes(char *token, int *i, int *j, char **env)
{
	char		c;
	char		*str;
	char		*str2;
	char		*tmp;

	c = token[(*i)++];
	*j = *i;
	str2 = ft_calloc(sizeof(char), 2);
	while (token[*i] != c)
	{
		if (*j != *i)
		{
			str = ft_substr(token, *j, *i - *j);
			tmp = ft_strjoin(str2, str);
			free(str2);
			free(str);
			str2 = tmp;
			tmp = NULL;
			*j = *i;
		}
		if (token[*i] == '\\' && c == '\"' && token[*i + 1])
		{
			*j = ++(*i);
		}
		else if (token[*i] == '$' && c == '\"')
		{
			str = find_env_var(token, i, j);
			tmp = get_env_var(str, env);
			free(str);
			str = ft_strjoin(str2, tmp);
			free(str2);
			free(tmp);
			str2 = str;
			*j = (*i);
		}
		else	
			(*i)++;
	}
	if (*j != *i)
	{
		str = ft_substr(token, *j, *i - *j);
		tmp = ft_strjoin(str2, str);
		free(str2);
		free(str);
		str2 = tmp;	
		*j = ++(*i);
	}
	return (str2);
}

char 			*find_env_var(char *token, int *i, int *j)
{
	char *str;

	*j = ++(*i);
	while (ft_strchr("$\\ \'\"", token[*i]) == NULL)
	{
		(*i)++;
	}
	str = ft_substr(token, *j, *i - *j);
	
	return (str);
}

char			*edit_arg_main(char *token, char **env)
{
	int			i;
	int			j;
	char		*str;
	char		*str2;
	char		*tmp;
	
	i = 0;
	j = 0;
	str2 = ft_calloc(sizeof(char), 2);
	while (token[i])
	{
		if (j != i)
		{
			str = ft_substr(token, j, i - j);
			tmp = ft_strjoin(str2, str);
			free(str2);
			free(str);
			str2 = tmp;
			j = i;
		}
		if (token[i] == '\'' || token[i] == '\"')
		{
			str = quotes(token, &i, &j, env);
			tmp = ft_strjoin(str2, str);
			free(str2);
			free(str);	
			str2 = tmp;
		}
		else if (token[i] == '$')
		{
			str = find_env_var(token, &i, &j);
			//printf("found $ arg %s\n", str);
			tmp = get_env_var(str, env);
			free(str);
			str = ft_strjoin(str2, tmp);
			free(str2);
			free(tmp);
			str2 = str;
			j = ++i;
		}
		else
			i++;
	}
	if (j != i)
	{
		str = ft_substr(token, j, i - j);
		tmp = ft_strjoin(str2, str);
		free(str2);
		free(str);
		str2 = tmp;
	}	
	return(str2);
}