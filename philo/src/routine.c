/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:25:23 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/08 17:25:40 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	print_state_fork(t_philo philo, char c)
// {
// 	struct timeval	t;

// 	gettimeofday(&t, NULL);
// 	printf("%ld %c_FORK_UNLOCKED_BY : %d\n", (t.tv_sec * 1000) + (t.tv_usec / 1000), c, philo.id);
// }

// static void	print_info(t_philo philo, int r_pos_fork, int l_pos_fork)
// {
// 	printf("ID_PHILO : %d\t", philo.id);
// 	printf("l_pos : %d\tstate : %d\n", l_pos_fork, philo.fork[l_pos_fork]);
// 	printf("r_pos : %d\tstate : %d\n\n", r_pos_fork, philo.fork[r_pos_fork]);
// 	usleep(1000000);
// }

static void	bolt_fork(t_philo *philo, int mutex_state)
{
	if (mutex_state == LOCK)
		pthread_mutex_lock(&(philo->shared->fork[philo->first_fork]));
	else if (mutex_state == UNLOCK_A)
		pthread_mutex_unlock(&(philo->shared->fork[philo->first_fork]));
	else if (mutex_state == UNLOCK_A_B)
	{
		pthread_mutex_unlock(&(philo->shared->fork[philo->second_fork]));
		pthread_mutex_unlock(&(philo->shared->fork[philo->first_fork]));
	}
}

bool	print_state(t_philo *philo, int state, int mutex_state)
{
	struct timeval	t;
	const char	*state_arr[LENGHT] = {
		"has taken a fork\n",
		"is eating\n",
		"is thinking\n",
		"is sleeping\n"
	};

	pthread_mutex_lock(&(philo->shared->m_state));
	gettimeofday(&t, NULL);
	if (philo->shared->state == 0)
	{
		bolt_fork(philo, mutex_state);
		pthread_mutex_unlock(&(philo->shared->m_state));
		return (false);
	}
	printf("%ld %d %s", get_time(philo->start_time_ms),
		philo->id, (char *)state_arr[state]);
	pthread_mutex_unlock(&(philo->shared->m_state));
	return (true);
}

long	get_death_time(int	ttd, long start_time_ms)
{
	return (get_time(start_time_ms) + (ttd / 1000));
}

long	get_time(long start_time_ms)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000) - start_time_ms);
}

bool	sleep_time(int tts, t_philo *philo)
{
	int				a;
	long	time_stamp;
	long	finish_time;

	a = 0;
	time_stamp = get_time(philo->start_time_ms);
	finish_time = time_stamp + (tts / 1000);
	while (time_stamp < finish_time)
	{
		if (a == 10000)
		{
			pthread_mutex_lock(&(philo->shared->m_state));
			if (philo->shared->state == 0)
			{
				pthread_mutex_unlock(&(philo->shared->m_state));
				return (false);
			}
			a = 0;
			pthread_mutex_unlock(&(philo->shared->m_state));
		}
		time_stamp = get_time(philo->start_time_ms);
		usleep(100);
		a += 100;
	}
	return (true);
}

void	set_pos_first_fork(t_philo *philo)
{
	if (philo->id == 1)
		philo->first_fork = 0;
	else if (philo->id % 2 == 0)
		philo->first_fork = philo->id - 2;
	else
		philo->first_fork = philo->id - 1;		
}

void	set_pos_second_fork(t_philo *philo)
{
	if (philo->id == 1)
		philo->second_fork = philo->np - 1;
	else if (philo->id % 2 == 0)
		philo->second_fork = philo->id - 1; 
	else
		philo->second_fork = philo->id - 2;
}

static bool	philo_cycle(t_philo *philo)
{
	philo->cycle++;
	if (philo->cycle == philo->pms)
	{
		pthread_mutex_lock(&(philo->shared->m_must_eat));
		philo->shared->must_eat++;
		pthread_mutex_unlock(&(philo->shared->m_must_eat));
	}
	return (true);
}

bool	__eat(t_philo *philo)
{
	set_pos_first_fork(philo);
	set_pos_second_fork(philo);
	pthread_mutex_lock(&(philo->shared->fork[philo->first_fork]));
	// printf("first block : id : %d\tfork : %d\n", philo->id, philo->first_fork);
	if (!print_state(philo, FORK, UNLOCK_A))
		return (false);
	if (philo->np == 1)
		return (false);
	pthread_mutex_lock(&(philo->shared->fork[philo->second_fork]));
	// printf("second block : id : %d\tfork : %d\n", philo->id, philo->second_fork);
	if (!print_state(philo, FORK, UNLOCK_A_B))
		return (false);
	if (!print_state(philo, EAT, UNLOCK_A_B))
		return (false);
	pthread_mutex_lock(&(philo->shared->m_death_time[philo->id - 1]));
	philo->shared->death_time[philo->id - 1] = get_death_time(philo->ttd, philo->start_time_ms);
	pthread_mutex_unlock(&(philo->shared->m_death_time[philo->id -  1]));
	sleep_time(philo->tte, philo);
	bolt_fork(philo, UNLOCK_A_B);
	// printf("second unblock : %d\n", philo->id);
	// printf("first unblock : %d\n", philo->id);
	if (!philo_cycle(philo))
		return (false);
	return (__sleep(philo));
}

bool	__think(t_philo *philo)
{
	if (!print_state(philo, THINK, NONE))
		return (false);
	usleep(1000);
	return (true);
}

bool	__sleep(t_philo *philo)
{
	if (!print_state(philo, SLEEP, NONE))
		return (false);
	sleep_time(philo->tts, philo);
	return (__think(philo));
}
