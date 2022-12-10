/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/10 19:17:23 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_thread_philo(void *philo_params, t_philo *dest)
{
	t_philo	*src;
	
	src = (t_philo*)(philo_params);
	dest->np =  src->np;
	dest->ttd = src->ttd;
	dest->tte = src->tte;
	dest->tts = src->tts;
	dest->pms = src->pms;
	dest->id = src->id;
	dest->mutex = src->mutex;
	// dest->fork = src->fork;
}

void	*thread_function(void * philo_params)
{
	t_philo	thread_philo;
	int i;
	int	r_pos_fork;
	int	l_pos_fork;
	
	i = 0;
	init_thread_philo(philo_params, &thread_philo);
	while (21)
	{	
		//	Set pos fork	/////////////////
		l_pos_fork = thread_philo.id - 1;
		if (thread_philo.id == 1)
			r_pos_fork = thread_philo.np - 1;
		else
			r_pos_fork = thread_philo.id - 2;
		/////////////////////////////////////
		if (thread_philo.id % 2 == 1)
		{
			print_state(thread_philo, THINK);
			usleep(1000);
		}
		__eat(&thread_philo);
	}
	return (NULL);
}

bool	init_thread(t_philo *philo)
{
	int		i;
	
	i = -1;
	while (++i < philo->np)
	{
		philo->id = i + 1;
		if (pthread_create(&philo->thread_id[i], NULL, thread_function, philo))
			return (false);
		usleep(100);
	}
	i = -1;
	while (++i < philo->np)
		pthread_join(philo->thread_id[i], NULL);
	return (true);
}

// time_stamp = 16:45:30
