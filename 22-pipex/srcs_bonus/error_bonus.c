/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:58:45 by junji             #+#    #+#             */
/*   Updated: 2022/10/06 15:30:18 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/error_bonus.h"
#include <stdlib.h>

void	dup2_error(void)
{
	perror("dup2");
	exit(1);
}

void	close_error(void)
{
	perror("dup2");
	exit(1);
}

void	pipe_error(void)
{
	perror("pipe");
	exit(1);
}

void	waitpid_error(void)
{
	perror("pipe");
	exit(1);
}
