/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:41 by junji             #+#    #+#             */
/*   Updated: 2022/09/27 15:25:37 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H
# include "signal.h"

typedef struct s_sig_tool
{
	struct sigaction	zero_act;
	struct sigaction	one_act;
	int					count;
	pid_t				pid;
}						t_sig_tool;

#endif
