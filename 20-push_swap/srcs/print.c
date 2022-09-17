/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:55:38 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 09:32:01 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *str)
{
	char	*init_pos;

	init_pos = str;
	while (*str)
		++str;
	return (str - init_pos);
}

void	ft_putstr(char *str)
{
	ssize_t	len;

	len = ft_strlen(str);
	if (write(1, str, len) != len)
		exit(1);
}

void	put_error(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(2, str, len);
	exit(1);
}
