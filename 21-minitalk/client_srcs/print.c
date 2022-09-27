/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:46:36 by junji             #+#    #+#             */
/*   Updated: 2022/09/27 12:46:56 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	receive(int signum)
{
	(void)signum;
	write(1, "client 1bit received...\n", 24);
}

void	put_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}
