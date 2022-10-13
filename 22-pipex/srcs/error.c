/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:58:45 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 16:59:29 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdlib.h>
#include <unistd.h>

void	fork_error(void)
{
	perror("fork");
	exit(1);
}

void	dup2_error(void)
{
	perror("dup2");
	exit(1);
}

void	open_error(void)
{
	perror("open");
	exit(1);
}

void	close_error(void)
{
	perror("close");
	exit(1);
}

void	pipe_error(void)
{
	perror("pipe");
	exit(1);
}
