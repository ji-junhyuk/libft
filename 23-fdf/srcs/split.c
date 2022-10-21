/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:06:47 by junji             #+#    #+#             */
/*   Updated: 2022/10/21 14:06:48 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"

int	count_word(const char *str, char c)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		while (*str && *str == c)
			++str;
		if (*str && *str != c)
		{
			++cnt;
			while (*str && *str != c)
				++str;
		}
	}
	return (cnt);
}

static char	*ft_strlen_dup(const char **str, char c)
{
	int		word_len;
	int		cnt;
	char	*copy;

	word_len = 0;
	while (*(*str) && *(*str) != c)
	{
		++word_len;
		++*str;
	}
	*str -= word_len;
	copy = malloc(sizeof(char) * (word_len + 1));
	if (!copy)
		put_error("ft_strlen_dup malloc");
	cnt = 0;
	while (*(*str) && ++cnt <= word_len)
		*copy++ = *(*str)++;
	*copy = '\0';
	copy -= word_len;
	return (copy);
}

char	**free_arr(char **str)
{
	int	index;

	index = -1;
	while (str[++index])
		free(str[index]);
	free(str);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**copy;
	int		words;
	int		index;

	if (!str)
		return (0);
	words = count_word(str, c);
	copy = malloc(sizeof(char *) * (words + 1));
	if (!copy)
		put_error("ft_split malloc");
	index = -1;
	while (++index < words)
	{
		while (*str && *str == c)
			++str;
		copy[index] = ft_strlen_dup(&str, c);
	}
	copy[index] = 0;
	return (copy);
}
