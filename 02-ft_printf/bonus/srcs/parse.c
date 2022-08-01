/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:12 by junji             #+#    #+#             */
/*   Updated: 2022/08/01 15:55:50 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_precision(char **format, t_option *option)
{
	int	res;

	res = 0;
	if ((*(*format)) == '.')
	{
		if (option->precision < 0)
			option->precision = 0;
		option->flag |= PRECISION;
		++(*format);
		while (*(*format) && is_num(*(*format)))
		{
			res *= 10;
			res += (*(*format)) - '0';
			if (res >= 214748364 && (*format + 1
					&& (*(*format + 1) >= '7' && *(*format + 1) <= '9')))
				return (-1);
			++(*format);
		}
		option->precision = res;
	}
	return (0);
}

int	check_width(char **format, t_option *option)
{
	int	res;

	res = 0;
	while (*(*format) && is_num(*(*format)))
	{
		res *= 10;
		res += (*(*format)) - '0';
		if (res >= 214748364 && (*format + 1
				&& (*(*format + 1) >= '7' && *(*format + 1) <= '9')))
			return (-1);
		++(*format);
	}
	option->width = res;
	return (0);
}

void	check_flag(char **format, t_option *option)
{
	while (*(*format))
	{
		if (*(*format) == '-')
			option->flag |= FLAG_LEFT;
		else if (*(*format) == '0')
			option->flag |= FLAG_ZERO;
		else if (*(*format) == '#')
			option->flag |= FLAG_HASH;
		else if (*(*format) == ' ')
			option->flag |= FLAG_SPACE;
		else if (*(*format) == '+')
			option->flag |= FLAG_PLUS;
		else
			break ;
		++(*format);
	}
}
