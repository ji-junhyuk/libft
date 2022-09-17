/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:35 by junji             #+#    #+#             */
/*   Updated: 2022/08/02 10:27:52 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/printf_bonus.h"

int	print_hex_big_2(t_option *option, t_tool *tool, int value)
{
	if (!(option->flag & FLAG_ZERO || option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (option->flag & FLAG_HASH && value != 0)
	{
		if (write(1, "0X", 2) == -1)
			return (-1);
		tool->printed += 2;
	}
	if (tool->sign)
		if (write_tool(tool, tool->sign) == -1)
			return (-1);
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	while (tool->len < (option->precision)--)
		if (write_tool(tool, '0') == -1)
			return (-1);
	if (!tool->precision_value_zero)
		if (ft_puthex_fd_2(value, 1, tool) == -1)
			return (-1);
	if (print_width(tool, option) == -1)
		return (-1);
	return (0);
}

int	print_hex_big(t_option *option, t_tool *tool, va_list *ap)
{
	unsigned int	value;

	value = va_arg(*ap, unsigned int);
	tool->len = find_len_hex(value);
	if (option->precision == 0 && value == 0)
		check_prec_value(tool, option);
	if (option->flag & FLAG_LEFT)
		option->flag &= ~FLAG_ZERO;
	if (option->precision != -1)
		option->flag &= ~FLAG_ZERO;
	if (option->flag & FLAG_ZERO)
		tool->c = '0';
	if (option->precision < tool->len)
		option->precision = tool->len;
	option->width -= option->precision;
	if (option->flag & FLAG_HASH && value != 0)
		option->width -= 2;
	if (print_hex_big_2(option, tool, value) == -1)
		return (-1);
	return (0);
}

int	print_hex_small_2(t_option *option, t_tool *tool, int value)
{
	if (!(option->flag & FLAG_ZERO || option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (option->flag & FLAG_HASH && value != 0)
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		tool->printed += 2;
	}
	if (tool->sign)
		if (write_tool(tool, tool->sign) == -1)
			return (-1);
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	while (tool->len < (option->precision)--)
		if (write_tool(tool, '0') == -1)
			return (-1);
	if (!tool->precision_value_zero)
		if (ft_puthex_fd(value, 1, tool) == -1)
			return (-1);
	while ((option->width)-- > 0)
		if (write_tool(tool, tool->c) == -1)
			return (-1);
	return (0);
}

int	print_hex_small(t_option *option, t_tool *tool, va_list *ap)
{
	unsigned int	value;

	value = va_arg(*ap, unsigned int);
	tool->len = find_len_hex(value);
	if (option->precision == 0 && value == 0)
		check_prec_value(tool, option);
	if (option->flag & FLAG_LEFT)
		option->flag &= ~FLAG_ZERO;
	if (option->precision != -1)
		option->flag &= ~FLAG_ZERO;
	if (option->flag & FLAG_ZERO)
		tool->c = '0';
	if (option->precision < tool->len)
		option->precision = tool->len;
	option->width -= option->precision;
	if (option->flag & FLAG_HASH && value != 0)
		option->width -= 2;
	if (print_hex_small_2(option, tool, value) == -1)
		return (-1);
	return (0);
}
