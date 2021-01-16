/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:05:40 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 18:46:11 by bbelen           ###   ########.fr       */
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
		if (!flag && i == 0 && (line[i] == ';' || line[i] == '|'))
			return (1);
		if (flag == 0 && (line[i] == ' ' || line[i] == 9))
			return (i);
		if ((line[i] == '\"' || line[i] == '\'') && (!line[i - 1] ||
				line[i - 1] != '\\') && !flag)
			flag = 1;
		else if ((line[i] == '\"' || line[i] == '\'') &&
				(!line[i - 1] || line[i - 1] != '\\') && flag)
			flag = 0;
		if (!flag && i != 0 && (line[i] == '|' || line[i] == ';'))
			return (i);
		i++;
	}
	return (i);
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

	i = 0;
	tmp = *line;
	token = NULL;
	while (tmp[i] != '\0')
	{
		while (tmp[i] == ' ' || tmp[i] == 9)
			i++;
		len = count_len(&tmp[i]);
		if (len == 0)
			continue ;
		if (!(token = (char*)malloc(sizeof(char) * (len + 1))))
			error_quit("memory issue", conf);
		ft_strlcpy(token, &tmp[i], len + 1);
		token[len] = '\0';
		conf->tokens = ft_array_realloc(conf->tokens, token);
		free(token);
		i = i + len;
	}
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
	if (g_signal == 8)
		return ;
	split_line(line, conf);
	analyze_tokens(conf, conf->tokens);
}
