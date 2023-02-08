/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:25:23 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/08 09:46:59 by mmeguedm         ###   ########.fr       */
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

bool	print_state(t_philo *philo, int state)
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

bool	__eat(t_philo *philo)
{
	int	r_pos_fork;
	int	l_pos_fork;

	//This line have to be in v2 not in main.
	l_pos_fork = philo->id - 1;
	if (philo->id == 1)
		r_pos_fork = philo->np - 1;
	else
		r_pos_fork = philo->id - 2;
	pthread_mutex_lock(&(philo->shared->fork[l_pos_fork]));
	if (!print_state(philo, FORK))
	{
		pthread_mutex_unlock(&(philo->shared->fork[l_pos_fork]));
		return (false);
	}
	if (philo->np == 1)
		return (false);
	pthread_mutex_lock(&(philo->shared->fork[r_pos_fork]));
	if (!print_state(philo, FORK))
	{
		pthread_mutex_unlock(&(philo->shared->fork[r_pos_fork]));
		pthread_mutex_unlock(&(philo->shared->fork[l_pos_fork]));
		return (false);
	}
	if (!print_state(philo, EAT))
	{
		pthread_mutex_unlock(&(philo->shared->fork[r_pos_fork]));
		pthread_mutex_unlock(&(philo->shared->fork[l_pos_fork]));
		return (false);
	}

	pthread_mutex_lock(&(philo->shared->m_death_time[philo->id - 1]));
	philo->shared->death_time[philo->id - 1] = get_death_time(philo->ttd, philo->start_time_ms);
	pthread_mutex_unlock(&(philo->shared->m_death_time[philo->id -  1]));
	sleep_time(philo->tte, philo);
	pthread_mutex_unlock(&(philo->shared->fork[r_pos_fork]));
	pthread_mutex_unlock(&(philo->shared->fork[l_pos_fork]));
	philo->cycle++;
	if (philo->cycle == philo->pms)
	{
		pthread_mutex_lock(&(philo->shared->m_must_eat));
		philo->shared->must_eat++;
		pthread_mutex_unlock(&(philo->shared->m_must_eat));
		return (false);
	}
	return (__sleep(philo));
}

bool	__think(t_philo *philo)
{
	if (!print_state(philo, THINK))
		return (false);
	usleep(1000);
	return (true);
}

bool	__sleep(t_philo *philo)
{
	if (!print_state(philo, SLEEP))
		return (false);
	sleep_time(philo->tts, philo);
	return (__think(philo));
}
