/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:25:23 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/08 19:39:57 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_state(struct timeval t, t_philo philo, int state)
{
	const char	*state_arr[LENGHT] = {
		"has taken a fork\n",
		"is eating\n",
		"is thinking\n",
		"is sleeping\n"
	};
	
	printf("%ld %d %s", (t.tv_sec * 1000) + (t.tv_usec / 1000),
		philo.id, (char *)state_arr[state]);
}

void	__eat(t_philo *philo)
{
	struct timeval	t;
	int	r_pos_mutex;
	int	l_pos_mutex;
	
	r_pos_mutex = philo->id;
	if (philo->id == 1)
		l_pos_mutex = philo->np;
	else
		l_pos_mutex = philo->id - 1;
	pthread_mutex_lock(&philo->mutex[r_pos_mutex]);
	pthread_mutex_lock(&philo->mutex[l_pos_mutex]);
	gettimeofday(&t, NULL);
	print_state(t, *philo, EAT);
	usleep(philo->tte);
	pthread_mutex_unlock(&philo->mutex[r_pos_mutex]);
	pthread_mutex_unlock(&philo->mutex[l_pos_mutex]);
}

void	__think(t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	print_state(t, *philo, THINK);
	usleep(1000);
}

void	__sleep(t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	print_state(t, *philo, SLEEP);
	usleep(philo->tts);
}

