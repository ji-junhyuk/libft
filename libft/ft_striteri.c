/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:25:17 by junji             #+#    #+#             */
/*   Updated: 2022/05/26 19:22:16 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	len;
	unsigned int	idx;

	if (!s)
		return ;
	len = ft_strlen(s);
	idx = -1;
	while (++idx < len)
		f(idx, &s[idx]);
}
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//void func(unsigned int idx, char *c)
//{
//	*c = *c + idx;
//}
//
//int main()
//{
//	char	str[500] = "abcdefgh";
//	ft_striteri(str, func);
//	printf("%s\n", str);
//}
