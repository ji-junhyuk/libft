/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:58:45 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 16:59:36 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdlib.h>
#include <unistd.h>

void	execve_error(void)
{
	perror("execve");
	exit(1);
}

void	waitpid_error(void)
{
	perror("waitpid");
	exit(1);
}

void	invalid_argument(void)
{
	write(2, "Invalid input\n", 14);
	exit(1);
}
