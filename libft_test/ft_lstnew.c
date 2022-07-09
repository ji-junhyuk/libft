/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:41:10 by junji             #+#    #+#             */
/*   Updated: 2022/05/27 15:22:42 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*list;

	list = malloc(sizeof(t_list) * 1);
	if (!list)
		return (0);
	list->content = content;
	list->next = NULL;
	return (list);
}
//
//int main(void)
//{
//	t_list *head;
//	
//	head = ft_lstnew("junto");
//	head->next = ft_lstnew("junhyuk");
//	head->next->next = ft_lstnew("ji-junhyuk");
//	while (head)
//	{
//		ft_putstr_fd((char *)(*head).content, 0);
//		ft_putstr_fd((char *)(head->content), 0);
//		write(1, "\n", 1);
//		head = head->next;
//	}
//}
