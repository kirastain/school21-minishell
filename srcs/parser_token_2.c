/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:27:46 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 15:56:48 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *add_char(char *old, char c)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	i = 0;
	j = 0;
	//printf("addding %c to %s\n", c, old);
	if (!(new = (char*)malloc(sizeof(char) * (ft_strlen(old) + 2))))
		return (NULL);
	//printf("addding %c to %s\n", c, old);
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

char	*edit_arg_2(char *token, char **env, int flag)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	printf("first is in env %s\n", env[0]);
	while (token[i])
	{
		if (token[i + 1] && token[i] == '\\' && (token[i + 1] == '\\' ||
				token[i + 1] == '|' || token[i + 1] == ';'))
		{
			i++;
			new = add_char(new, token[i]);
		}
		else if (token[i + 1] && token[i] == '\\' && token[i + 1] == '\'' && flag == 1)
		{
			i++;
			new = add_char(new, token[i]);
		}
		else
			new = add_char(new, token[i]);
		i++;
	}
	free(token);
	return (new);
}