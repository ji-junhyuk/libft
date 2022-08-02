/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:46 by junji             #+#    #+#             */
/*   Updated: 2022/08/02 10:43:00 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	ft_strlen(char *str)
{
	long long		len;
	char			*init_pos;

	init_pos = str;
	if (!str)
		return (6);
	while (*str)
		++str;
	len = str - init_pos;
	if (len >= 2147483647)
		return (-1);
	return (len);
}

int	print_str2(t_option *option, t_tool *tool, char *str)
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
	char	*str;

	str = va_arg(*ap, char *);
	if (!str)
		str = "(null)";
	tool->len = ft_strlen(str);
	if (tool->len == -1)
		return (-1);
	if (option->precision != -1 && option->precision > tool->len)
		option->precision = tool->len;
	if (option->precision == -1)
		option->width -= tool->len;
	else
		option->width -= option->precision;
	if (option->precision == -1)
		option->precision = tool->len;
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (print_str2(option, tool, str) == -1)
		return (-1);
	return (0);
}
