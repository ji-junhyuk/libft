/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:16:13 by junji             #+#    #+#             */
/*   Updated: 2023/01/19 11:05:19 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo_character
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_philo_character;

typedef struct s_shared_data
{
	pthread_mutex_t		*m_fork;
	pthread_mutex_t		*m_print;
	bool				is_print_possible;
	pthread_mutex_t		m_is_all_eat;
	bool				is_all_eat;
	pthread_mutex_t		m_last_eat_time;
	long				last_eat_time;
	pthread_mutex_t		m_is_anyone_die;
	bool				is_anyone_die;
}	t_shared_data;

typedef struct s_philosophy
{
	int					identity;
	pthread_t			thread;
	struct timeval		start_time;
	t_philo_character	*philo_character;
	t_shared_data		*shared_data;
}	t_philosophy;

int		ft_atoi(const char *str);
void	ft_putstr_fd(const char *s, int fd);;
long	get_elapsed_milesecond(t_philosophy *philosophy, bool is_eat_status);
int		print_elapse_time(t_philosophy *philosophy,
			const char *status, bool is_eat_status);
int		msleep(int time);

bool	is_valid_input(const int argc, const char *argv[],
			t_philo_character *philo_char);

int		create_philosophers(t_philosophy **philosophy,
			t_philo_character *philo_character);

int		monitor_philosophers(t_philosophy *philosophy);

int		return_resource(t_philosophy *philosophy);

int		_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
			void *(*start_routine)(void *), void *arg);
int		_pthread_mutex_init(pthread_mutex_t *mutex,
			const pthread_mutexattr_t *attr);
int		_pthread_mutex_lock(pthread_mutex_t *mutex);
int		_pthread_mutex_unlock(pthread_mutex_t *mutex);

int		_pthread_join(pthread_t thread, void **value_ptr);
int		_pthread_mutex_destroy(pthread_mutex_t *mutex);
void	*dining_philosopher(void *philo);
void	*_malloc(size_t size);

int		is_thinking(t_philosophy *philosophy);
int		get_fork(t_philosophy *philosophy);
int		eat_spaghetti(t_philosophy *philosophy, int eat_count);
int		putdown_fork(t_philosophy *philosophy);
int		is_sleeping(t_philosophy *philosophy);

#endif
