/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:40:21 by junji             #+#    #+#             */
/*   Updated: 2022/07/06 17:58:11 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
//
//#include <stdio.h>
//#include <ctype.h>
//
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%d\n", ft_isdigit('0'));
//	printf("%d\n", ft_isdigit('9'));
//	printf("%d\n", ft_isdigit(1));
//	printf("%d\n", ft_isdigit(0));
//	printf(">>>Test<<<\n");
//	printf("%d\n", isdigit('0'));
//	printf("%d\n", isdigit('9'));
//	printf("%d\n", isdigit(1));
//	printf("%d\n", isdigit(0));
//}	
