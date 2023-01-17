/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_thread1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:14:57 by junji             #+#    #+#             */
/*   Updated: 2023/01/17 14:21:17 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine)(void *), void *arg)
{
	if (pthread_create(thread, attr, start_routine, arg) != 0)
	{
		ft_putstr_fd("pthread_create() error", 2);
		return (1);
	}
	return (0);
}

int	_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
	if (pthread_mutex_init(mutex, attr) != 0)
	{
		ft_putstr_fd("pthread_mutex_init() error", 2);
		return (1);
	}
	return (0);
}

int	_pthread_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		ft_putstr_fd("pthread_mutex_lock(), error", 2);
		return (1);
	}
	return (0);
}

int	_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		ft_putstr_fd("pthread_mutex_unlock(), error", 2);
		return (1);
	}
	return (0);
}
