/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:06:19 by junji             #+#    #+#             */
/*   Updated: 2022/10/21 14:32:07 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	invalid_input(void)
{
	write(2, "INVALID INPUT\n", 14);
	exit(1);
}

void	put_error(char *str)
{
	perror(str);
	exit(1);
}
