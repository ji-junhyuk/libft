/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:59:51 by junji             #+#    #+#             */
/*   Updated: 2022/05/22 18:02:29 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}
//
//void ft_strcpy(char *s1, char *s2)
//{
//	while (*s2)
//		*s1++ = *s2++;
//	*s1 = '\0';
//}
//
//#include <stdio.h>
//#include <ctype.h>
//int main(void)
//{
//	char arr[5];
//
//	printf(">>>Your<<<\n");
//	ft_strcpy(arr, "AaBbCcDd");
//	for (int idx = 0; idx < 9; ++idx)
//		printf("%c\n", ft_tolower(arr[idx]));
//	printf(">>>Test<<<\n");
//	ft_strcpy(arr, "AaBbCcDd");
//	for (int idx = 0; idx < 9; ++idx)
//		printf("%c\n", tolower(arr[idx]));
//}
