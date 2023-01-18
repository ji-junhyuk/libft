/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_thread2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:37 by junji             #+#    #+#             */
/*   Updated: 2023/01/18 15:21:26 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_pthread_join(pthread_t thread, void **value_ptr)
{
	if (pthread_join(thread, value_ptr) != 0)
	{
		ft_putstr_fd("pthread_join() error", 2);
		return (1);
	}
	return (0);
}

int	_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) == 1)
	{
		ft_putstr_fd("pthread_mutex_destroy() error", 2);
		return (1);
	}
	return (0);
}

void	*_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("malloc() error", 2);
		return (NULL);
	}
	return (ptr);
}
