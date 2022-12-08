/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:36:20 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/08 19:49:44 by mmeguedm         ###   ########.fr       */
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

typedef struct s_philo
{
	int				np;
	int				ttd;
	int				tte;
	int				tts;
	int				pms;
	int				id;
	int				*fork;
	pthread_t		*thread_id;
	pthread_mutex_t	*mutex;
}		t_philo;		

#endif