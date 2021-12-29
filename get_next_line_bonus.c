/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:36:27 by leldiss           #+#    #+#             */
/*   Updated: 2021/12/29 15:08:17 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(int fd, char *buff, char *remainder)
{
	long	count;
	char	*tmp;

	count = 1;
	while (count)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1)
			return (0);
		else if (count == 0)
			break ;
		buff[count] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		tmp = remainder;
		remainder = ft_strjoin(tmp, buff);
		tmp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (remainder);
}

char	*subline(char *line)
{
	long	len;
	char	*new_remainder;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	if (line[len] == '\0')
		return (NULL);
	new_remainder = ft_substr(line, len + 1, ft_strlen(line) - len);
	if (*new_remainder == '\0')
	{
		free(new_remainder);
		new_remainder = NULL;
	}
	line[len + 1] = '\0';
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*remainder[10400];

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, NULL, 0) < 0 || fd > 10400)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	line = get_line(fd, buff, remainder[fd]);
	free(buff);
	buff = NULL;
	if (!line)
		return (NULL);
	remainder[fd] = subline(line);
	return (line);
}
