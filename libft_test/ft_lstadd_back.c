/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:18:19 by junji             #+#    #+#             */
/*   Updated: 2022/05/28 01:06:09 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*init_pos;

	init_pos = *lst;
	if (!(*lst) && new)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	*lst = init_pos;
}
//
//int main(void)
//{
//	t_list *head;
//
//	head = ft_lstnew("junto");
//	head->next = ft_lstnew("junhyuk");
//	head->next->next = ft_lstnew("ji-junhyuk");
//	ft_lstadd_back(&head, ft_lstnew("hoho")); 
//
//
//	while (head)
//	{
//		ft_putstr_fd((char *)(*head).content, 0);
//		ft_putstr_fd((char *)(head->content), 0);
//		write(1, "\n", 1);
//		head = head->next;
//	}
//}
