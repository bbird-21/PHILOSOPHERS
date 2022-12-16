/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/16 18:13:43 by mmeguedm         ###   ########.fr       */
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
	// dest->fork = src->fork;
}

void	*thread_function(void * philo_params)
{
	t_philo					*philo;
	int 					i;
	int						r_pos_fork;
	int						l_pos_fork;
	// static t_shared_mem		shared_mem;
	philo = (t_philo*)philo_params;
	if (philo->id == 1 || philo->id == 2)
		usleep(1000000);
	static pthread_mutex_t	test;


	printf("test\n");
	pthread_mutex_init(&test, NULL);
	pthread_mutex_lock(&test);
	printf("Hey %d !\n", philo->id);
	usleep(3000000);
	printf("Bye  %d !\n", philo->id);
	pthread_mutex_unlock(&test);
	// shared_mem.mutex = malloc(sizeof(*shared_mem.mutex) * (philo->np));
	// while (++i < philo->np)
	// 	pthread_mutex_init(&shared_mem.mutex[i], NULL);
	// i = 0;
	// printf("test\n");
	// printf("%d philo->np = %d\n", philo->id, philo->ttd);
	
	// pthread_mutex_lock(&shared_mem.mutex[0]);
	// printf("Hey %d !\n", philo->id);
	// usleep(3000000);
	// printf("Bye  %d !\n", philo->id);
	// pthread_mutex_unlock(&shared_mem.mutex[0]);
	// if (philo->id == 2)
	// 	philo->id = 21;
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
	int			i;
	t_philo 	*tmp;
	pthread_t	j;
	i = -1;
	tmp = *arr_philo;
	printf("arr_philo->id : %d\n", (*arr_philo)[2].id);
	while (++i < (*arr_philo)[0].np)
	{
		// tmp = &arr_philo[i];
		// printf("arr_philo->id : %d\n", arr_philo[i]->id);
		// printf("tmp->id : %d\n", tmp->id);
		// print_philo(&tmp[i]);
		if (pthread_create(&((*arr_philo)[i].thread_id), NULL, thread_function, &(*arr_philo)[i]))
			return (false);
		usleep(100);
	}
	i = -1;
	while (++i < (*arr_philo)[0].np)
		pthread_join((*arr_philo)[i].thread_id, NULL);
	return (true);
}

