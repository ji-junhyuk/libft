/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:00:32 by junji             #+#    #+#             */
/*   Updated: 2022/05/22 18:01:56 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
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
//	ft_strcpy(arr, "abcd");
//	for (int idx = 0; idx < 5; ++idx)
//		printf("%c\n", ft_toupper(arr[idx]));
//	printf(">>>Test<<<\n");
//	ft_strcpy(arr, "abcd");
//	for (int idx = 0; idx < 5; ++idx)
//		printf("%c\n", toupper(arr[idx]));
//}
