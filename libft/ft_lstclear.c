/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 23:59:01 by junji             #+#    #+#             */
/*   Updated: 2022/05/28 00:11:10 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, del);
	}
	*lst = 0;
}
//
//void	del(void *content)
//{
//	free(content);
//}
//
//int main(void)
//{
//	t_list *head;
//	t_list *init_pos;
//	
//	head = ft_lstnew(ft_strdup("hello"));
//	head->next = ft_lstnew(ft_strdup("junto"));
//	head->next->next = ft_lstnew(ft_strdup("ji-junhyuk"));
//
//	init_pos = head;
//	while (head)
//	{
//		ft_putstr_fd((char *)(*head).content, 0);
//		ft_putstr_fd((char *)(head->content), 0);
//		write(1, "\n", 1);
//		head = head->next;
//	}
//	head = init_pos;
//	ft_lstclear(&head, del);
//	while (head)
//	{
//		ft_putstr_fd((char *)(*head).content, 0);
//		ft_putstr_fd((char *)(head->content), 0);
//		write(1, "\n", 1);
//		head = head->next;
//	}
//}
