/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:45:46 by junji             #+#    #+#             */
/*   Updated: 2022/07/28 15:45:51 by junji            ###   ########.fr       */
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
#define LONGGEST_ARGS		1
#define LONGGEST_WIDTH		2
#define LONGGEST_PRECISION	3

typedef struct t_option
{
	int	flag;
	int	width;
	int precision;
}	s_option;	

typedef struct t_tool
{
	int			longgest;
	int			printed;
	void		*functions[256];
}	s_tool;

//typedef enum t_enum
//{
//	LONGGEST_ARGS 		= 1,
//	LONGGEST_WIDTH 		= 2,
//	LONGGEST_PRECISION	= 3
//}	e_flag;


int	find_len(long long num)
{
	int	len;

	len = 0;
	if (num < 0)
		num *= -1;
	while (1)
	{
		++len;
		num /= 10;
		if (num == 0)
			return (len);
	}
}

void	check_len_flag(s_option *option, s_tool *tool, int len)
{
	int		max;

	max = 0;
	if (max < len)
		max = len;
	if (max < option->width)
		max = option->width;
	if (max < option->precision)
		max = option->precision;	
	if (max == len)
	{
		tool->longgest = LONGGEST_ARGS;
		return ;
	}
	if (max == option->precision)
	{
		tool->longgest = LONGGEST_PRECISION;
		return ;
	}
	if (max == option->width)
	{
		tool->longgest = LONGGEST_WIDTH;
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd, s_tool *tool)
{
	long long	num;
	char		c;

	num = n;
	if (num < 0)
		num *= -1;
	if (num < 10)
	{
		c = num + '0';
		write(fd, &c, 1);
		++tool->printed;
	}	
	else
	{
		ft_putnbr_fd(num / 10, fd, tool);
		ft_putnbr_fd(num % 10, fd, tool);
	}
}

int	printf_dec_args(s_option *option, s_tool *tool, int value)
{
	if (value < 0)
	{
		write(1, "-", 1);
		++tool->printed;
	}
	else
	{
		if (option->flag & FLAG_PLUS)
			write(1, "+", 1);
		else if (option->flag & FLAG_SPACE)
			write(1, " ", 1);
		++tool->printed;
	}
	ft_putnbr_fd(value, 1, tool);
	return (0);
}

int	printf_dec_width(s_option *option, s_tool *tool, int value, int len)
{
	if (value < 0)
	{
		write(1, "-", 1);
		++tool->printed;
		++len;
	}
	if (option->flag & FLAG_PLUS)
	{
		write(1, "+", 1);
		++len;
		++tool->printed;
	}
	else if (option->flag & FLAG_SPACE)
	{
		if (value > 0)
			write(1, " ", 1);
		++len;
		++tool->printed;
	}
	if (option->flag & FLAG_LEFT)
	{

	}
	else
	{

	}
	while (option->width > len)
	return (0);
}
int	printf_dec_prec(s_option *option, s_tool *tool, int value, int len)
{
	if (value < 0)
	{
		write(1, "-", 1);
		++tool->printed;
	}
	if (option->flag & FLAG_PLUS)
		write(1, "+", 1);
	else if (option->flag & FLAG_SPACE)
	{
		if (value > 0)
			write(1, " ", 1);
	}
	++tool->printed;
	while (option->precision > len) // 8 3
	{
		write(1, "0", 1);
		++len;
	}
	ft_putnbr_fd(value, 1, tool);
	return (0);
}

int	print_decimal(s_option *option, s_tool *tool, va_list *ap)
{
	int		value;
	int		len;

	value = va_arg(*ap, int);
	len = find_len(value);
	check_len_flag(option, tool, len);
	if (tool->longgest == LONGGEST_ARGS)
	{
		if (printf_dec_args(option, tool, value) == -1)
			return (-1);
	}
	else if (tool->longgest == LONGGEST_PRECISION)
	{
		if (printf_dec_prec(option, tool, value, len) == -1)
			return (-1);
	}
	else
	{
		if (printf_dec_width(option, tool, value, len) == -1)
			return (-1);
	}
	return (0);
}

void	initializer(s_option *option, s_tool *tool)
{
	int	idx;

	option->flag = 0;
	option->width = 0;
	option->precision = 0;
	tool->printed = 0;
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

void	check_width(char **format, s_option *option)
{
	int	res;

	res = 0;
	while (*(*format) && is_num(*(*format)))
	{
		res *= 10;
		res += (*(*format)) - '0';
		if (res >= 214748364 && (*format + 1 && *(*format + 1)  >= '7'))
		{
			option->width = -1;
			return ;
		}
		++(*format);
	}
	option->width = res;
}

void	check_precision(char **format, s_option *option)
{
	int	res;

	res= 0;
	if ((*(*format)) == '.')
	{
		option->flag |= PRECISION;
		++(*format);
		while (*(*format) && is_num(*(*format)))
		{
			res *= 10;
			res += (*(*format)) - '0';
			if (res >= 214748364 && (*format + 1 && *(*format + 1) >= '7'))
			{
				option->width = -1;
				return ;
			}
			++(*format);
		}
		option->precision = res;
	}
}

//int	print(char *format, s_option *option, void *functions[], va_list *ap)
//{
//	printf("print, format: %c\n", *format);
//	return (0);
//}

//void	check_print_len(s_option *option, s_tool *tool)
//{
//	if (tool->len < option->width)
//		tool->len = option->width;
//	if (tool->len < option->precision)
//		tool->len = option->width;
//}

int	parse_print(char **format, s_option *option, s_tool *tool, va_list *ap)
{
	void (*func)(s_option *, s_tool *, va_list *);

	check_flag(format, option);
	check_width(format, option);
	check_precision(format, option);
	if (option->width == -1 || option->precision == -1)
		return (-1);
//	check_print_len(option, tool);
	func = tool->functions[(int)*(*format)];
	// cf. %d : 가변인자 크기가 INTMAX보다 같거나 비슷하면 Format specifies type 'int' but the argument has type 'long'
    // 반드시 널에 도달한다. %u, %d등 type이 없으면 Incomplete format specifier 컴파일 에러가 발생한다.
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

			// 이중포인터로 넘길까, -> 좀 낯섬
			// 아니면 그냥 포인터로 넘길까? -> 함수포인터 만날 떄까지 길이를 세줘야한다. 그냥 이중포인터로.
			// 다음 함수에서 체크하면서 넘겨주자.
		}
		else
		{
			write(1, format++, 1);
			++tool.printed;
		}
	}
	return (tool.printed);
}

int main(void)
{
//	printf("%d\n", ft_printf("%2147483646"));
//	ft_printf("%2147483647d");

//	printf("===========================\n");
//	ft_printf("===========================\n");

	ft_printf("ft[% -05.13d]\n", -123);
	printf("pf[% 05.13d]\n", -123);

	ft_printf("ft[%03.11d]\n", -123);
	printf("pf[%03.11d]\n", -123);

	ft_printf("ft[%03.3d]\n", -123);
	printf("pf[%03.3d]\n", -123);
//	printf("%+2.2d\n", 123);
//	ft_printf("%+2.2d\n", 123);
//	printf("%0 2.2d\n", -123);
//	ft_printf("%0 2.2d\n", -123);
//	printf("%0 2.2d\n", 123);
//	ft_printf("%0 2.2d\n", 123);
//
//	printf("%02.2d\n", 123);
//	ft_printf("%02.2d\n", 123);
//	printf("%2.2d\n", 123);
//	ft_printf("%2.2d\n", 123);
//	printf("[% 010.07d]\n", 123); //[ 0000123] 
//	ft_printf("[% 010.07d]\n", 123); //[  000123] 
//	printf("[% 05.04d]\n", 123); //[ 0123]
//	ft_printf("[% 05.04d]\n", 123); //[ 0123]

//	printf("[% 06.3d]\n", 123); //   [ 00123] : 정밀도가 있으면 flag 0을 무시한다.
//	ft_printf("[% 06.3d]\n", 123); //   [ 00123] : 정밀도가 있으면 flag 0을 무시한다.
//	printf("[% 06d]\n", 123); //   [ 00123]
//	ft_printf("[% 06d]\n", 123); //   [ 00123]
//	printf("[% 05d]\n", 123); //   [ 0123]
//	ft_printf("[% 05d]\n", 123); //   [ 0123]

//	ft_printf("[% 5d]\n", 123);
//	printf("[% 5d]\n", 123);
}
