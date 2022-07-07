/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:10:40 by junji             #+#    #+#             */
/*   Updated: 2022/05/27 22:18:00 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}
//
//int main(void)
//{
//	t_list *head;
//	t_list *last;
//	
//	head = ft_lstnew("junto");
//	head->next = ft_lstnew("junhyuk");
//	head->next->next = ft_lstnew("ji-junhyuk");
//
//	last = ft_lstlast(head);
//	ft_putstr_fd((char *)(*last).content, 0);
//	ft_putstr_fd((char *)(last->content), 0);
//}
