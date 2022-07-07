/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:00:42 by junji             #+#    #+#             */
/*   Updated: 2022/05/22 18:01:42 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
//	printf("%d\n", ft_isascii(0));
//	printf("%d\n", ft_isascii(50));
//	printf("%d\n", ft_isascii(127));
//	printf("%d\n", ft_isascii(128));
//	printf("%d\n", ft_isascii(300));
//	printf(">>>Test<<<\n");
//	printf("%d\n", isascii(0));
//	printf("%d\n", isascii(50));
//	printf("%d\n", isascii(127));
//	printf("%d\n", isascii(128));
//	printf("%d\n", isascii(300));
//}
