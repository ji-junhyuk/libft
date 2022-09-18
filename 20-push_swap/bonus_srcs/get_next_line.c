/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:10:28 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 09:17:22 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/get_next_line.h"
#include "../bonus_includes/checker.h"

int	get_stdin(t_list *list1, t_list *list2)
{
	char	*cmd;

	while (1)
	{
		cmd = get_next_line(0);
		if (!cmd)
			break ;
		if (check_valid_command(list1, list2, cmd) == 1)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
	}
	return (0);
}

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
