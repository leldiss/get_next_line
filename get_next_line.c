/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:56:51 by leldiss           #+#    #+#             */
/*   Updated: 2021/12/24 17:56:51 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*subline(char **remainder, char **line)
{
	size_t	len;
	char	*new_remainder;

	len = 0;
	new_remainder = NULL;
	while ((*remainder)[len] != '\n' && (*remainder)[len])
		++len;
	if ((*remainder)[len] == '\n')
	{
		++len;
		*line = ft_substr(*remainder, 0, len);
		new_remainder = ft_strdup(*remainder + len);
	}
	else
		*line = ft_strdup(*remainder);
	free(*remainder);
	return (new_remainder);
}

size_t	get_line(char **remainder, char **line, char **buff, int fd)
{
	size_t	rb;

	rb = 1;
	while (rb && !ft_strchr(*remainder, '\n'))
	{
		rb = read(fd, *buff, BUFFER_SIZE);
		(*buff)[rb] = 0;
		*remainder = ft_strjoin(*remainder, *buff);
	}
	free(*buff);
	*remainder = subline(remainder, line);
	if (!**line)
	{
		free(*line);
		*line = NULL;
	}
	return (rb);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*remainder = NULL;
	size_t		rb;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (read(fd, buff, 0) < 0)
	{
		free(buff);
		return (NULL);
	}
	if (!remainder)
		remainder = ft_strdup("");
	rb = get_line(&remainder, &line, &buff, fd);
	if (!rb && !line)
		return (NULL);
	return (line);
}
