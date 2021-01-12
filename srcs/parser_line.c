/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:05:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/13 00:32:51 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_len(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"' && line[i] != '\0')
			i++;
		i++;
	}
	else if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i] != '\0')
			i++;
		i++;
	}
	else
	{
		while ((line[i] != ' ' && line[i] != 9) && line[i] != '\0')
		i++;
	}
	return (i);
}

/*
* Разбиение строки на связный список токенов. 
* После нужно обработать полученные токены по правилам последовательности команд терминала
* Команда - флаги - аргументы
* Смотреть на всякие пайпы, > < | ; в соответствии с шеллом
*/
void	split_line(char *line, t_struct *conf)
{
	int		i;
	int		len;
	char	*token;
	t_list	*current;

	i = 0;
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == 9)
			i++;
		len = count_len(&line[i]);
		if (!(token = (char*)malloc(sizeof(char) * (len + 1))))
			return ;
		ft_strlcpy(token, &line[i], len + 1);
		ft_lstadd_back(&(conf->tokens), ft_lstnew(token));
		i = i + len + 1;
	}
	current = conf->tokens;
	while (current)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
}

void	analyze_tokens(t_struct *conf, t_list *tokens)
{
	char	*token;

	while (tokens)
	{
		token = tokens->content;
		if (ft_strcmp(token, ":") == 0 || ft_strcmp(token, "|") == 0)
		{
			conf->betweens = ft_array_realloc(conf->betweens, tokens->next->content);
		}
		else
		{
			create_command(tokens, conf);
		}
		tokens = tokens->next;
	}
}

/*Основная работа со строкой
*Вначале она проверяется на неправильные последовательности символов ы hecking_line
*Далее она должна быть разбита в связный список токенов (split_line), пробелы опущены
*Внутри кавычек сохраняется все содержимое
*Одна кавычка - открывается поток на чтение до закрывающей кавычки
*/
int    	parser_line(char *line, t_struct *conf)
{
    //char    **spaces;

    checking_line(line, conf);
	if (g_signal == 8)
		return ;
	split_line(line, conf);
	analyze_tokens(conf, conf->tokens);
	//tokens = split_tokens(line);
	//analyze_tokens(tokens, conf);
	return (0);
}