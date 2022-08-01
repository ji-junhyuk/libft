/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:59 by junji             #+#    #+#             */
/*   Updated: 2022/08/01 18:12:26 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/printf_bonus.h"

int	write_tool(t_tool *tool, char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	++tool->printed;
	return (0);
}

int	print_width(t_tool *tool, t_option *option)
{
	while ((option->width)-- > 0)
	{
		if (write(1, &tool->c, 1) == -1)
			return (-1);
		++tool->printed;
	}
	return (0);
}

int	parse_print(char **format, t_option *option, t_tool *tool, va_list *ap)
{
	int	(*func)(t_option *, t_tool *, va_list *);

	check_flag(format, option);
	if (check_width(format, option) == -1)
		return (-1);
	if (check_precision(format, option) == -1)
		return (-1);

	if ((tool->functions[(int)*(*format)])option, tool, ap))
		return (-1);
	++(*(format));
	return (0);
}

void	initializer(t_option *option, t_tool *tool)
{
	int	idx;

	option->flag = 0;
	option->width = -1;
	option->precision = -1;
	tool->precision_value_zero = 0;
	tool->len = 0;
	tool->c = ' ';
	tool->sign = 0;
	idx = -1;
	while (++idx < 256)
		tool->functions[idx] = 0;
	tool->functions['c'] = print_char;
	tool->functions['s'] = print_str;
	tool->functions['p'] = print_address;
	tool->functions['d'] = print_decimal;
	tool->functions['i'] = print_decimal;
	tool->functions['u'] = print_un_decimal;
	tool->functions['x'] = print_hex_small;
	tool->functions['X'] = print_hex_big;
	tool->functions['%'] = print_percent;
}

int	ft_printf(const char *format, ...)
{
	t_option	option;
	t_tool		tool;
	va_list		ap;

	va_start(ap, format);
	tool.printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			initializer(&option, &tool);
			if (parse_print((char **)&format, &option, &tool, &ap) == -1)
				return (-1);
		}
		else
		{
			if (write(1, format++, 1) == -1)
				return (-1);
			++tool.printed;
		}
	}
	return (tool.printed);
}
