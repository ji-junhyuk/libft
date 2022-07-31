/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:45:46 by junji             #+#    #+#             */
/*   Updated: 2022/07/31 16:11:33 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define FLAG_LEFT			0b00000001
#define FLAG_ZERO			0b00000010
#define FLAG_HASH			0b00000100
#define FLAG_SPACE			0b00001000
#define FLAG_PLUS			0b00010000
#define PRECISION			0b00100000

typedef struct s_option
{
	int	flag;
	int	width;
	int	precision;
}	t_option;	

typedef struct s_tool
{
	int			c;
	int			precision_value_zero;
	int			sign;
	int			len;
	int			printed;
	void		*functions[256];
}	t_tool;

int	find_len(long long num)
{
	int	len;

	len = 0;
	while (1)
	{
		++len;
		num /= 10;
		if (num == 0)
			return (len);
	}
}

int	ft_putnbr_fd(int value, int fd, t_tool *tool)
{
	long	num;
	char	c;

	num = value;
	if (num < 10)
	{
		c = num + '0';
		if (write(fd, &c, 1) == -1)
			return (-1);
		++tool->printed;
	}	
	else
	{
		ft_putnbr_fd(num / 10, fd, tool);
		ft_putnbr_fd(num % 10, fd, tool);
	}
	return (0);
}

void	check_sign_un(t_option *option, t_tool *tool, unsigned int *value)
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

void	check_sign(t_option *option, t_tool *tool, int *value)
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

void	check_prec_value(t_tool *tool, t_option *option)
{
	tool->precision_value_zero = 1;
	++option->width;
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

int	print_decimal_2(t_option *option, t_tool *tool, int value)
{
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	while (tool->len < (option->precision)--)
		if (write(1, "0", 1) == -1)
			return (-1);
	if (!tool->precision_value_zero)
		if (ft_putnbr_fd(value, 1, tool) == -1)
			return (-1);
	while ((option->width)-- > 0)
		if (write(1, &tool->c, 1) == -1)
			return (-1);
	return (0);
}

int	print_decimal(t_option *option, t_tool *tool, va_list *ap)
{
	int		value;

	value = va_arg(*ap, int);
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
	check_sign(option, tool, &value);
	if (!(option->flag & FLAG_ZERO || option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (tool->sign)
		if (write(1, &tool->sign, 1) == -1)
			return (-1);
	if (print_decimal_2(option, tool, value) == -1)
		return (-1);
	return (0);
}

int	print_char(t_option *option, t_tool *tool, va_list *ap)
{
	int		value;

	(void)	*tool;
	value = va_arg(*ap, int);
	if (!(option->flag & FLAG_LEFT))
		while (--option->width > 0)
			if (write(1, " ", 1) == -1)
				return (-1);
	if (write(1, &value, 1) == -1)
		return (-1);
	while (--option->width > 0)
		if (write(1, " ", 1) == -1)
			return (-1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (6);
	while (*str)
	{
		++len;
		++str;
	}
	return (len);
}

int	print_str(t_option *option, t_tool *tool, va_list *ap)
{
	char	*str;

	str = va_arg(*ap, char *);
	if (!str)
		str = "(null)";
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
		while (option->width-- > 0)
			if (write(1, " ", 1) == -1)
				return (-1);
	while (option->precision-- > 0)
		if (write(1, str++, 1) == -1)
			return (-1);
	while (option->width-- > 0)
		if (write(1, " ", 1) == -1)
			return (-1);
	return (0);
}

int	ft_putnbr_fd_2(unsigned int num, int fd, t_tool *tool)
{
	char		c;

	if (num < 10)
	{
		c = num + '0';
		if (write(fd, &c, 1) == -1)
			return (-1);
		++tool->printed;
	}	
	else
	{
		ft_putnbr_fd_2(num / 10, fd, tool);
		ft_putnbr_fd_2(num % 10, fd, tool);
	}
	return (0);
}

int	print_un_decimal_2(t_option *option, t_tool *tool, unsigned int value)
{
	if (!(option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	while (tool->len < (option->precision)--)
		if (write(1, "0", 1) == -1)
			return (-1);
	if (!tool->precision_value_zero)
		if (ft_putnbr_fd_2(value, 1, tool) == 1)
			return (-1);
	while ((option->width)-- > 0)
		if (write(1, &tool->c, 1) == -1)
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
	check_sign_un(option, tool, &value);
	if (!(option->flag & FLAG_ZERO || option->flag & FLAG_LEFT))
		if (print_width(tool, option) == -1)
			return (-1);
	if (tool->sign)
		write(1, &tool->sign, 1);
	if (print_un_decimal_2(option, tool, value) == -1)
		return (-1);
	return (0);
}

int	print_address(t_option *option, t_tool *tool, va_list *ap)
{
//	long long			value;
//	unsigned char 		*p_value;
//
//	value = 
	return (0);
}

void	initializer(t_option *option, t_tool *tool)
{
	int	idx;

	option->flag = 0;
	option->width = -1;
	option->precision = -1;
	tool->precision_value_zero = 0;
	tool->printed = 0;
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
//	functions['x'] = print_11hex_small;
//	functions['X'] = print_hex_big;
//	functions['%'] = print_percent;
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

int	check_width(char **format, t_option *option)
{
	int	res;

	res = 0;
	while (*(*format) && is_num(*(*format)))
	{
		res *= 10;
		res += (*(*format)) - '0';
		if (res >= 214748364 && (*format + 1 && *(*format + 1) >= '7'))
			return (-1);
		++(*format);
	}
	option->width = res;
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
			if (res >= 214748364 && (*format + 1 && *(*format + 1) >= '7'))
				return (-1);
			++(*format);
		}
		option->precision = res;
	}
	return (0);
}

int	parse_print(char **format, t_option *option, t_tool *tool, va_list *ap)
{
	void	(*func)(t_option *, t_tool *, va_list *);

	check_flag(format, option);
	if (check_width(format, option) == -1)
		return (-1);
	if (check_precision(format, option) == -1)
		return (-1);
	func = tool->functions[(int)*(*format)];
	func(option, tool, ap);
	++(*(format));
	return (0);
}

int	ft_printf(char *format, ...)
{
	t_option	option;
	t_tool		tool;
	va_list		ap;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			initializer(&option, &tool);
			if (parse_print(&format, &option, &tool, &ap) == -1)
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
//int main(void)
//{
//	printf("%u", 4294967295u);
//	ft_printf("%u", 4294967295u);
//}
//
//int main(void)
//{
//	printf("%.3s|\n", (unsigned char *)NULL);
//	ft_printf("%.3s|\n", (unsigned char *)NULL);
//	printf("%s|\n", (unsigned char *)NULL);
//	ft_printf("%s|\n", (unsigned char *)NULL);
//	printf("%7s|\n", (char *)NULL);
//	ft_printf("%7s|\n", (char *)NULL);
//	printf("%7.2s|\n", (char *)NULL);
//	ft_printf("%7.2s|\n", (char *)NULL);
//	printf("%3s|\n", (char *)NULL);
//	ft_printf("%3s|\n", (char *)NULL);
//	printf("%.3s|\n", "junto");
//	ft_printf("%.3s|\n", "junto");
//	printf("%4.3s|\n", "junto");
//	ft_printf("%4.3s|\n", "junto");
//	printf("%5.2s|\n", "junto");
//	ft_printf("%5.2s|\n", "junto");
//	printf("%5.7s|\n", "junto");
//	ft_printf("%5.7s|\n", "junto");
//	printf("%-5.2s|\n", "junto");
//	ft_printf("%-5.2s|\n", "junto");
//	printf("%-5s|\n", "junto");
//	ft_printf("%-5s|\n", "junto");
//	printf("%-5.6s|\n", "junto");
//	ft_printf("%-5.6s|\n", "junto");
//}
