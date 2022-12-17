/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:25:23 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/17 21:03:19 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_state_fork(t_philo philo, char c)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	printf("%ld %c_FORK_UNLOCKED_BY : %d\n", (t.tv_sec * 1000) + (t.tv_usec / 1000), c, philo.id);
}

static void	print_info(t_philo philo, int r_pos_fork, int l_pos_fork)
{
	printf("ID_PHILO : %d\t", philo.id);
	printf("l_pos : %d\tstate : %d\n", l_pos_fork, philo.fork[l_pos_fork]);
	printf("r_pos : %d\tstate : %d\n\n", r_pos_fork, philo.fork[r_pos_fork]);
	usleep(1000000);
}

void	print_state(t_philo *philo, int state, int r_pos_fork, int l_pos_fork)
{
	struct timeval	t;
	const char	*state_arr[LENGHT] = {
		"has taken a fork\n",
		"is eating\n",
		"is thinking\n",
		"is sleeping\n"
	};
	
	if (philo->shared->state == 0)
	{
		// pthread_mutex_unlock(&philo->shared->fork[l_pos_fork]);
		// pthread_mutex_unlock(&philo->shared->fork[r_pos_fork]);
		// pthread_mutex_unlock(&philo->shared->m_state);
		return ;
	}
	gettimeofday(&t, NULL);
	printf("%ld %d %s", (t.tv_sec * 1000) + (t.tv_usec / 1000),
		philo->id, (char *)state_arr[state]);
}

long	get_death_time(int	ttd)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000) + (ttd / 1000));
}

bool	sleep_time(int tts, t_philo *philo)
{
	struct timeval t;
	long			time_stamp;
	long			finish_time;


	gettimeofday(&t, NULL);
	time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	finish_time = time_stamp + (tts / 1000);
	while (time_stamp < finish_time)
	{
		pthread_mutex_lock(&philo->shared->m_state);
		if (philo->shared->state == 0)
		{
			pthread_mutex_unlock(&philo->shared->m_state);
			return (false);
		}
		pthread_mutex_unlock(&philo->shared->m_state);
		gettimeofday(&t, NULL);
		time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		usleep(100);
	}
	return (true);
}

void	__eat(t_philo *philo)
{
	int	r_pos_fork;
	int	l_pos_fork;
	int	i;

	i = -1;
	//	Set pos fork
	l_pos_fork = philo->id - 1;
	if (philo->id == 1)
		r_pos_fork = philo->np - 1;
	else
		r_pos_fork = philo->id - 2;
	pthread_mutex_lock(&philo->shared->fork[l_pos_fork]);
	//	Lock the fork
	pthread_mutex_lock(&philo->shared->msg);
	print_state(philo, FORK, r_pos_fork, l_pos_fork);	
	pthread_mutex_unlock(&philo->shared->msg);
	pthread_mutex_lock(&philo->shared->fork[r_pos_fork]);

	//	All prerequisite are respected
	//	Lock the fork
	pthread_mutex_lock(&philo->shared->msg);
	print_state(philo, FORK, r_pos_fork, l_pos_fork);
	pthread_mutex_unlock(&philo->shared->msg);
	
	pthread_mutex_lock(&philo->shared->msg);
	print_state(philo, EAT, r_pos_fork, l_pos_fork);
	pthread_mutex_unlock(&philo->shared->msg);
	philo->shared->death_time[philo->id - 1] = get_death_time(philo->ttd);
	sleep_time(philo->tte, philo);
	pthread_mutex_unlock(&philo->shared->fork[l_pos_fork]);
	pthread_mutex_unlock(&philo->shared->fork[r_pos_fork]);
	__sleep(philo, r_pos_fork, l_pos_fork);
}

void	__think(t_philo *philo, int r_pos_fork, int l_pos_fork)
{
	pthread_mutex_lock(&philo->shared->msg);
	print_state(philo, THINK, r_pos_fork, l_pos_fork);
	pthread_mutex_unlock(&philo->shared->msg);
	// usleep(1000);
}

void	__sleep(t_philo *philo, int r_pos_fork, int l_pos_fork)
{
	pthread_mutex_lock(&philo->shared->msg);
	print_state(philo, SLEEP, r_pos_fork, l_pos_fork);
	pthread_mutex_unlock(&philo->shared->msg);
	sleep_time(philo->tts, philo);
	__think(philo, r_pos_fork, l_pos_fork);
}
