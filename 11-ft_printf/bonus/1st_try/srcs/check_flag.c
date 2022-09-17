/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:00 by junji             #+#    #+#             */
/*   Updated: 2022/08/01 14:40:17 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	check_prec_value(t_tool *tool, t_option *option)
{
	tool->precision_value_zero = 1;
	++option->width;
}

void	check_un_sign(t_option *option, t_tool *tool)
{
	if (option->flag & FLAG_PLUS)
	{
		tool->sign = '+';
		--option->width;
	}
	else if (option->flag & FLAG_SPACE)
	{
		tool->sign = ' ';
		--option->width;
	}
}

void	check_sign(t_option *option, t_tool *tool, long *value)
{
	if (*value < 0)
	{
		tool->sign = '-';
		*value *= -1;
		--option->width;
	}
	else if (option->flag & FLAG_PLUS)
	{
		tool->sign = '+';
		--option->width;
	}
	else if (option->flag & FLAG_SPACE)
	{
		tool->sign = ' ';
		--option->width;
	}
}
