/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:00:11 by junji             #+#    #+#             */
/*   Updated: 2022/05/22 18:00:17 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%d\n", ft_isprint('~'));
//	printf("%d\n", ft_isprint(' '));
//	printf("%d\n", ft_isprint('0'));
//	printf("%d\n", ft_isprint(0));
//	printf("%d\n", ft_isprint('\n'));
//	printf("%d\n", ft_isprint('\t'));
//	printf(">>>Test<<<\n");
//	printf("%d\n", isprint('~'));
//	printf("%d\n", isprint(' '));
//	printf("%d\n", isprint('0'));
//	printf("%d\n", isprint(0));
//	printf("%d\n", isprint('\n'));
//	printf("%d\n", isprint('\t'));
//}
