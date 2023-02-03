/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/03 16:40:22 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void * philo_params)
{
	t_philo					*philo;

	philo = (t_philo*)philo_params;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (21)
	{
		pthread_mutex_lock(&philo->shared->m_state);
		if (philo->shared->state == 0)
		{
			pthread_mutex_unlock(&philo->shared->m_state);
			break ;
		}
		pthread_mutex_unlock(&philo->shared->m_state);
		__eat(philo);
	}
	return (NULL);
}

bool	init_thread(t_philo **arr_philo)
{
	int			i;

	i = -1;
	while (++i < (*arr_philo)[0].np)
	{
		if (pthread_create(&((*arr_philo)[i].thread_id), NULL, thread_function, &(*arr_philo)[i]))
			break ;
		// usleep(100);
	}
	pthread_mutex_lock(&(*arr_philo)[0].shared->m_state);
	if ((*arr_philo)[0].shared->state == 0)
	{
		while (i--)
			pthread_join((*arr_philo)[i].thread_id, NULL);
	}
	pthread_mutex_unlock(&(*arr_philo)[0].shared->m_state);
	return (true);
}

