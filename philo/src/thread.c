/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/09 19:30:26 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_thread_philo(void *philo_params, t_philo *dest)
{
	t_philo	*src;
	
	src = (t_philo*)(philo_params);
	dest->np =  src->np;
	dest->ttd = src->ttd * 1000;
	dest->tte = src->tte * 1000;
	dest->tts = src->tts * 1000;
	dest->pms = src->pms;
	dest->id = src->id;
	dest->mutex = src->mutex;
	dest->fork = src->fork;
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
			usleep(1000);
		__eat(&thread_philo);
		// if(thread_philo.fork[l_pos_fork] == 1 
		// 	&& thread_philo.fork[r_pos_fork] == 1)
		// 	__eat(&thread_philo);
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
/*

1sec sleep
time_stamp = 16:45:30
while (time_stamp < time_stamp + 1)
	usleep(1000);
	gettimeofaday(&time_stamp, NULL);
*/