/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:25 by junji             #+#    #+#             */
/*   Updated: 2022/08/02 10:01:48 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/printf_bonus.h"

int	print_char(t_option *option, t_tool *tool, va_list *ap)
{
	int				value;
	unsigned char	c;

	value = va_arg(*ap, int);
	c = (unsigned char)value;
	if (!(option->flag & FLAG_LEFT))
	{
		while (--option->width > 0)
		{
			if (write(1, " ", 1) == -1)
				return (-1);
			++tool->printed;
		}
	}
	if (write(1, &c, 1) == -1)
		return (-1);
	++tool->printed;
	while (--option->width > 0)
	{
		if (write(1, " ", 1) == -1)
			return (-1);
		++tool->printed;
	}
	return (0);
}
