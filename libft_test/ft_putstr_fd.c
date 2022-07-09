/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:42:17 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 10:12:17 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//#include <fcntl.h>
//int main(void)
//{
//	int		fd;
//	char	c;
//	c = 'a';
//	fd = open("1", O_RDWR);
//		ft_putstr_fd("0123456789", fd);
//	close(fd);
//}
//
