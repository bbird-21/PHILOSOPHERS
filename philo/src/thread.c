/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/08 19:40:54 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_thread_philo(t_philo src, t_philo *dest)
{
	dest->np =  src.np;
	dest->ttd = src.ttd;
	dest->tte = src.tte;
	dest->tts = src.tts;
	dest->pms = src.pms;
	dest->id = src.id;
	dest->mutex = src.mutex;
}

void	*thread_function(void * philo_params)
{
	t_philo	*tmp_philo;
	t_philo	thread_philo;
	int i;
	
	i = 0;
	tmp_philo = (t_philo*)(philo_params);
	init_thread_philo(*tmp_philo, &thread_philo);
	while (21)
	{
		if (thread_philo.id % 2 == 0)
			__eat(&thread_philo);
		// else
		// 	__sleep(thread_philo);
		// __think(thread_philo);
	}
	return (NULL);
}

bool	init_thread(t_philo *philo)
{
	int		i;
	
	i = -1;
	while (++i < philo->np + 1)
	{
		philo->id = i + 1;
		if (pthread_create(&philo->thread_id[i], NULL, thread_function, philo))
			return (false);
		usleep(100000);
	}
	i = -1;
	while (++i < philo->np)
		pthread_join(philo->thread_id[i], NULL);
	return (true);
}