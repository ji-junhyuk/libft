/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 23:39:48 by junji             #+#    #+#             */
/*   Updated: 2022/05/27 23:58:28 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
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
//
//	head = ft_lstnew(ft_strdup("hello~!"));
//	ft_putstr_fd((char *)(head->content), 0);
//	ft_lstdelone(head, del);
//	system("leaks a.out");
//}
