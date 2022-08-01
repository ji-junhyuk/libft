/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_undecimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:53 by junji             #+#    #+#             */
/*   Updated: 2022/08/01 14:41:56 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	print_un_decimal_2(t_option *option, t_tool *tool, unsigned int value)
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
	while ((option->width)-- > 0)
		if (write_tool(tool, tool->c) == -1)
			return (-1);
	return (0);
}

int	print_un_decimal(t_option *option, t_tool *tool, va_list *ap)
{
	unsigned int	value;

	value = va_arg(*ap, unsigned int);
	tool->len = find_len(value);
	if (option->precision == 0 && value == 0)
		check_prec_value(tool, option);
	if (option->precision < tool->len)
		option->precision = tool->len;
	option->width -= option->precision;
	if (option->flag & FLAG_LEFT)
		option->flag &= ~FLAG_ZERO;
	if (option->flag & PRECISION)
		option->flag &= ~FLAG_ZERO;
	if (option->flag & FLAG_ZERO)
		tool->c = '0';
	check_un_sign(option, tool);
	if (!(option->flag & FLAG_ZERO || option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (tool->sign)
		if (write_tool(tool, tool->sign) == -1)
			return (-1);
	if (print_un_decimal_2(option, tool, value) == -1)
		return (-1);
	return (0);
}
