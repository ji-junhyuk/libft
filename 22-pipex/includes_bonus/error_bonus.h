/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:08:02 by junji             #+#    #+#             */
/*   Updated: 2022/10/12 08:18:19 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H
# include <stdio.h>

void	fork_error(void);
void	dup2_error(void);
void	open_error(void);
void	close_error(void);
void	pipe_error(void);
void	execve_error(void);
void	waitpid_error(void);
void	invalid_argument(void);

#endif
