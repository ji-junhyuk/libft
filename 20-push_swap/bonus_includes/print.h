/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:05:08 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:05:27 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H
# include <unistd.h>
# include <stdlib.h>

# define ERROR_MESSAGE "Error\n"

size_t	ft_strlen(const char *s);
void	put_error(char *str);

#endif
