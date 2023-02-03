/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:35:44 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/03 17:18:17 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "tools.h"
# include "utils.h"
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*	<thread.c>	*/
bool	print_state(t_philo *philo, int state);
bool	init_thread(t_philo **arr_philo);

/*	<parsing.c>	*/
int		parse_args(char *str);

/*	<routine.c	*/
long	get_death_time(int	ttd);
bool	sleep_time(int tts, t_philo *philo);

/*	Required by thread_function in <thread.c> to apply routine*/
void	__eat(t_philo *philo);
void	__think(t_philo *philo, int l_pos_fork, int r_pos_fork);
void	__sleep(t_philo *philo, int l_pos_fork, int r_pos_fork);


void	print_philo(t_philo *philo);

#endif
