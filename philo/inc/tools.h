/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:36:20 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/15 23:43:41 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <stdbool.h>
# include <pthread.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define INT_OVERFLOW 2147483648

typedef enum e_state {
	FORK,
	EAT,
	THINK,
	SLEEP,
	LENGHT
}	t_state;

typedef struct s_philo t_philo;

typedef struct s_shared_mem
{
	int		test;
	t_philo *philo;
}			t_shared_mem;

typedef struct s_philo
{
	int				np;
	int				ttd;
	int				tte;
	int				tts;
	int				pms;
	int				id;
	int				test;
	long			death_time;
	int				*fork;
	t_shared_mem	shared_mem;
	pthread_t		thread_id[10];
	pthread_mutex_t	*mutex;
}		t_philo;		


#endif