/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:45:46 by junji             #+#    #+#             */
/*   Updated: 2022/07/31 12:49:42 by jijunhyuk        ###   ########.fr       */
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

typedef struct t_option
{
	int	flag;
	int	width;
	int precision;
}	s_option;	

typedef struct t_tool
{
	int			c;
	int			sign;
	int			len;
	int			printed;
	void		*functions[256];
}	s_tool;

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

int	ft_putnbr_fd(int value, int fd, s_tool *tool)
{
	long long	num;
	char		c;

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

void	check_sign(s_option *option, s_tool *tool, int *value)
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

int	print_decimal(s_option *option, s_tool *tool, va_list *ap)
{
	int		value;

	value = va_arg(*ap, int);
	tool->len = find_len(value);

	int wow = 0;
	if (option->precision == 0 && value == 0)
	{
		wow = 1;
		++option->width;
	}
	if (option->precision < tool->len)
		option->precision = tool->len;
	option->width -= option->precision;
	if (option->flag & FLAG_LEFT)
		option->flag &= ~FLAG_ZERO;
	else if (option->flag & PRECISION) 
		option->flag &= ~FLAG_ZERO;
	if (option->flag & FLAG_ZERO)
		tool->c = '0';
	check_sign(option, tool, &value);
	if (!(option->flag & FLAG_ZERO || option->flag & FLAG_LEFT))
	{
		while (option->width-- > 0)
		{
			if (write(1, &tool->c, 1) == -1)
				return (-1);
			++tool->printed;
		}
	}
	if (tool->sign)
		write(1, &tool->sign, 1);
	if (!(option->flag & FLAG_LEFT))
	{
		while (option->width-- > 0)
		{
			if (write(1, &tool->c, 1) == -1)
				return (-1);
			++tool->printed;
		}
	}
	while (tool->len < (option->precision)--)
		if (write(1, "0", 1) == -1)
			return (-1);
	if (!wow)
		if (ft_putnbr_fd(value, 1, tool) == -1)
			return (-1);
	while ((option->width)-- > 0)
		if (write(1, &tool->c, 1) == -1)
			return (-1);
	return (0);
}

void	initializer(s_option *option, s_tool *tool)
{
	int	idx;

	option->flag = 0;
	option->width = -1;
	option->precision = -1;
	tool->printed = 0;
	tool->len = 0;
	tool->c = ' ';
	tool->sign = 0;
	idx = -1;
	while (++idx < 256)
		tool->functions[idx] = 0;
//	functions['c'] = print_char;
//	functions['s'] = print_str;
//	functions['p'] = print_address;
	tool->functions['d'] = print_decimal;
//	functions['i'] = print_decimal;
//	functions['u'] = print_un_decimal;
//	functions['x'] = print_11hex_small;
//	functions['X'] = print_hex_big;
//	functions['%'] = print_percent;
	// 적합하지 않은 인자에 대해선 컴파일 에러가 난다. 
	// ex) printf("%v", 123) // Invalid conversion specifier 'v'
}

void	check_flag(char **format, s_option *option)
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

int is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_width(char **format, s_option *option)
{
	int	res;

	res = 0;
	while (*(*format) && is_num(*(*format)))
	{
		res *= 10;
		res += (*(*format)) - '0';
		if (res >= 214748364 && (*format + 1 && *(*format + 1)  >= '7'))
			return (-1);
		++(*format);
	}
	option->width = res;
	return (0);
}

int	check_precision(char **format, s_option *option)
{
	int	res;

	res= 0;
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

int	parse_print(char **format, s_option *option, s_tool *tool, va_list *ap)
{
	void (*func)(s_option *, s_tool *, va_list *);

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


int ft_printf(char *format, ...)
{
	s_option	option;
	s_tool		tool;

	va_list ap;
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
//	printf("%5.0d|\n", 0);
//	ft_printf("%5.0d|\n", 0);
//}
//int main(void)
//{
//	printf("pf[%0+7d]\n", 123); //[-0000000789]
//	ft_printf("ft[%0+7d]\n", 123); //[-0000000789]
//	printf("pf[%+07d]\n", 123); //[-0000000789]
//	ft_printf("ft[%+07d]\n", 123); //[-0000000789]

//	printf("pf[%0+7d]\n", 123); //[-0000000789]
//	ft_printf("ft[%0+7d]\n", 123); //[-0000000789]
//	printf("pf[%0 6d]\n", 456); //[-0000000789]
//	ft_printf("ft[%0 6d]\n", 456); //[-0000000789]
//	printf("pf[% 07d]\n", 789); //[-0000000789]
//	ft_printf("ft[% 07d]\n", 789); //[-0000000789]
//	printf("pf[%+07d]\n", 789); //[-0000000789]
//	ft_printf("pf[%+07d]\n", 789); //[-0000000789]
								
//	ft_printf("ft[%+07d]\n", 789); //[-0000000789]
//	printf("pf[%+07d]\n", 789); //[-0000000789]
//	ft_printf("ft[%+07d]\n", 789); //[-0000000789]
//	ft_printf("[%+10d]]\n", 789); //[-0000000789]
//	printf("[%+10d]]\n", 789); //[-0000000789]
// ========================================== 
//	ft_printf("[%+10d]]\n", -789); //[-0000000789]
//	printf("[%+10d]]\n", -789); //[-0000000789]
//	printf("pf[%0 6.8d]\n", -789); //[-0000000789]
//	ft_printf("pf[%0 6.8d]\n", -789); //[-0000000789]
//	printf("pf[%0 6.5d]\n", -789); //[-0000000789]
//	ft_printf("ft[%0 6.5d]\n", -789); //[-0000000789]
//	printf("pf[%0 6.5d]\n", 789); //[-0000000789]
//	ft_printf("ft[%0 6.5d]\n", 789); //[-0000000789]
//
//
//=========================================
//	printf("pf[%+7.2d]\n", 789); //[  +0789] 
//	ft_printf("ft[%+7.2d]\n", 789); //[  +0789]
//	printf("pf[%+7.4d]\n", 789); //[  +0789]
//	ft_printf("ft[%+7.4d]\n", 789); //[  +0789]
//	printf("pf[%-6.4d]\n", -789); //[  +0789]
//	ft_printf("pf[%-6.4d]\n", -789); //[  +0789]
//	printf("pf[%+-6.4d]\n", -789); //[  +0789]
//	printf("pf[%+-6.4d]\n", -789); //[  +0789]
//	printf("pf[%-10.4d]\n", 789); //[  +0789]
//	ft_printf("ft[%-10.4d]\n", 789); //[  +0789]
//}
//int main(void)
//{
//	printf("%03d|\n", 123);
//	ft_printf("%03d|\n", 123);
//	printf("%7d|\n", -14);
//	ft_printf("%7d|\n", -14);
//	printf("%05d|\n", 123);
//	ft_printf("%05d|\n", 123);
//
//	f_printf("%-5d|\n", 123);
//	ft_printf("%-+5d|\n", 123);
//	ft_printf("%- 5d|\n", 123);
//	ft_printf("%05d|\n", 123);
//	ft_printf("%0+5d|\n", 123);
//	ft_printf("%0 5d|\n", 123);
//
//	printf("%05d|\n", 123);
//	printf("%0+5d|\n", 123);
//	printf("%0 5d|\n", 123);
//
//	printf("%-5d|\n", 123);
//	printf("%-+5d|\n", 123);
//	printf("%- 5d|\n", 123);
//
//	printf("%-7d|\n", -14);
//	ft_printf("%-7d|\n", -14);
//	printf("%-5d|\n", 12345);
//	ft_printf("%-5d|\n", 12345);
//}
//	printf("%-7d|\n", 123);
//	ft_printf("%-7d|\n", 123);
//	ft_printf("%d\n", 17);
//	printf("%d\n", 17);
//	ft_printf("ft[%7d]\n", 123);
//	printf("pf[%7d]\n", 123);
//	printf("%03d\n", 123);
//	ft_printf("%03d\n", 123);
//	ft_printf("[%010.5d]\n", -123);
//	printf("[%010.5d]\n", -123);
//
//	ft_printf("%0.d\n", 0);
//	printf("%d", 0);
//	ft_printf("%d", 0);
//	printf("%d", 0);
//	ft_printf("%.3d\n", 000);
//	printf("%.3d\n", 0);
//	ft_printf("%.3d\n", 0);
//	printf("%8.5d\n", 0);
//	ft_printf("%8.5d\n", 0);
//	printf("%5.0d\n", 0);
//	ft_printf("%5.0d\n", 0);
//	printf("%-5.0d\n", 0);
//int main(void)
//{
//	printf("%d\n", 0);
//	ft_printf("%d\n", 0);
//	printf("%5.0d|\n", 0);
//	ft_printf("%5.0d|\n", 0);
// ========================
//	printf("%-7d|\n", 33);
//	ft_printf("%-7d|\n", 33);
//	printf("%.0d|\n", 0);
//	ft_printf("%.0d|\n", 0);
//	printf("%.d|\n", 0);
//	ft_printf("%.d|\n", 0);

//}
