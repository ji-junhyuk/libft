/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:43:32 by junji             #+#    #+#             */
/*   Updated: 2023/01/17 14:06:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

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

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ')
		++str;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str && ('0' <= *str && *str <= '9'))
	{
		result *= 10;
		result += (*str - '0');
		++str;
	}
	return (sign * result);
}

bool	is_valid_number(const int argc, const char *argv[],
		t_philo_character *philo_char)
{
	philo_char->number_of_philosophers = ft_atoi(argv[1]);
	philo_char->time_to_die = ft_atoi(argv[2]);
	philo_char->time_to_eat = ft_atoi(argv[3]);
	philo_char->time_to_sleep = ft_atoi(argv[4]);
	philo_char->must_eat = 0x7fffffff;
	if (philo_char->number_of_philosophers <= 0)
		return (false);
	if (philo_char->time_to_die < 0 || philo_char->time_to_eat < 0
		|| philo_char->time_to_sleep < 0)
		return (false);
	if (argc == 6)
	{
		philo_char->must_eat = ft_atoi(argv[5]);
		if (philo_char->must_eat < 0)
			return (false);
	}
	return (true);
}

int	ft_strlen(const char *str)
{
	const char	*init_pos = str;

	while (*str)
		++str;
	return (str - init_pos);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

bool	is_valid_input(const int argc, const char *argv[],
		t_philo_character *philo_char)
{
	const char	*input_argc_error_msg = "usage: \n\
1. number_of_philosophers\n\
2. time_to_die(in milliseconds\n\
3. time_to_eat(in milliseconds\n\
4. time_to_sleep(in milliseconds\n\
5. number_of_times_each_philosopher_must_eat(optional argument";
	const char	*input_number_error_msg = "usage: \n\
1. philosopher more than 0\n\
2. negative argument is not allowed";

	memset(philo_char, 0, sizeof(*philo_char));
	if (!(argc == 5 || argc == 6))
	{
		ft_putstr_fd(input_argc_error_msg, 2);
		return (false);
	}
	if (!is_valid_number(argc, argv, philo_char))
	{
		ft_putstr_fd(input_number_error_msg, 2);
		return (false);
	}
	return (true);
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

int	init_mutex(t_shared_data *shared_data, int identity)
{
	if (_pthread_mutex_init(&shared_data->m_is_all_eat, NULL) == 1)
		return (1);
	if (_pthread_mutex_init(&shared_data->m_is_anyone_die, NULL) == 1)
		return (1);
	if (_pthread_mutex_init(&shared_data->m_last_eat_time, NULL) == 1)
		return (1);
	if (_pthread_mutex_init(&shared_data->m_fork[identity], NULL) == 1)
		return (1);
	return (0);
}

int	malloc_struct(t_philosophy **philosophy, t_shared_data **shared_data_addr,
	pthread_mutex_t **m_fork_addr, int numbers)
{
	t_shared_data		*shared_data;
	pthread_mutex_t		*m_fork;

	*philosophy = malloc(sizeof(t_philosophy) * numbers);
	if (!*philosophy)
	{
		ft_putstr_fd("malloc() error", 2);
		return (1);
	}
	shared_data = malloc(sizeof(t_shared_data) * numbers);
	if (!shared_data)
	{
		ft_putstr_fd("malloc() error", 2);
		return (1);
	}
	m_fork = malloc(sizeof(pthread_mutex_t) * numbers);
	if (!m_fork)
	{
		ft_putstr_fd("malloc() error", 2);
		return (1);
	}
	*shared_data_addr = shared_data;
	*m_fork_addr = m_fork;
	return (0);
}

int	init_struct(t_philosophy **philosophy,
	t_philo_character *philo_character, int i)
{
	const int		n = philo_character->number_of_philosophers;
	struct timeval	start_time;
	t_shared_data	*shared_data;
	pthread_mutex_t	*m_fork;

	shared_data = NULL;
	m_fork = NULL;
	if (malloc_struct(philosophy, &shared_data, &m_fork, n) == 1)
		return (1);
	i = -1;
	gettimeofday(&start_time, NULL);
	while (++i < n)
	{
		shared_data[i].m_fork = m_fork;
		shared_data[i].is_all_eat = false;
		shared_data[i].is_anyone_die = false;
		shared_data[i].last_eat_time = 0;
		if (init_mutex(&shared_data[i], i) == 1)
			return (1);
		(*philosophy)[i].identity = i;
		(*philosophy)[i].philo_character = philo_character;
		(*philosophy)[i].shared_data = &shared_data[i];
		(*philosophy)[i].start_time = start_time;
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

long	get_elapsed_milesecond(t_philosophy *philosophy, bool is_eat_status)
{
	struct timeval	cur_time;
	long			elapsed_time;
	long			sec;
	int				usec;
	t_shared_data	*cur_shared_data;

	gettimeofday(&cur_time, NULL);
	cur_shared_data = philosophy->shared_data;
	sec = (cur_time.tv_sec - philosophy->start_time.tv_sec) * 1000;
	usec = (cur_time.tv_usec - philosophy->start_time.tv_usec) / 1000;
	elapsed_time = sec + usec;
	if (is_eat_status)
	{
		if (_pthread_mutex_lock(&cur_shared_data->m_last_eat_time) == 1)
			return (-1);
		cur_shared_data->last_eat_time = elapsed_time;
		if (_pthread_mutex_unlock(&cur_shared_data->m_last_eat_time) == 1)
			return (-1);
	}
	return (elapsed_time);
}

int	print_elapse_time(t_philosophy *philosophy,
	const char *status, bool is_eat_status)
{
	const int	identity = philosophy->identity;
	const long	elapsed = get_elapsed_milesecond(philosophy, is_eat_status);

	printf("%ld %d %s\n", elapsed, identity + 1, status);
	return (0);
}

int	msleep(int time)
{
	struct timeval	cur_time;
	long			start_sec;
	int				start_usec;
	int				waiting_time;

	gettimeofday(&cur_time, NULL);
	start_sec = cur_time.tv_sec;
	start_usec = cur_time.tv_usec;
	waiting_time = 0;
	while (waiting_time < time)
	{
		gettimeofday(&cur_time, NULL);
		waiting_time = (cur_time.tv_sec - start_sec) * 1000
			+ (cur_time.tv_usec - start_usec) / 1000;
		usleep(100);
	}
	return (0);
}

int	is_sleeping(t_philosophy *philosophy)
{
	const int		sleep_time = philosophy->philo_character->time_to_sleep;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (cur_shared_data->is_anyone_die == true)
	{
		if (pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == -1)
			return (-1);
		return (1);
	}
	if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	print_elapse_time(philosophy, "is sleeping", false);
	msleep(sleep_time);
	return (0);
}

int	putdown_fork(t_philosophy *philosophy)
{
	const int		identity = philosophy->identity;
	const int		n = philosophy->philo_character->number_of_philosophers;
	const int		left_fork = identity;
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (cur_shared_data->is_anyone_die == true)
	{
		if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
			return (-1);
		return (1);
	}
	if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (_pthread_mutex_unlock(&cur_shared_data->m_fork[right_fork]) == 1)
		return (-1);
	if (_pthread_mutex_unlock(&cur_shared_data->m_fork[left_fork]))
		return (-1);
	return (0);
}

int	eat_spaghetti(t_philosophy *philosophy)
{
	const int		eat_time = philosophy->philo_character->time_to_eat;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (cur_shared_data->is_anyone_die == true)
	{
		if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
			return (-1);
		return (1);
	}
	if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	print_elapse_time(philosophy, "is eating", true);
	msleep(eat_time);
	return (0);
}

int	get_fork(t_philosophy *philosophy)
{
	const int		identity = philosophy->identity;
	const int		n = philosophy->philo_character->number_of_philosophers;
	const int		left_fork = identity;
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (left_fork == right_fork)
		return (msleep(philosophy->philo_character->time_to_die));
	if (_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (cur_shared_data->is_anyone_die == true)
	{
		_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die);
		return (1);
	}
	if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (_pthread_mutex_lock(&cur_shared_data->m_fork[left_fork]) == 1)
		return (-1);
	if (_pthread_mutex_lock(&cur_shared_data->m_fork[right_fork]) == 1)
		return (-1);
	return (print_elapse_time(philosophy, "has taken a fork", true));
}

int	is_thinking(t_philosophy *philosophy)
{
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (cur_shared_data->is_anyone_die == true)
	{
		if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
			return (-1);
		return (1);
	}
	if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	print_elapse_time(philosophy, "is thinking", false);
	return (0);
}

int	routine(t_philosophy *philosophy, int identity, int eat_count, int numbers)
{
	const int	left_fork = identity;
	const int	right_fork = (identity + numbers - 1) % numbers;

	while (--eat_count >= 0)
	{
		if (is_thinking(philosophy))
			return (1);
		if (get_fork(philosophy))
			return (1);
		if (eat_spaghetti(philosophy))
		{
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[right_fork]);
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[left_fork]);
			return (1);
		}
		if (putdown_fork(philosophy))
		{
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[right_fork]);
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[left_fork]);
			return (1);
		}
		if (is_sleeping(philosophy))
			return (1);
	}
	return (0);
}

void	*dining_philosopher(void *philo)
{
	t_philosophy	*philosophy;
	int				identity;
	int				eat_count;
	int				numbers;
	int				sleep_time;

	philosophy = (t_philosophy *)philo;
	identity = philosophy->identity;
	eat_count = philosophy->philo_character->must_eat;
	sleep_time = philosophy->philo_character->time_to_sleep;
	numbers = philosophy->philo_character->number_of_philosophers;
	if (identity % 2 == 0)
		msleep(sleep_time);
	if (routine(philosophy, identity, eat_count, numbers) == 1)
		return (NULL);
	pthread_mutex_lock(&philosophy->shared_data->m_is_all_eat);
	philosophy->shared_data->is_all_eat = true;
	pthread_mutex_unlock(&philosophy->shared_data->m_is_all_eat);
	return (NULL);
}

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

int	create_philosophers(t_philosophy **philosophy,
	t_philo_character *philo_character)
{
	int	i;

	i = -1;
	init_struct(philosophy, philo_character, i);
	while (++i < philo_character->number_of_philosophers)
	{
		if (_pthread_create(&((*philosophy)[i].thread), NULL,
			dining_philosopher, &(*philosophy)[i]) == 1)
			return (1);
	}
	return (0);
}

bool	is_philo_dead(t_philosophy *philo)
{
	int			i;
	int			fasting_time;
	long		passed_time_start;
	const int	numbers = philo->philo_character->number_of_philosophers;
	const int	time_to_die = philo->philo_character->time_to_die;

	i = -1;
	while (++i < numbers)
	{
		passed_time_start = get_elapsed_milesecond(&philo[i], false);
		_pthread_mutex_lock(&(philo[i].shared_data->m_last_eat_time));
		fasting_time = passed_time_start - philo[i].shared_data->last_eat_time;
		if (fasting_time >= time_to_die)
		{
			_pthread_mutex_lock(&philo[i].shared_data->m_is_anyone_die);
			philo[i].shared_data->is_anyone_die = true;
			_pthread_mutex_unlock(&philo[i].shared_data->m_is_anyone_die);
			_pthread_mutex_unlock(&(philo[i].shared_data->m_last_eat_time));
			print_elapse_time(&philo[i], "died", false);
			return (true);
		}
		_pthread_mutex_unlock(&(philo[i].shared_data->m_last_eat_time));
	}
	return (false);
}

bool	is_all_finished_dining(t_philosophy *philosophy)
{
	const int	n = philosophy->philo_character->number_of_philosophers;
	int			i;

	i = -1;
	while (++i < n)
	{
		_pthread_mutex_lock(&(philosophy[i].shared_data->m_is_all_eat));
		if (philosophy[i].shared_data->is_all_eat == false)
		{
			_pthread_mutex_unlock(&(philosophy[i].shared_data->m_is_all_eat));
			return (false);
		}
		_pthread_mutex_unlock(&(philosophy[i].shared_data->m_is_all_eat));
	}
	return (true);
}

int	monitor_philosophers(t_philosophy *philosophy)
{
	const int		n = philosophy->philo_character->number_of_philosophers;
	int				i;
	t_shared_data	*cur_shared_data;

	while (1)
	{
		if (is_philo_dead(philosophy))
		{
			i = -1;
			while (++i < n)
			{
				cur_shared_data = philosophy[i].shared_data;
				_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die);
				philosophy[i].shared_data->is_anyone_die = true;
				_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die);
			}
			return (0);
		}
		if (is_all_finished_dining(philosophy))
			return (0);
	}
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

int	_pthread_join(pthread_t thread, void **value_ptr)
{
	if (pthread_join(thread, value_ptr) != 0)
	{
		ft_putstr_fd("pthread_join() error", 2);
		return (1);
	}
	return (0);
}

int	return_resource(t_philosophy *philosophy)
{
	const int		n = philosophy->philo_character->number_of_philosophers;
	int				i;
	t_shared_data	*cur_shared_data;

	i = -1;
	while (++i < n)
		if (_pthread_join(philosophy[i].thread, NULL) == 1)
			return (1);
	i = -1;
	while (++i < n)
	{
		cur_shared_data = philosophy[i].shared_data;
		if (_pthread_mutex_destroy(&cur_shared_data->m_last_eat_time) == 1)
			return (1);
		if (_pthread_mutex_destroy(&cur_shared_data->m_is_anyone_die) == 1)
			return (1);
		if (_pthread_mutex_destroy(&cur_shared_data->m_is_all_eat) == 1)
			return (1);
		if (_pthread_mutex_destroy(&cur_shared_data->m_fork[i]) == 1)
			return (1);
	}
	free(philosophy[0].shared_data->m_fork);
	free(philosophy[0].shared_data);
	free(philosophy);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_character	philo_character;
	t_philosophy		*philosophy;

	philosophy = NULL;
	if (!is_valid_input(argc, (const char **)argv, &philo_character))
		return (1);
	if (create_philosophers(&philosophy, &philo_character) == 1)
		return (1);
	if (monitor_philosophers(philosophy) == 1)
		return (1);
	return (return_resource(philosophy));
}
