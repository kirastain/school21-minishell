/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:33:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 15:20:33 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char *arg, char **env)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (env[i])
	{
		if (ft_strcmp(arg, env[i]) == 0)
		{
			value = ft_strdup(env[i + 1]);
			return (value);
		}
		i++;
	}
	return (NULL);
}

t_list	*create_command(t_list *tokens, t_struct *conf)
{
	t_command	*com;
	int			flag_name;
	char		*arg;

	com = NULL;
	com = init_command(conf);
	arg = NULL;
	flag_name = 0;
	if (!(com = init_command(conf)))
		error_quit("Memory issue", conf);
	printf("com init done\n");
	printf("tokens len is %d\n", ft_lstsize(tokens));
	while ((tokens != NULL) && !(is_command_end(tokens->content)))
	{
		if (flag_name == 0)
		{
			if (!(if_command_name(tokens->content, get_env_var("PATH", conf->env))))
				error_quit("Command not found", conf);
			printf("com name found\n");
			com->name = ft_strdup(tokens->content);
			flag_name = 1;
			printf("com name is %s\n", com->name);
		}
		else 
		{
			printf("Args found...\n");
			if (!(arg = edit_arg(tokens->content)))
				error_quit("Invalid argument\n", conf);
			com->args = ft_array_realloc(com->args, arg);
			if (arg)
				free(arg);
		}
		printf("Next token...\n");
		tokens = tokens->next;
	}
	printf("adding com to the list...\n");
	ft_comadd_back(&(conf->command), com);
	printf("com added\n");
	return (tokens);
}

void	analyze_tokens(t_struct *conf, t_list *tokens)
{
	char	*token;

	while (tokens)
	{
		token = tokens->content;
		printf("our token is %s\n", token);
		if (ft_strcmp(token, ":") == 0 || ft_strcmp(token, "|") == 0)
		{
			conf->betweens = ft_array_realloc(conf->betweens, tokens->content);
		}
		else
		{
			printf("Start creating command\n");
			tokens = create_command(tokens, conf);
			printf("command created\n");
		}
		if (tokens)
			tokens = tokens->next;
	}
	printf("analyze finished\n");
}