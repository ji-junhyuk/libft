/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:44:27 by junji             #+#    #+#             */
/*   Updated: 2022/10/21 14:45:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ')
		++str;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result *= 10;
		result += (*str - '0');
		++str;
	}
	return (sign * result);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (c - 'A' + 10);
}

unsigned int	convert_hex_to_int(const char *str)
{
	unsigned int	result;

	str += 2;
	result = 0;
	while (*str)
	{
		result *= 16;
		result += is_num(*str);
		++str;
	}
	return (result);
}
