/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 07:19:25 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 08:29:39 by jijunhyuk        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/print.h"

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
