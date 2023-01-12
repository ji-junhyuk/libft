/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:43:32 by junji             #+#    #+#             */
/*   Updated: 2023/01/12 13:06:53 by junji            ###   ########.fr       */
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
	bool				is_created;
	t_philo_character	*philo_char;
	pthread_t			*thread;
	pthread_mutex_t		*m_fork;

	pthread_mutex_t		m_cur_eat;
	int					cur_eat;

	pthread_mutex_t		m_is_philo_dead;
	bool				is_philo_dead;

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
	if (philo_char->number_of_philosophers <= 1)
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
	const int cur_eat_result = pthread_mutex_init(&philosophy->m_cur_eat, NULL);
	const int philo_dead_result = pthread_mutex_init(&philosophy->m_is_philo_dead, NULL);
	const int syscall_fail_result = pthread_mutex_init(&philosophy->m_is_syscall_failed, NULL);

	if (fork_result || cur_eat_result || philo_dead_result
		|| syscall_fail_result)
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

	*philosophy = malloc(sizeof(t_philosophy) * philo_char->number_of_philosophers + 1);
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
	m_fork = malloc(sizeof(pthread_mutex_t) * philo_char->number_of_philosophers + 1);
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

	thread_addr = NULL;
	m_fork_addr = NULL;
	if (malloc_struct(philo_char, philosophy, &thread_addr, &m_fork_addr) == 1)
		return (1);
	i = -1;
	while (++i < philo_char->number_of_philosophers)
	{
		(*philosophy)[i].identity = i;
		(*philosophy)[i].cur_eat = 0;
		(*philosophy)[i].is_philo_dead = false;
		(*philosophy)[i].is_syscall_failed = false;
		(*philosophy)[i].thread = thread_addr;
		(*philosophy)[i].m_fork = m_fork_addr;
		if (_pthread_mutex_init(&(*philosophy)[i], i) != 0)
			return (1);
		(*philosophy)[i].philo_char = philo_char;
	}
	return (0);
}

void print_elapse_time(int identity, struct timeval *start_time, const char *status)
{
	struct timeval cur_time;

	gettimeofday(&cur_time, NULL);
	int elapsed_time = (cur_time.tv_sec - start_time->tv_sec) * 1000 + (cur_time.tv_usec - start_time->tv_usec) / 1000;
	printf("%d %d %s\n", elapsed_time, identity, status);
}

void	is_sleeping(t_philosophy *philosophy, struct timeval *start_time)
{
	print_elapse_time(philosophy->identity, start_time, "is sleeping");
	usleep(philosophy->philo_char->time_to_sleep);
}

void	eat_spaghetti(t_philosophy *philosophy, struct timeval *start_time)
{
	const int number = philosophy->philo_char->number_of_philosophers;
	const int identity = philosophy->identity;

	print_elapse_time(philosophy->identity, start_time, "is eating");
	usleep(philosophy->philo_char->time_to_eat * 1000);
	if (philosophy->identity % 2 == 0)
	{
		pthread_mutex_unlock(&philosophy->m_fork[identity]);
		pthread_mutex_unlock(&philosophy->m_fork[(identity + 1) % number]);
	}
	else
	{
		pthread_mutex_unlock(&philosophy->m_fork[identity - 1]);
		pthread_mutex_unlock(&philosophy->m_fork[philosophy->identity]);
	}
}

void	get_fork(pthread_mutex_t *m_fork, int identity, int number_of_philosophers, struct timeval *start_time)
{
	if (identity % 2 == 0)
	{
		pthread_mutex_lock(&m_fork[identity]);
		pthread_mutex_lock(&m_fork[(identity + 1) % number_of_philosophers]);
		print_elapse_time(identity, start_time, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&m_fork[identity - 1]);
		pthread_mutex_lock(&m_fork[identity]);
		print_elapse_time(identity, start_time, "has taken a fork");
	}
}

static __inline t_philosophy *get_philosophy(void *philo)
{
	return ((t_philosophy *)(philo));
}

void	is_thinking(t_philosophy *philosophy, struct timeval *start_time)
{
	print_elapse_time(philosophy->identity, start_time, "is_thinking");
}

void	*dining_philosopher(void *philo)
{
	t_philosophy	*philosophy;
	struct timeval	start_time;

	philosophy = get_philosophy(philo);
	gettimeofday(&start_time, NULL);
	while (1)
	{
		get_fork(philosophy->m_fork, philosophy->identity, philosophy->philo_char->number_of_philosophers, &start_time);
		eat_spaghetti(philosophy, &start_time);
		is_sleeping(philosophy, &start_time);
		is_thinking(philosophy, &start_time);
	}
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
	philosophy->is_created = true;
	return (0);
}

bool	is_every_philo_created(t_philosophy *philosophy)
{
	int		i;

	i = -1;
	while (++i < philosophy->philo_char->number_of_philosophers)
	{
		if (philosophy[i].is_created == false)
			return (false);
	}
	return (true);
}

// 모든 스레드가 만들어질 때까지 기다려줘야 할까?
// -> 모든 스레드가 만들어지고 나서 철학자를 밥먹이는 것...
// 만들어지자마자 철학자 로직을 실행한다고 했을 때,
// 아직 만들어지지 않은 스레드의 뮤택스를 얻어오는 것이 가능할까?
// 어떻게 테스트하지?
// 스레드가 만들어진거 여부에 상관없이 뮤택스로 잠금이 되는 거 같다? 
// 생각해보면 스레드가 만들어지는 것과 뮤택스를 만들고 초기화하는 작업은 독립적이다.
int	create_philosophers(t_philosophy *philosophy)
{
	int	i;

	i = -1;
	while (++i < philosophy->philo_char->number_of_philosophers)
	{
		if (_pthread_create(&philosophy[i]) == 1)
			return (1);
	}
	return (0);
}

int	monitor_philosophers(t_philosophy *philosophy)
{
	const int number = philosophy->philo_char->number_of_philosophers;

	while (1)
	{
		int i = -1;
		while (++i < number)
		{
			if (philosophy[i].is_philo_dead == true)
				break ;

		}
		// 부모는 여기서 매번 
		// 1. 죽은 철학자가 있는지
		// 2. 모든 철학자가 먹어야 하는 횟수만큼 먹었는지 검사한다. // 난 초기에 0으로 초기화했는데. 조건으로 바로 탈출하거나 data race가 발생할 수 있나?
		// 3. 철학자들이 식사하면서 락을 걸고, 락을 풀고 하는 시스템 콜을 할텐데, 그 시스템 콜값이 실패한 게 있는지 체크해서 종료하는 것까지 추가.
	}
}

int	main(int argc, char *argv[])
{
	t_philo_character	philo_char;
	t_philosophy		*philosophy;

	if (!is_valid_input(argc, (const char **)argv, &philo_char))
		return (1);
	philosophy = NULL;
	if (init_struct(&philo_char, &philosophy) == 1)
		return (1);
//	int i = -1;
//	while (++i < philosophy[0].philo_char->number_of_philosophers)//philo_char.number_of_philosophers)
//	{
//		printf("identity: %d\n", philosophy[i].identity);
//		printf("cur_eat: %d\n", philosophy[i].cur_eat);
//		printf("is_philo_dead: %d\n", philosophy[i].is_philo_dead);
//		printf("%d %d %d %d %d\n", philosophy[i].philo_char->number_of_philosophers, philosophy[i].philo_char->must_eat, philosophy[i].philo_char->time_to_die, philosophy[i].philo_char->time_to_eat, philosophy[i].philo_char->time_to_sleep);
//	}
	if (create_philosophers(philosophy) == 1)
		return (1);
	if (monitor_philosophers(philosophy) == 1)
		return (1);
	return (0);
}
