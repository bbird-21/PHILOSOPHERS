/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/06 15:49:02 by mmeguedm         ###   ########.fr       */
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
		if (!__eat(philo))
			return (NULL);
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
	return (true);
}

