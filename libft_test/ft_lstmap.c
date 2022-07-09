/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 00:24:14 by junji             #+#    #+#             */
/*   Updated: 2022/05/28 01:06:36 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*map_lst;

	map_lst = 0;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&map_lst, del);
			return (0);
		}
		ft_lstadd_back(&map_lst, new_node);
		lst = lst->next;
	}
	return (map_lst);
}
//
//void	fun(void *content)
//{
//	*(int *)content *= 2;
//}
//
//#include <stdio.h>
//int main(void)
//{
//	t_list *head;
//	int a = 1, b = 2, c = 3;
//	
//	head = ft_lstnew((void *)&a);
//	head->next = ft_lstnew((void *)&b);
//	head->next->next = ft_lstnew((void *)&c);
//	while (head)
//	{
//		fun(head->content);
//		printf("%d\n", *(int *)(head->content));
//		head = head->next;
//	}
//}
