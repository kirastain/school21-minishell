/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:05:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/15 17:53:47 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_len(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		//printf("char is %c flag is %d\n", line[i], flag);
		if (!flag && i == 0 && (line[i] == ';' || line[i] == '|'))
		{
			//printf("furute pipe_sc busted %c\n", line[i]);
			return (1);
		}
		if (flag == 0 && (line[i] == ' ' || line[i] == 9))
		{
			//printf("here token len is %d\n", i);
			return (i);
		}
		if ((line[i] == '\"' || line[i] == '\'') && (!line[i - 1] || line[i - 1] != '\\') && !flag)
			flag = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && (!line[i - 1] || line[i - 1] != '\\') && flag)
			flag = 0;
		if (!flag && i != 0 && (line[i] == '|' || line[i] == ';'))
			return (i);
		i++;
	}
	//printf("token len is %d\n", i);
	return (i);
	/*
	if (line[i] == '\"')
	{
		//i++;
		while (line[i++] != '\0' && line[i] != '\"')
			i++;
		i++;
	}
	else if (line[i] == '\'')
	{
		//i++;
		while (line[i++] != '\0' && line[i] != '\'')
			i++;
		i++;
	}
	else if (line[i] == ';' || line[i] == '|')
		return (1);
	else
	{
		while (line[i] != '\0' && (line[i] != ' ' && line[i] != 9))
		{
			if ((line[i] == ';' || line[i] == '|') && i != 0)
				return (i);
			i++;
		}
		//printf("stopped on %c\n", line[i]);
	}
	return (i);*/
}

/*
** Разбиение строки на связный список токенов.
** После нужно обработать полученные токены по правилам
** последовательности команд терминала
** Команда - флаги - аргументы
** Смотреть на всякие пайпы, > < | ; в соответствии с шеллом
*/

void	split_line(char **line, t_struct *conf)
{
	int		i;
	int		len;
	char	*token;
	char	*tmp;
	//t_list	*current;

	i = 0;
	tmp = *line;
	token = NULL;
	//printf("-line tmp is %s-\n", tmp);
	while (tmp[i] != '\0')
	{
		while (tmp[i] == ' ' || tmp[i] == 9)
		{
			//printf("space skipped\n");
			i++;
		}
		len = count_len(&tmp[i]);
		if (!(token = (char*)malloc(sizeof(char) * (len + 1))))
			return ;
		ft_strlcpy(token, &tmp[i], len + 1);
		token[len] = '\0';
		//printf("token is %s\n", token);
		conf->tokens = ft_array_realloc(conf->tokens, token);
		free(token);
		//ft_lstadd_back(&(conf->tokens), ft_lstnew(token));
		i = i + len;
		//if (tmp[i + 1])
		//{
		//	printf("there is %c\n", tmp[i]);
		//	i++;
		//}
		//printf("next from %s\n", line[i]);
	}
	i = 0;
	while (conf->tokens[i])
	{
		//printf("token is %s\n", conf->tokens[i]);
		i++;
	}
	//current = conf->tokens;
	//while (current)
	//{
	//	printf("token is %s\n", current->content);
	//	current = current->next;
	//}
	//free(tmp);
}

/*
** Основная работа со строкой
** Вначале она проверяется на неправильные последовательности символов
** Далее она должна быть разбита в связный список токенов (split_line),
** пробелы опущены
** Внутри кавычек сохраняется все содержимое
** Одна кавычка - открывается поток на чтение до закрывающей кавычки
*/

void	parser_line(char **line, t_struct *conf)
{
	init_betweens(conf);
	checking_line(*line, conf);
	//printf("checking line ok:%s\n", *line);
	if (g_signal == 8)
		return ;
	split_line(line, conf);
	//printf("to analyze\n");
	analyze_tokens(conf, conf->tokens);
}
