/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:16:55 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/16 01:00:02 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Gerer le temps gettimeos addition des deux elements de la structure
//	Afficher les messages a l'inifi sans gerer la mort

// static void	init_fork(t_philo *philo)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < philo->np)
// 		philo->fork[i] = 1;
// }

static bool	init_philo(int argc, char **argv, t_philo *philo)
{
	int	i;

	i = -1;
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
	philo->fork = malloc(sizeof(*philo->fork) * (philo->np));
	philo->mutex = malloc(sizeof(*philo->mutex) * (philo->np));
	// philo->thread_id = malloc(sizeof(*philo->thread_id) * (philo->np) + 1);
	while (++i < philo->np)
		pthread_mutex_init(&philo->mutex[i], NULL);
	// init_fork(philo);
	return (true);
}

t_philo	*init_arr_philo(t_philo philo_params)
{
	t_philo	*philo;
	int		i;
	
	i = 0;
	philo = malloc(sizeof(*philo) * (philo_params.np));

	// printf("philo->shared_mem->test : %d\n", philo->shared_mem.test);
	while (i < philo_params.np)
	{
		philo[i].np = philo_params.np;
		philo[i].ttd = philo_params.ttd;
		philo[i].tte = philo_params.tte;
		philo[i].tts = philo_params.tts;
		philo[i].pms = philo_params.pms;
		philo[i].id = i;
		i++;
	}
	return (philo);
}

bool	check_death(t_philo *philo ,int	time_to)
{
	struct timeval	t;
	long			time_stamp;
	long			die_time;

	die_time = 0;
	time_stamp = 0;
	gettimeofday(&t, NULL);
	time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	die_time = time_stamp + (time_to / 1000);
	// long double tmp = die_time - time_stamp; 
	// printf("die_time : %ld\n", die_time);
	// printf("time_stamp : %ld\n", time_stamp);
	// printf("time_stamp - finish_stamp : %Lf\n", tmp);
	int	i;

	i = 0;
	// printf("time_stamp :  %ld\nfinish_time : %ld\n", time_stamp, die_time);
	while (21)
	{
		gettimeofday(&t, NULL);
		time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		usleep(1000);
		if (time_stamp > die_time)
			return (false);
		// philo->ttd -= 1000;
		if (philo->ttd == 0)
			return (false);
	}
	printf("i : %d\n", i);
	printf("time_stamp : %ld\n", time_stamp);
	printf("ttd : %d\n", philo->ttd);
	return (true);
}

// void	test(t_philo *philo)
// {
// 	printf("%d philo->np = %d\n", philo->id, philo->ttd);

// }


int	main(int argc, char **argv)
{
	t_philo			philo;
	t_philo			*arr_philo;
	
	if (!init_philo(argc, argv, &philo))
		return (printf("Invalid arguments\n"));
	arr_philo = init_arr_philo(philo);
	// test(&arr_philo[0]);
	
	if (!init_thread(&arr_philo))
		return (printf("pthread_create encountered an error\n"));
	// if (!check_death(&philo, philo.tts))
	// 	printf("philo is died\n");
	// printf("philo->shared_mem : %d\n", arr_philo[2].shared_mem.test);
}
