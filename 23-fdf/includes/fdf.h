/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:19:01 by junji             #+#    #+#             */
/*   Updated: 2022/10/21 15:29:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_tool
{
	void				*mlx;
	void				*mlx_win;
	void				*image;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					horizental;
	char				*addr;
	int					vertical;
	int					*height;
	unsigned int		*color;
}						t_tool;

char	**ft_split(char const *str, char c);
int		count_word(const char *str, char c);
char	**free_arr(char **str);

#endif
