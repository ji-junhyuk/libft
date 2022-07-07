/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:51:51 by junji             #+#    #+#             */
/*   Updated: 2022/05/27 15:22:26 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
//
//int main(void)
//{
//	t_list *head;
//
//	head = ft_lstnew("junto");
//	head->next = ft_lstnew("junhyuk");
//	head->next->next->next = ft_lstnew("ji-junhyuk");
//	ft_lstadd_front(&head, ft_lstnew("hoho")); 
//
////	head = ft_lstnew("junto");
////	head->next = ft_lstnew("junhyuk");
////	ft_lstadd_front(&head, ft_lstnew("haha")); 
////	head->next->next->next = ft_lstnew("ji-junhyuk");
////	ft_lstadd_front(&head, ft_lstnew("hoho")); 
//
//	while (head)
//	{
//		ft_putstr_fd((char *)(*head).content, 0);
//		ft_putstr_fd((char *)(head->content), 0);
//		write(1, "\n", 1);
//		head = head->next;
//	}
//}
