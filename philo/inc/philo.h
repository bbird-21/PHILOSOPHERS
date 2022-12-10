/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:35:44 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/10 18:06:31 by mmeguedm         ###   ########.fr       */
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
void	print_state(t_philo philo, int state);
bool	init_thread(t_philo *philo);

/*	<parsing.c>	*/
int		parse_args(char *str);
/*	<routine.c	*/
/*	Required by thread_function in <thread.c> to apply routine*/
void	__eat(t_philo *philo);
void	__think(t_philo *philo);
void	__sleep(t_philo *philo);

#endif