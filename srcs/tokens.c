/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:33:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/14 23:32:57 by bbelen           ###   ########.fr       */
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

int		if_internal(char *name)
{
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	return (0);
}

t_list	*create_command(t_list *tokens, t_struct *conf)
{
	t_command	*com;
	int			flag_name;
	char		*arg;

	arg = NULL;
	flag_name = 0;
	if (!(com = init_command(conf)))
		error_quit("Memory issue", conf);
	printf("tokens len is %d with first as %s\n", ft_lstsize(tokens), tokens->content);
	while (tokens != NULL)
	{
		if (flag_name == 0)
		{
			if (!(if_internal(tokens->content)) && !(if_command_name(tokens->content, get_env_var("PATH", conf->env))))
				error_code(tokens->content, -5, conf);
			com->name = ft_strdup(tokens->content);
			flag_name = 1;
			printf("com name is %s\n", com->name);
		}
		else if (ft_strcmp(tokens->content, ">") == 0 || ft_strcmp(tokens->content, "<") == 0 ||
					ft_strcmp(tokens->content, ">>") == 0)
		{
			printf("arrow found\n");
			com->arrows = ft_array_realloc(com->arrows, tokens->content);
			tokens = tokens->next;
			com->file = ft_array_realloc(com->file, tokens->content);
		}
		else if (ft_strcmp(tokens->content, "|") == 0 || ft_strcmp(tokens->content, ";") == 0)
		{
			com->pipe_sc = ((char*)(tokens->content))[0];
			printf("pipe_sc is %c\n", com->pipe_sc);
			//tokens = tokens->next;
			break ;
		}
		else
		{
			printf("arg is %s\n", tokens->content);
			if (!(arg = edit_arg(tokens->content, conf)))
				error_quit("Invalid argument", conf);
			com->args = ft_array_realloc(com->args, arg);
			if (arg)
				free(arg);
		}
		if (is_command_end(tokens->content))
		{
			ft_comadd_back(&(conf->command), com);
			return (tokens->next);
		}
		tokens = tokens->next;
	}
	ft_comadd_back(&(conf->command), com);
	printf("com added\n");
	return (tokens);
}

void	analyze_tokens(t_struct *conf, t_list *tokens)
{
	char	*token;
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		token = tmp->content;
		printf("our token is %s\n", token);
		if (ft_strcmp(token, ":") == 0 || ft_strcmp(token, "|") == 0)
		{
			conf->betweens = ft_array_realloc(conf->betweens, tokens->content);
		}
		else
		{
			printf("hey command\n");
			tmp = create_command(tmp, conf);
			printf("command created\n");
		}
		if (tmp)
			tmp = tmp->next;
	}
	//clear_tokens(conf);
	printf("analyze finished\n");
}