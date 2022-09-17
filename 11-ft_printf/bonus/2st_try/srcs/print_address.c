/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:19 by junji             #+#    #+#             */
/*   Updated: 2022/08/02 10:42:35 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	print_address_hex(void *p, unsigned char *value, int idx, t_tool *tool)
{
	const char	*hex = "0123456789abcdef";

	if (!p)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		++tool->printed;
	}
	else
	{
		if (value[idx] < 16)
		{
			if (write_tool(tool, hex[*(value + idx--) % 16]) == -1)
				return (-1);
		}
		while (idx >= 0)
		{
			if (write_tool(tool, hex[*(value + idx) / 16]) == -1)
				return (-1);
			if (write_tool(tool, hex[*(value + idx--) % 16]) == -1)
				return (-1);
		}
	}
	return (0);
}

int	find_zero_num(unsigned char *value, int *idx)
{
	int	zero_num;

	zero_num = 0;
	*idx = sizeof(size_t) - 1;
	while (value[*idx] == 0)
	{
		--(*idx);
		zero_num += 2;
	}
	if (value[*idx] < 16)
		++zero_num;
	return (zero_num);
}

int	print_address(t_option *option, t_tool *tool, va_list *ap)
{
	unsigned char	*value;
	void			*p;
	int				idx;

	p = va_arg(*ap, unsigned char *);
	value = (unsigned char *)&p;
	if (!p)
		tool->len = 3;
	else
		tool->len = sizeof(size_t) * 2 + 2 - find_zero_num(value, &idx);
	option->width -= tool->len;
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (write(1, "0x", 2) == -1)
		return (-1);
	tool->printed += 2;
	if (print_address_hex(p, value, idx, tool) == -1)
		return (-1);
	if (print_width(tool, option) == -1)
		return (-1);
	return (0);
}
