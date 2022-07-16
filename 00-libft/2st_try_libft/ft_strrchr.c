/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:53:37 by junji             #+#    #+#             */
/*   Updated: 2022/07/11 16:08:49 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		idx;
	char	*last_occurence;

	idx = 0;
	last_occurence = 0;
	while (*s)
	{
		if (*s == (char)c)
			last_occurence = ((char *)s);
		++s;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (last_occurence)
		return (last_occurence);
	return (0);
}
