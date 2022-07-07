/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:01:28 by junji             #+#    #+#             */
/*   Updated: 2022/05/27 22:10:13 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}
//
//#include <stdio.h>
//int main(void)
//{
//	t_list *head;
//	
//	head = ft_lstnew("junto");
//	head->next = ft_lstnew("junhyuk");
//	head->next->next = ft_lstnew("ji-junhyuk");
//	printf("listsize: %d\n", ft_lstsize(head));
//}
