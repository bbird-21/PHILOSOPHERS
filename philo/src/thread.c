/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/16 14:31:07 by mmeguedm         ###   ########.fr       */
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
	t_philo					*thread_philo;
	int 					i;
	int						r_pos_fork;
	int						l_pos_fork;
	static pthread_mutex_t	test;
	
	i = 0;
	thread_philo = philo_params;
	// printf("%d philo->np = %d\n", thread_philo->id, thread_philo->ttd);
	
	pthread_mutex_lock(&test);
	printf("Hey %d !\n", thread_philo->id);
	usleep(3000000);
	printf("Bye  %d !\n", thread_philo->id);
	pthread_mutex_unlock(&test);
	if (thread_philo->id == 2)
		thread_philo->id = 21;
	// init_thread_philo(philo_params, &thread_philo);
	// while (21)
	// {	
	// 	//	Set pos fork	/////////////////
	// 	l_pos_fork = thread_philo.id - 1;
	// 	if (thread_philo.id == 1)
	// 		r_pos_fork = thread_philo.np - 1;
	// 	else
	// 		r_pos_fork = thread_philo.id - 2;
	// 	/////////////////////////////////////
	// 	if (thread_philo.id % 2 == 1)
	// 		usleep(1000);
	// 	__eat(&thread_philo);
	// }
	return (NULL);
}

void	test(t_philo *philo)
{
	printf("%d philo->np = %d\n", philo->id, philo->ttd);
	philo->id = 21;
}

bool	init_thread(t_philo **arr_philo)
{
	int		i;
	pthread_t	j;

	i = -1;
	// printf("arr_philo->test : %d\n", (*arr_philo)->shared_mem->test);
	while (++i < (*arr_philo)->np)
	{
		// printf("i : %d\n", i);
		if (pthread_create(&(*arr_philo)->thread_id[i], NULL, thread_function, &(*arr_philo)[i]))
			return (false);
		usleep(100);
	}
	i = -1;
	while (++i < (*arr_philo)->np)
		pthread_join((*arr_philo)->thread_id[i], NULL);
	return (true);
}

