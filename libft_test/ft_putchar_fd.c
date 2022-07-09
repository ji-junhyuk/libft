/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:32:05 by junji             #+#    #+#             */
/*   Updated: 2022/05/25 18:41:16 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}
//
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
//	for (int idx = 0; idx < 26; ++idx)
//		ft_putchar_fd(c + idx, fd);
//	close(fd);
//}
