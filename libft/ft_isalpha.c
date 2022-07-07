/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:40:09 by junji             #+#    #+#             */
/*   Updated: 2022/07/04 16:40:13 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
//
//#include <stdio.h>
//#include <ctype.h>
//int main(void)
//{
//	printf("==>Your<==\n");
//	printf("%d\n", ft_isalpha(30));
//	printf("%d\n", ft_isalpha(40));
//	printf("%d\n", ft_isalpha(50));
//	printf("%d\n", ft_isalpha(60));
//	printf("%d\n", ft_isalpha(70));
//	printf("%d\n", ft_isalpha(80));
//	printf("%d\n", ft_isalpha(90));
//	printf("==>Ans<==\n");
//	printf("%d\n", isalpha(30));
//	printf("%d\n", isalpha(40));
//	printf("%d\n", isalpha(50));
//	printf("%d\n", isalpha(60));
//	printf("%d\n", isalpha(70));
//	printf("%d\n", isalpha(80));
//	printf("%d\n", isalpha(90));
//	return 0;
//}
