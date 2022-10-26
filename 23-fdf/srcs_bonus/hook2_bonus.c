/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:57:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 16:10:46 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "define_bonus.h"

void	depth(int keycode, t_tool *tool)
{
	if (keycode == R)
		tool->modify_z += 0.05;
	else if (keycode == T)
		tool->modify_z -= 0.05;
}
