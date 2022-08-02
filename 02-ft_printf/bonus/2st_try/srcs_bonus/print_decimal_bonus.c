/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:30 by junji             #+#    #+#             */
/*   Updated: 2022/08/02 09:56:53 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/printf_bonus.h"

int	print_decimal_2(t_option *option, t_tool *tool, long value)
{
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	while (tool->len < (option->precision)--)
		if (write_tool(tool, '0') == -1)
			return (-1);
	if (!tool->precision_value_zero)
		if (ft_putnbr_fd(value, 1, tool) == -1)
			return (-1);
	if (print_width(tool, option) == -1)
		return (-1);
	return (0);
}

int	print_decimal(t_option *option, t_tool *tool, va_list *ap)
{
	long	value;

	value = va_arg(*ap, int);
	tool->len = find_len(value);
	if (option->flag & FLAG_LEFT)
		option->flag &= ~FLAG_ZERO;
	if (option->precision != -1)
		option->flag &= ~FLAG_ZERO;
	if (option->flag & FLAG_ZERO)
		tool->c = '0';
	if (option->precision == 0 && value == 0)
		check_prec_value(tool, option);
	if (option->precision < tool->len)
		option->precision = tool->len;
	option->width -= option->precision;
	check_sign(option, tool, (long *)&value);
	if (!(option->flag & FLAG_ZERO || option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (tool->sign)
		if (write_tool(tool, tool->sign) == -1)
			return (-1);
	if (print_decimal_2(option, tool, value) == -1)
		return (-1);
	return (0);
}
