/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijunhyuk <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:15:50 by jijunhyuk         #+#    #+#             */
/*   Updated: 2022/08/01 15:46:22 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_BONUS_H
# define PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>

# define FLAG_LEFT			0b00000001
# define FLAG_ZERO			0b00000010
# define FLAG_HASH			0b00000100
# define FLAG_SPACE			0b00001000
# define FLAG_PLUS			0b00010000
# define PRECISION			0b00100000

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

int		write_tool(t_tool *tool, char c);
int		print_width(t_tool *tool, t_option *option);
int		parse_print(char **format, t_option *option, t_tool *tool, va_list *ap);
void	initializer(t_option *option, t_tool *tool);
int		ft_printf(const char *format, ...);

int		ft_puthex_fd(unsigned int value, int fd, t_tool *tool);
int		ft_puthex_fd_2(unsigned int value, int fd, t_tool *tool);
int		ft_putnbr_fd(long num, int fd, t_tool *tool);
int		find_len(long num);
int		find_len_hex(long num);

void	check_prec_value(t_tool *tool, t_option *option);
void	check_un_sign(t_option *option, t_tool *tool);
void	check_sign(t_option *option, t_tool *tool, long *value);

int		is_num(char c);
int		is_alpha(char c);
int		check_precision(char **format, t_option *option);
int		check_width(char **format, t_option *option);
void	check_flag(char **format, t_option *option);

int		print_percent(t_option *option, t_tool *tool);

int		print_hex_small_2(t_option *option, t_tool *tool, int value);
int		print_hex_small(t_option *option, t_tool *tool, va_list *ap);
int		print_hex_big_2(t_option *option, t_tool *tool, int value);
int		print_hex_big(t_option *option, t_tool *tool, va_list *ap);

int		print_address_hex(void *p, unsigned char *value, int idx, t_tool *tool);
int		find_zero_num(unsigned char *value, int *idx);
int		print_address(t_option *option, t_tool *tool, va_list *ap);

int		print_un_decimal_2(t_option *option, t_tool *tool, unsigned int value);
int		print_un_decimal(t_option *option, t_tool *tool, va_list *ap);

int		ft_strlen(unsigned char *str);
int		print_str2(t_option *option, t_tool *tool, unsigned char *str);
int		print_str(t_option *option, t_tool *tool, va_list *ap);

int		print_char(t_option *option, t_tool *tool, va_list *ap);

int		print_decimal_2(t_option *option, t_tool *tool, long value);
int		print_decimal(t_option *option, t_tool *tool, va_list *ap);

#endif
