/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:43:32 by junji             #+#    #+#             */
/*   Updated: 2023/01/16 11:16:38 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

/*
 *  int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
 *  void *(*start_routine)(void *), void *arg);
 *
 * return value = zero, otherwise error;
 *
 */

/*
 * int
     pthread_join(pthread_t thread, void **value_ptr);
 *
 * return value = zero, otherwise error
 */

/*
 * int
     pthread_mutex_init(pthread_mutex_t *mutex,
         const pthread_mutexattr_t *attr);
 *
 * return value = zero, otherwise error
 */

/*
 * int
     pthread_mutex_destroy(pthread_mutex_t *mutex);
 *
 * return value = zero, otherwise error;
 */

/*
 *      int
     pthread_mutex_lock(pthread_mutex_t *mutex);
 *
 * return value = zero, otherwise error;
 */
/*
 *int
     pthread_mutex_unlock(pthread_mutex_t *mutex);
 *
 * return value = zero, otherwise error;
 */

/*
 * 시간 측정
 * 1. 철학자가 포크를 들었을 때
 * 2. 철학자가 먹기 시작할 때
 * 3. 철학자가 자기 시작할 때
 * 4. 철학자가 생각할 때(포크를 들지도 않았고, 먹지도 않았고, 잠자지도 않았으면)
 * 5. 철학자가 죽었을 때 
 *struct timeval start_time, end_time;
 * gettimeofday(&start_time, NULL);
 * 어떤 동작
 * gettimeofday(&end_time, NULL);
 * print_elapse_time(1. 철학자)
 * {
 * }
 * int elapsed_time = (end_time.tv_usec - start_time.tv_usec) * 1000; 
 * 
 * 1. sleep에서 차이가 심한 이유
 * - sleep에서 깨어나는 시간이 현재 스케줄러 상황에 따라 다르기 때문.
 */
// =========Syscall==========
// ==========================
// 1. 시간 음수 체크
// 2. 철학자가 한 명 일때
// 3. time_to_die가 0이라면?

typedef struct s_philo_character
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_philo_character;

typedef struct s_philosophy
{
	int					identity;
	struct timeval		start_time;
	pthread_t			*thread;
	t_philo_character	*philo_char;

	pthread_mutex_t		*m_fork;

	pthread_mutex_t		m_all_created;

	pthread_mutex_t		m_last_eat_time;
	long				last_eat_time;

	pthread_mutex_t		m_is_all_eat;
	bool				is_all_eat;

	pthread_mutex_t		m_is_syscall_failed;
	bool				is_syscall_failed;
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
1. philosopher more than 1\n\
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


int	_pthread_mutex_init(t_philosophy *philosophy, int identity)
{
	const int fork_result = pthread_mutex_init(&(philosophy->m_fork[identity]), NULL);
	const int cur_eat_result = pthread_mutex_init(&philosophy->m_is_all_eat, NULL);
	const int last_eat_time_result = pthread_mutex_init(&philosophy->m_last_eat_time, NULL);
	const int syscall_fail_result = pthread_mutex_init(&philosophy->m_is_syscall_failed, NULL);
	const int m_all_created = pthread_mutex_init(&philosophy->m_all_created, NULL);

	if (fork_result || cur_eat_result || last_eat_time_result
		|| syscall_fail_result || m_all_created)
	{
		ft_putstr_fd("pthread_mutex_init() error", 2);
		return (1);
	}
	return (0);
}

int	malloc_struct(t_philo_character *philo_char, t_philosophy **philosophy, void **thread_addr, void **m_fork_addr)
{
	pthread_t	*thread;
	pthread_t	*m_fork;

	*philosophy = malloc(sizeof(t_philosophy) * philo_char->number_of_philosophers);
	if (!*philosophy)
	{
		ft_putstr_fd("malloc() error", 2);
		return (1);
	}
	thread = malloc(sizeof(pthread_t) * philo_char->number_of_philosophers);
	if (!thread)
	{
		ft_putstr_fd("malloc() error", 2);
		return (1);
	}
	m_fork = malloc(sizeof(pthread_mutex_t) * philo_char->number_of_philosophers);
	if (!m_fork)
	{
		ft_putstr_fd("malloc() error", 2);
		return (1);
	}
	*thread_addr = thread;
	*m_fork_addr = m_fork;
	return (0);
}

int	init_struct(t_philo_character *philo_char, t_philosophy **philosophy)
{
	int	i;
	void *thread_addr;
	void *m_fork_addr;
	struct timeval start_time;

	thread_addr = NULL;
	m_fork_addr = NULL;
	if (malloc_struct(philo_char, philosophy, &thread_addr, &m_fork_addr) == 1)
		return (1);
	i = -1;
	gettimeofday(&start_time, NULL);
	while (++i < philo_char->number_of_philosophers)
	{
		(*philosophy)[i].identity = i;
		(*philosophy)[i].is_all_eat = false;
		(*philosophy)[i].is_syscall_failed = false;
		(*philosophy)[i].thread = thread_addr;
		(*philosophy)[i].m_fork = m_fork_addr;
		(*philosophy)[i].last_eat_time = 0;
		if (_pthread_mutex_init(&(*philosophy)[i], i) != 0)
			return (1);
		(*philosophy)[i].philo_char = philo_char;
	}
	return (0);
}

// 기준 시간, mutex_ eat_status
long	get_elapsed_milesecond(t_philosophy *philosophy, bool is_eat_status)
{
	struct		timeval cur_time;
	long		elapsed_time;
	long		sec;
	int			usec;

	gettimeofday(&cur_time, NULL);
	sec = (cur_time.tv_sec - philosophy->start_time.tv_sec ) * 1000;
	usec = (cur_time.tv_usec - philosophy->start_time.tv_usec) / 1000;
	elapsed_time = sec + usec;
	if (is_eat_status)
	{
		pthread_mutex_lock(&philosophy->m_last_eat_time);
		philosophy->last_eat_time = elapsed_time;
		pthread_mutex_unlock(&philosophy->m_last_eat_time);
	}
	return (elapsed_time);
}

void print_elapse_time(t_philosophy *philosophy, const char *status, bool is_eat_status)
{
	const int identity = philosophy->identity;
	const long elapsed_time = get_elapsed_milesecond(philosophy, is_eat_status);

	printf("%ld %d %s\n", elapsed_time, identity, status);
}

void	_msleep(int time)
{
	struct		timeval cur_time;
	long		start_sec;
	int			start_usec;
	int			waiting_time;

	gettimeofday(&cur_time, NULL);
	start_sec = cur_time.tv_sec;
	start_usec = cur_time.tv_usec;
	waiting_time = 0;
	while (waiting_time < time)
	{
		gettimeofday(&cur_time, NULL);
		waiting_time = (cur_time.tv_sec - start_sec) * 1000 + (cur_time.tv_usec - start_usec) / 1000;
		usleep(100);
	}
}

void	is_sleeping(t_philosophy *philosophy)
{
	const int sleep_time = philosophy->philo_char->time_to_sleep;

	print_elapse_time(philosophy, "is sleeping", false);
	_msleep(sleep_time);
}

void	putdown_fork(t_philosophy *philosophy)
{
	const int identity = philosophy->identity;
	const int numbers = philosophy->philo_char->number_of_philosophers;
	int	left_fork	= identity; 
	int	right_fork	= (identity + numbers - 1) % numbers;

	pthread_mutex_unlock(&philosophy->m_fork[right_fork]);
	pthread_mutex_unlock(&philosophy->m_fork[left_fork]);
//	if (philosophy->identity % 2 == 0)
//	{
//		if (identity == 0)
//			right_fork = number - 1;
//		pthread_mutex_unlock(&philosophy->m_fork[right_fork]);
//		pthread_mutex_unlock(&philosophy->m_fork[left_fork]);
//	}
//	else
//	{
//		pthread_mutex_unlock(&philosophy->m_fork[left_fork]);
//		pthread_mutex_unlock(&philosophy->m_fork[right_fork]);
//	}
}

void	eat_spaghetti(t_philosophy *philosophy)
{
	const int eat_time = philosophy->philo_char->time_to_eat;

	print_elapse_time(philosophy, "is eating", true);
	_msleep(eat_time);
}

//198
void	get_fork(t_philosophy *philosophy)
{
	const int identity = philosophy->identity;
	const int numbers = philosophy->philo_char->number_of_philosophers;
	int	left_fork	= identity; 
	int	right_fork	= (identity + numbers - 1) % numbers;

//	if (identity % 2 == 0)
//	{
//		if (identity == 0)
//			right_fork = numbers - 1;
		// 0 -> 4
		// 1 -> 0
		// 2 -> 1
		// 3 -> 2
		// 4 -> 3
		
		pthread_mutex_lock(&philosophy->m_fork[left_fork]);
		pthread_mutex_lock(&philosophy->m_fork[right_fork]);
		print_elapse_time(philosophy, "has taken a fork", true);
//		return ;
//	}
//	pthread_mutex_lock(&philosophy->m_fork[right_fork]);
//	pthread_mutex_lock(&philosophy->m_fork[left_fork]);
//	print_elapse_time(philosophy,  "has taken a fork", true);
}

void	is_thinking(t_philosophy *philosophy)
{
	print_elapse_time(philosophy, "is thinking", false);
}

void	*dining_philosopher(void *philo)
{
	t_philosophy	*philosophy;
	int				eat_count;

	philosophy = (t_philosophy *)(philo);
	const int identity = philosophy->identity;
	const int sleep_time = philosophy->philo_char->time_to_sleep;
	gettimeofday(&philosophy->start_time, NULL);
	eat_count = philosophy->philo_char->must_eat;
	if (identity % 2 == 0)
		_msleep(sleep_time);
	while (--eat_count >= 0)
	{
		is_thinking(philosophy);
		get_fork(philosophy);
		eat_spaghetti(philosophy);
		putdown_fork(philosophy);
		is_sleeping(philosophy);
	}
	pthread_mutex_lock(&philosophy->m_is_all_eat);
	philosophy->is_all_eat = true;
	pthread_mutex_unlock(&philosophy->m_is_all_eat);
	return (NULL);
}

int _pthread_create(t_philosophy *philosophy)
{
	const int result = pthread_create(philosophy->thread, NULL, dining_philosopher, philosophy);
	if (result)
	{
		ft_putstr_fd("pthread_create() error", 2);
			return (1);
	}
	return (0);
}

int	create_philosophers(t_philosophy *philosophy)
{
	int	i;

	i = -1;
	while (++i < philosophy->philo_char->number_of_philosophers)
	{
		if (_pthread_create(&philosophy[i]) == 1)
			return (1);
		int ret;
		ret = pthread_detach(*philosophy[i].thread);
		if (ret != 0)
		{
			printf("detach dㅔ러\n");
			exit(5);
		}
	}
	return (0);
}

bool	is_philo_dead(t_philosophy *philosophy)
{
	int		i;
	int		fasting_time;
	const	int	numbers = philosophy->philo_char->number_of_philosophers;
	const	int time_to_die = philosophy->philo_char->time_to_die;
	long	passed_time_to_start;

	i = -1;
	while (++i < numbers)
	{
		passed_time_to_start = get_elapsed_milesecond(&philosophy[i], false);
		pthread_mutex_lock(&(philosophy[i].m_last_eat_time));
		fasting_time = passed_time_to_start - philosophy[i].last_eat_time;
		if (fasting_time >= time_to_die)
		{
			print_elapse_time(&philosophy[i], "died", false);
			return (true);
		}
		pthread_mutex_unlock(&(philosophy[i].m_last_eat_time));
	}
	return (false);
}

bool	is_all_finished_dining(t_philosophy *philosophy)
{
	int	i;
	const	int	number = philosophy->philo_char->number_of_philosophers;

	i = -1;
	while (++i < number)
	{
		pthread_mutex_lock(&(philosophy[i].m_is_all_eat));
		if (philosophy[i].is_all_eat == false)
		{
			pthread_mutex_unlock(&(philosophy[i].m_is_all_eat));
			return (false);
		}
		pthread_mutex_unlock(&(philosophy[i].m_is_all_eat));
	}
	return (true);
}

int monitor_philosophers(t_philosophy *philosophy)
{
	while (1)
	{
		if (is_philo_dead(philosophy)) 
			return (0);
		if (is_all_finished_dining(philosophy))
			return (0);
//		if (is_systemcall_failed)
//			return (1);
	}
}
//
int	main(int argc, char *argv[])
{
	t_philo_character	philo_character;
	t_philosophy		*philosophy;

	if (!is_valid_input(argc, (const char **)argv, &philo_character))
		return (1);
	philosophy = NULL;
	if (init_struct(&philo_character, &philosophy) == 1)
		return (1);
//	int i = -1;
//	while (++i < philosophy[0].philo_char->number_of_philosophers)//philo_char.number_of_philosophers)
//	{
//		printf("identity: %d\n", philosophy[i].identity);
//		printf("%d %d %d %d %d\n", philosophy[i].philo_char->number_of_philosophers, philosophy[i].philo_char->must_eat, philosophy[i].philo_char->time_to_die, philosophy[i].philo_char->time_to_eat, philosophy[i].philo_char->time_to_sleep);
//	}
	if (create_philosophers(philosophy) == 1)
		return (1);
	if (monitor_philosophers(philosophy) == 1)
		return (1);
	return (0);
}
