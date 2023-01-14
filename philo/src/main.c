/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:16:55 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/01/14 20:46:48 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static bool	init_philo(int argc, char **argv, t_philo *philo)
{
	if ((argc < 5 || argc > 6))
		return (false);
	philo->np = parse_args(argv[1]);
	philo->ttd = parse_args(argv[2]) * 1000;
	philo->tte = parse_args(argv[3]) * 1000;
	philo->tts = parse_args(argv[4]) * 1000;
	philo->pms = -2;
	if (argc == 6)
		philo->pms = parse_args(argv[5]);
	if ((philo->np == -1) || (philo->ttd == -1) || (philo->tte == -2)
		|| (philo->tts == -1) || (philo->pms == -1)
		|| (philo->np < 1))
 			return (false);
	return (true);
}


bool init_arr_philo(t_philo **arr_philo, t_philo philo_params,
		t_shared_mem *shared_mem)
{
	int		i;

	i = 0;
 	*arr_philo = malloc(sizeof(t_philo) * philo_params.np);
	if (!*arr_philo)
		return (false);
	while (i < philo_params.np)
	{
		(*arr_philo)[i].shared = shared_mem;
		(*arr_philo)[i].np = philo_params.np;
		(*arr_philo)[i].ttd = philo_params.ttd;
		(*arr_philo)[i].tte = philo_params.tte;
		(*arr_philo)[i].tts = philo_params.tts;
		(*arr_philo)[i].pms = philo_params.pms;
		(*arr_philo)[i].id = i + 1;
		(*arr_philo)[i].shared->death_time[i] = get_death_time(philo_params.ttd);
		i++;
	}
	return (true);
}

bool	init_shared_mem(t_shared_mem *shared_mem, t_philo philo)
{
	int			i;

	i = -1;
	shared_mem->fork = malloc(sizeof(*shared_mem->fork) * philo.np);
	shared_mem->n_fork = malloc(sizeof(*shared_mem->n_fork) * philo.np);
	shared_mem->death_time = malloc(sizeof(*shared_mem->death_time) * philo.np);
	shared_mem->state = 1;
	if (!shared_mem->fork)
		return (false);
	while (++i < philo.np)
		pthread_mutex_init(&(shared_mem->fork[i]), NULL);
	pthread_mutex_init(&(shared_mem->m_msg), NULL);
	pthread_mutex_init(&(shared_mem->m_state), NULL);
	return (true);
}

bool	mower(t_philo *arr_philo, t_shared_mem *shared_mem)
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
		time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		while (++i < arr_philo[0].np)
		{
			pthread_mutex_lock(&(arr_philo[0].shared->m_state));
			if (time_stamp >= shared_mem->death_time[i])
			{
				shared_mem->state = 0;
				printf("%ld %d died\n", time_stamp, i + 1);
				pthread_mutex_unlock(&(arr_philo[0].shared->m_state));
				return (false);
			}
			pthread_mutex_unlock(&(arr_philo[0].shared->m_state));
		}
		usleep(1000);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo			philo;
	t_philo			*arr_philo;
	t_shared_mem	shared_mem;
	int				i;

	i = -1;

	if (!init_philo(argc, argv, &philo))
		return (printf("Invalid arguments\n"));
	if (!init_shared_mem(&shared_mem, philo))
		return (printf("ENOMEM : Out of memory\n"));
	if (!init_arr_philo(&arr_philo, philo, &shared_mem))
		return (printf("ENOMEM : Out of memory\n"));
	if (!init_thread(&arr_philo))
		return (printf("pthread_create encountered an error\n"));
	mower(arr_philo, &shared_mem);
	while (++i < philo.np)
		pthread_join(arr_philo[i].thread_id, NULL);
}

// struct timeval t;
	// long			time_stamp;
	// long			finish_time;


	// gettimeofday(&t, NULL);
	// time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	// printf("time_stamp : %ld\n", time_stamp);

	// sleep_time(1000000);

	// gettimeofday(&t, NULL);
	// time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	// printf("time_stamp : %ld\n", time_stamp);
