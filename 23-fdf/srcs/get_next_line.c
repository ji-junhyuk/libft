/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:06:37 by junji             #+#    #+#             */
/*   Updated: 2022/10/21 14:43:53 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*read_line(int fd, char *buffer)
{
	char		temp[BUFFER_SIZE + 1];
	ssize_t		read_size;

	temp[0] = 0;
	while (!ft_strchr(temp, '\n'))
	{
		read_size = read(fd, temp, BUFFER_SIZE);
		if (read_size == 0)
			break ;
		if (read_size == -1)
		{
			if (buffer)
				free(buffer);
			return (0);
		}
		temp[read_size] = '\0';
		if (!buffer)
			buffer = ft_strdup(temp);
		else
			buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return (0);
	}
	return (buffer);
}

char	*extract_line(char *buffer)
{
	int		len;
	char	*line;

	len = 0;
	while (*buffer != '\n' && *buffer)
	{
		++len;
		++buffer;
	}
	if (*buffer == '\n')
		line = ft_substr(buffer - len, 0, len + 1);
	else
		line = ft_strdup(buffer - len);
	return (line);
}

char	*change_next_line(char *buffer)
{
	char	*next_line;
	char	*init_pos;
	int		len;

	init_pos = buffer;
	while (*buffer != '\n' && *buffer)
		++buffer;
	len = buffer - init_pos;
	if (!(*buffer))
	{
		free(buffer - len);
		return (0);
	}
	buffer -= len;
	next_line = ft_substr(buffer, len + 1, ft_strlen(buffer + len + 1));
	free(buffer);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (fd < 0)
		return (0);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (0);
	line = extract_line(buffer);
	buffer = change_next_line(buffer);
	return (line);
}
