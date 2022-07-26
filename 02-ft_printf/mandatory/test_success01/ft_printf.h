/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:27:22 by junji             #+#    #+#             */
/*   Updated: 2022/07/26 16:01:49 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int		find_len(int num);
int		ft_putnbr_fd(long long n, int fd, int *printed);
int		print_sm_hex(va_list *ap, int *printed);
int		print_bg_hex(va_list *ap, int *printed);
int		print_per(va_list *ap, int *printed);
int		print_dec(va_list *ap, int *printed);
int		print_un_dec(va_list *ap, int *printed);
int		print_addr(unsigned char *, int *printed);
int		print_ptr(va_list *ap, int *printed);
int		ft_putstr(unsigned char *str, int *printed);
int		print_str(va_list *ap, int *printed);
int		print_char(va_list *ap, int *printed);
void	init_funcs(void *funcs[]);
int		ft_printf(const char *format, ...);
