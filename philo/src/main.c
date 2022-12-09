/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:16:55 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/09 19:36:36 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Gerer le temps gettimeos addition des deux elements de la structure
//	Afficher les messages a l'inifi sans gerer la mort

static void	init_fork(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->np)
		philo->fork[i] = 1;
}

static bool	init_philo(int argc, char **argv, t_philo *philo)
{
	int	i;

	i = -1;
	philo->np = parse_args(argv[1]);
	philo->ttd = parse_args(argv[2]);
	philo->tte = parse_args(argv[3]);
	philo->tts = parse_args(argv[4]);
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
	init_fork(philo);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo			philo;

	if (!init_philo(argc, argv, &philo))
		return (printf("Invalid arguments\n"));
	if (!init_thread(&philo))
		return (printf("pthread_create encountered an error\n"));
}