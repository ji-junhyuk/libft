/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 00:11:27 by junji             #+#    #+#             */
/*   Updated: 2022/05/28 00:23:43 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
//
//void	fun(void *content)
//{
//	while (*(char *)content)
//		write(1, ((char *)content++), 1);
//	write(1, " ", 1);
//}
//
//int main(void)
//{
//	t_list *head;
//	
//	head = ft_lstnew("junto");
//	head->next = ft_lstnew("junhyuk");
//	head->next->next = ft_lstnew("ji-junhyuk");
//	ft_lstiter(head, fun); 
//}
