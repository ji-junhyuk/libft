/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:41 by junji             #+#    #+#             */
/*   Updated: 2022/08/01 12:12:30 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/printf_bonus.h"

int	print_percent(t_option *option, t_tool *tool)
{
	(void) *option;
	if (write(1, "%", 1) == -1)
		return (-1);
	++tool->printed;
	return (0);
}
