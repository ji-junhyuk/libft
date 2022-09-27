/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:33:40 by junji             #+#    #+#             */
/*   Updated: 2022/09/27 15:33:50 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "signal.h"

typedef struct s_sig_tool
{
	struct sigaction	zero_act;
	struct sigaction	one_act;
	int					count;
	pid_t				pid;
}						t_sig_tool;

#endif
