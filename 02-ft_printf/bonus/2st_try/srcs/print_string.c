/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:46 by junji             #+#    #+#             */
/*   Updated: 2022/08/01 12:11:02 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	ft_strlen(unsigned char *str)
{
	unsigned char	*init_pos;

	init_pos = str;
	if (!str)
		return (6);
	while (*str)
		++str;
	return (str - init_pos);
}

int	print_str2(t_option *option, t_tool *tool, unsigned char *str)
{
	while (option->precision-- > 0)
	{
		if (write_tool(tool, *str) == -1)
			return (-1);
		++str;
	}
	if (print_width(tool, option) == -1)
		return (-1);
	return (0);
}

int	print_str(t_option *option, t_tool *tool, va_list *ap)
{
	unsigned char	*str;

	str = va_arg(*ap, unsigned char *);
	if (!str)
		str = (unsigned char *)"(null)";
	tool->len = ft_strlen(str);
	if (option->precision != -1 && option->precision > tool->len)
		option->precision = tool->len;
	if (option->precision == -1)
		option->width -= tool->len;
	else
		option->width -= option->precision;
	if (!(option->flag & PRECISION))
		option->precision = tool->len;
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (print_str2(option, tool, str) == -1)
		return (-1);
	return (0);
}
