/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:16:55 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/11 00:21:25 by mmeguedm         ###   ########.fr       */
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
	philo->np = parse_args(argv[1]) * 1000;
	philo->ttd = parse_args(argv[2]) * 1000;
	philo->tte = parse_args(argv[3]) * 1000;
	philo->tts = parse_args(argv[4]) * 1000;
	philo->pms = -2;
	if (argc == 6)
		philo->pms = parse_args(argv[5]);
	if ((philo->np == -1) || (philo->ttd == -1) || (philo->tte == -2) 
		|| (philo->tts == -1) || (philo->pms == -1)
		|| (philo->np < 1)
		|| (argc < 5 || argc > 6))
			return (false);
	philo->thread_id = malloc(sizeof(*philo->thread_id) * philo->np);
	philo->fork = malloc(sizeof(*philo->fork) * (philo->np));
	philo->mutex = malloc(sizeof(*philo->mutex) * (philo->np));
	while (++i < philo->np)
		pthread_mutex_init(&philo->mutex[i], NULL);
	// init_fork(philo);
	return (true);
}

bool	sleep_time(t_philo *philo ,int	time_to)
{
	struct timeval	t;
	long			time_stamp;
	long			finish_time;
	
	finish_time = 0;
	time_stamp = 0;
	gettimeofday(&t, NULL);
	time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	finish_time = time_stamp + (time_to / 1000);
	long double tmp = finish_time - time_stamp; 
	printf("finish_time : %ld\n", finish_time);
	// printf("time_stamp : %ld\n", time_stamp);
	// printf("time_stamp - finish_stamp : %Lf\n", tmp);
	int	i;

	i = 0;
	while (time_stamp < finish_time)
	{
		gettimeofday(&t, NULL);
		time_stamp = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		usleep(10);
		i += 10;
		// philo->ttd -= 10;
		// if (philo->ttd == 0)
		// 	return (false);
	}
	printf("i : %d\n", i);
	printf("time_stamp : %ld\n", time_stamp);
	printf("ttd : %d\n", philo->ttd);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo			philo;

	if (!init_philo(argc, argv, &philo))
		return (printf("Invalid arguments\n"));
	struct timeval	t;
	
	// printf("OWN SLEEP\n");
	gettimeofday(&t, NULL);
	// printf("%ld\n", (t.tv_sec * 1000) + (t.tv_usec / 1000));
	if (!sleep_time(&philo, philo.tts))
		printf("philo is died\n");
	gettimeofday(&t, NULL);
	// printf("%ld\n", (t.tv_sec * 1000) + (t.tv_usec / 1000));

	// printf("\nAPPROVED SLEEP\n");
	// gettimeofday(&t, NULL);
	// printf("%ld\n", (t.tv_sec * 1000) + (t.tv_usec / 1000));
	// usleep(philo.tts);
	// gettimeofday(&t, NULL);
	// printf("%ld\n", (t.tv_sec * 1000) + (t.tv_usec / 1000));

	// if (!init_thread(&philo))
	// 	return (printf("pthread_create encountered an error\n"));
}