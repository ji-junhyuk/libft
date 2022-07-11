/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:38:02 by junji             #+#    #+#             */
/*   Updated: 2022/07/11 15:48:38 by junji            ###   ########.fr       */
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
	*lst = ft_lstlast(*lst);
	(*lst)->next = new;
	*lst = init_pos;
}
