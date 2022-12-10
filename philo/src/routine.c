/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:25:23 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/10 19:09:20 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo philo, int state)
{
	struct timeval	t;
	const char	*state_arr[LENGHT] = {
		"has taken a fork\n",
		"is eating\n",
		"is thinking\n",
		"is sleeping\n"
	};
	
	gettimeofday(&t, NULL);
	printf("%ld %d %s", (t.tv_sec * 1000) + (t.tv_usec / 1000),
		philo.id, (char *)state_arr[state]);
}

static void	print_state_fork(t_philo philo, char c)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	printf("%ld %c_FORK_UNLOCKED_BY : %d\n", (t.tv_sec * 1000) + (t.tv_usec / 1000), c, philo.id);
}

static void	print_info(t_philo philo, int r_pos_fork, int l_pos_fork)
{
	printf("ID_PHILO : %d\t", philo.id);
	printf("l_pos : %d\tstate : %d\n", l_pos_fork, philo.fork[l_pos_fork]);
	printf("r_pos : %d\tstate : %d\n\n", r_pos_fork, philo.fork[r_pos_fork]);
	usleep(1000000);
}

void	__eat(t_philo *philo)
{
	int	r_pos_fork;
	int	l_pos_fork;
	int	i;

	i = -1;
	//	Set pos fork
	l_pos_fork = philo->id - 1;
	if (philo->id == 1)
		r_pos_fork = philo->np - 1;
	else
		r_pos_fork = philo->id - 2;
	// print_info(*philo, r_pos_fork, l_pos_fork);
	//	If we lock mutex or if we train another time
	// printf("l_pos_fork : %d\tr_pos_fork : %d\tphilo_id : %d\n", l_pos_fork, r_pos_fork, philo->id);
	pthread_mutex_lock(&philo->mutex[l_pos_fork]);
	//	Lock the fork
	print_state(*philo, FORK);
	// printf("l_pos_fork : %d\n", l_pos_fork);
	pthread_mutex_lock(&philo->mutex[r_pos_fork]);

	//	All prerequisite are respected
	//	Lock the fork
	print_state(*philo, FORK);
	// printf("r_pos_fork : %d\n", r_pos_fork);
	print_state(*philo, EAT);
	usleep(philo->tte);
	
	pthread_mutex_unlock(&philo->mutex[l_pos_fork]);
	// print_state_fork(*philo, 'L');
	pthread_mutex_unlock(&philo->mutex[r_pos_fork]);
	// // print_state_fork(*philo, 'R');
	__sleep(philo);
}

void	__think(t_philo *philo)
{
	print_state(*philo, THINK);
	// usleep(1000);
}

void	__sleep(t_philo *philo)
{
	print_state(*philo, SLEEP);
	usleep(philo->tts);
	__think(philo);
}
