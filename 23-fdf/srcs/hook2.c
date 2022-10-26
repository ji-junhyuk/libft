/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:57:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 15:59:03 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "define.h"

void	depth(int keycode, t_tool *tool)
{
	if (keycode == R)
		tool->modify_z += 0.05;
	else if (keycode == T)
		tool->modify_z -= 0.05;
}
