/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:14:59 by junji             #+#    #+#             */
/*   Updated: 2022/05/25 00:33:41 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//int main(void)
//{
//	void *ptr;
//	void *ptr2;
////	void *ptr3;
////	void *ptr4;
//	printf(">>>Your<<<\n");
//	ptr2 = ft_calloc(8, 1);
//	strcpy(ptr2, "hello");
//	printf("%s\n", (char *)ptr2);
//
////	ptr4 = calloc(1, 1); //seg, ""->not seg
////	strcpy(ptr4, "hello");
////	printf("%s\n", (char *)ptr4);
//
//	printf(">>>Test<<<\n");
//	ptr = calloc(8, 1);
//	strcpy(ptr, "hello");
//	printf("%s\n", (char *)ptr);
//
////	ptr3 = calloc(1, 1); //seg, ""->not seg
////	strcpy(ptr3, "");
////	printf("%s\n", (char *)ptr3);
//}
