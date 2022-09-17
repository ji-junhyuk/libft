/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:16:23 by junji             #+#    #+#             */
/*   Updated: 2022/07/26 15:52:58 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_len(int num)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		++len;
		num *= -1;
	}
	while (1)
	{
		++len;
		num /= 10;
		if (num == 0)
			return (len);
	}
}

int	ft_putnbr_fd(long long n, int fd, int *printed)
{
	long long	num;
	char		c;

	num = n;
	if (num < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		++(*printed);
		num *= -1;
	}
	if (num < 10)
	{
		c = num + '0';
		if (write(fd, &c, 1) == -1)
			return (-1);
		++(*printed);
	}	
	else
	{
		ft_putnbr_fd(num / 10, fd, printed);
		ft_putnbr_fd(num % 10, fd, printed);
	}
	return (*printed);
}

int	print_sm_hex(va_list *ap, int *printed)
{
	unsigned int			value;
	char					c[9];
	const char				*hex = "0123456789abcdef";
	int						idx;

	value = va_arg(*ap, unsigned int);
	idx = -1;
	while (++idx < 9)
		c[idx] = 0;
	idx = -1;
	while (1)
	{
		c[++idx] = hex[value % 16];
		value /= 16;
		if (!value)
			break ;
	}
	while (idx >= 0)
	{
		if (write(1, (c + idx--), 1) == -1)
			return (-1);
		++(*printed);
	}
	return (*printed);
}

int	print_bg_hex(va_list *ap, int *printed)
{
	const char		*hex = "0123456789ABCDEF";
	unsigned int	value;
	char			c[9];
	int				idx;

	idx = -1;
	while (++idx < 9)
		c[idx] = 0;
	value = va_arg(*ap, unsigned int);
	idx = -1;
	while (1)
	{
		c[++idx] = hex[value % 16];
		value /= 16;
		if (!value)
			break ;
	}
	while (idx >= 0)
	{
		if (write(1, (c + idx--), 1) == -1)
			return (-1);
		++(*printed);
	}
	return (*printed);
}

int	print_per(va_list *ap, int *printed)
{
	(void)ap;
	if (write(1, "%", 1) == -1)
		return (-1);
	return (++(*printed));
}

int	print_dec(va_list *ap, int *printed)
{
	int	value;

	value = va_arg(*ap, int);
	if (ft_putnbr_fd(value, STDOUT_FILENO, printed) == -1)
		return (-1);
	return (*printed);
}

int	print_un_dec(va_list *ap, int *printed)
{
	unsigned int	value;

	value = va_arg(*ap, unsigned int);
	if (ft_putnbr_fd(value, STDOUT_FILENO, printed) == -1)
		return (-1);
	return (*printed);
}

int	print_addr(void *ptr, int *printed)
{
	const char			*hex = "0123456789abcdef";
	unsigned long long	value;
	char				addr[16];
	int					cnt;

	value = (unsigned long long)ptr;
	if (write(1, "0x", 2) == -1)
		return (-1);
	*printed += 2;
	cnt = -1;
	while (++cnt <= 15)
	{
		addr[cnt] = hex[(value % 16)];
		value /= 16;
	}
	while (addr[--cnt] == '0')
		;
	while (cnt >= 0)
	{
		if (write(1, (addr + cnt--), 1) == -1)
			return (-1);
		++(*printed);
	}
	return (*printed);
}

int	print_ptr(va_list *ap, int *printed)
{
	void	*p;

	p = va_arg(*ap, void *);
	print_addr(p, printed);
	if (!p)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		++(*printed);
	}
	return (*printed);
}

int	ft_putstr(unsigned char *str, int *printed)
{
	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		*printed += 6;
	}
	while (str && *str)
	{
		if (write(1, str++, 1) == -1)
			return (-1);
		++(*printed);
	}
	return (*printed);
}

int	print_str(va_list *ap, int *printed)
{
	unsigned char	*value;

	value = va_arg(*ap, unsigned char *);
	if (ft_putstr(value, printed) == -1)
		return (-1);
	return (*printed);
}

int	print_char(va_list *ap, int *printed)
{
	unsigned char	c;

	c = va_arg(*ap, int);
	if (write(1, &c, 1) == -1)
		return (-1);
	return (++(*printed));
}

void	init_funcs(void *funcs[])
{
	int	idx;

	idx = -1;
	while (++idx < 256)
		funcs[idx] = 0;
	funcs['c'] = print_char;
	funcs['s'] = print_str;
	funcs['p'] = print_ptr;
	funcs['d'] = print_dec;
	funcs['i'] = print_dec;
	funcs['u'] = print_un_dec;
	funcs['x'] = print_sm_hex;
	funcs['X'] = print_bg_hex;
	funcs['%'] = print_per;
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	void		*funcs[256];
	int			(*func)(va_list *, int *);
	int			printed;

	printed = 0;
	init_funcs(funcs);
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
		{
			if (write(1, format++, 1) == -1)
				return (-1);
			++printed;
		}
		else
		{
			func = funcs[(int)(*++format)];
			if (!func || (func(&ap, &printed) == -1))
				return (-1);
			++format;
		}
	}
	return (printed);
}
