/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/08 17:26:41 by mmeguedm         ###   ########.fr       */
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
		pthread_mutex_lock(&(philo->shared->m_must_eat));
		if (philo->shared->must_eat == philo->np)
		{
			pthread_mutex_unlock(&(philo->shared->m_must_eat));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->shared->m_must_eat));
		if (!__eat(philo))
			return (NULL);
	}
	return (NULL);
}

static void	mower(t_philo *arr_philo, t_shared_mem *shared_mem)
{
	struct timeval	t;
	long			time_stamp;
	gettimeofday(&t, NULL);
	time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	int	i;

	while (21)
	{
		i = -1;
		gettimeofday(&t, NULL);
		time_stamp = get_time(arr_philo[0].start_time_ms);
		pthread_mutex_lock(&(shared_mem->m_must_eat));
		if (shared_mem->must_eat == arr_philo[0].np)
		{
			pthread_mutex_unlock(&(shared_mem->m_must_eat));
			break ;
		}
		pthread_mutex_unlock(&(shared_mem->m_must_eat));
		while (++i < arr_philo[0].np)
		{
			pthread_mutex_lock(&(arr_philo[0].shared->m_death_time[i]));
			if (time_stamp >= shared_mem->death_time[i])
			{
				pthread_mutex_lock(&(arr_philo[0].shared->m_state));
				shared_mem->state = 0;
				printf("%ld %d died\n", time_stamp, i + 1);
				pthread_mutex_unlock(&(arr_philo[0].shared->m_state));
				pthread_mutex_unlock(&(arr_philo[0].shared->m_death_time[i]));				
				return ;
			}
			pthread_mutex_unlock(&(arr_philo[0].shared->m_death_time[i]));
		}
		usleep(1000);
	}
}

bool	init_thread(t_philo **arr_philo, t_shared_mem *shared_mem)
{
	int	i;

	i = -1;
	while (++i < (*arr_philo)[0].np)
	{
		if (pthread_create(&((*arr_philo)[i].thread_id), NULL, thread_function, &(*arr_philo)[i]))
			break ;
		// usleep(100);
	}
	mower(*arr_philo, shared_mem);
	while (i--)
		pthread_join((*arr_philo)[i].thread_id, NULL);
	return (true);
}

