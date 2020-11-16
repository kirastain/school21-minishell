/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 20:45:56 by lryan             #+#    #+#             */
/*   Updated: 2020/08/20 15:19:28 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*fill_buff(char **left, int fd, char *buff)
{
	char		*temp;

	if (left[fd])
	{
		temp = ft_strdup(left[fd]);
		free(left[fd]);
		left[fd] = ft_strjoin(temp, buff);
		free(temp);
	}
	else
		left[fd] = ft_strdup(buff);
	return (left[fd]);
}

static char		*what_left(char **left, int fd)
{
	char		*temp;
	int			i;

	i = 0;
	if (!left[fd])
		return (0);
	while (left[fd][i] && left[fd][i] != '\n')
		i++;
	if (left[fd][i] == '\0')
	{
		free(left[fd]);
		return (0);
	}
	temp = ft_substr(left[fd], i + 1, ft_strlen(left[fd]) - i - 1);
	free(left[fd]);
	return (temp);
}

static char		*get_line(char **left, int fd)
{
	int			i;
	char		*temp;
	int			j;

	j = 0;
	i = 0;
	if (!left[fd])
		return (0);
	while (left[fd][j] && left[fd][j] != '\n')
		j++;
	temp = ft_calloc(j + 1, 1);
	while (left[fd][i] && left[fd][i] != '\n')
	{
		temp[i] = left[fd][i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

static int		is_strchr(char **left, int fd)
{
	int		i;

	i = 0;
	if (!left[fd])
		return (0);
	while (left[fd][i])
	{
		if (left[fd][i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*left[65535];
	char		buff[BUFFER_SIZE + 1];
	int			rd;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	rd = 1;
	while (is_strchr(left, fd) == 0 && rd != 0)
	{
		if ((rd = read(fd, buff, BUFFER_SIZE)) >= 0)
		{
			buff[rd] = '\0';
			left[fd] = fill_buff(left, fd, buff);
		}
		else
			return (-1);
	}
	*line = get_line(left, fd);
	left[fd] = what_left(left, fd);
	if (rd == 0)
		return (0);
	return (1);
}
