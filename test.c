/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:45:13 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/09 12:29:08 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct	s_data
{
	char			character;
	int				count;
	pthread_mutex_t	mutex;
}			t_data;

void	*job(void *data_params)
{
	t_data		*data;
	int			i;

	i = 0;
	data = (t_data*)data_params;
	while (i < data->count)
	{
		printf("%c\n", data->character);
		i++;
	}
	return (NULL);
}

void	*thread_function(void *arg)
{
	t_data *data_cp;

	data_cp = (t_data*)arg;
	pthread_mutex_lock(&data_cp->mutex);
	if (data_cp->count)
		printf("Hello  \t i : %d\n", data_cp->count);
	else
		printf("Goodbye\t i : %d\n", data_cp->count);
	data_cp->count--;
	pthread_mutex_unlock(&data_cp->mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_id[3];
	t_data		data;
	struct timeval	start, end;
	int			i;
	

	// gettimeofday(&start, NULL);
	// printf("%ld 1 has taken a fork\n", (start.tv_sec * 1000) + (start.tv_usec / 1000));
	// usleep(1000);
	// gettimeofday(&start, NULL);
	// printf("%ld 1 has taken a fork\n", (start.tv_sec * 1000) + (start.tv_usec / 1000));
	// // gettimeofday(&start, NULL);
	// for (int i = 0; i < 1e8; i++){
	// }
	// gettimeofday(&end, NULL);
	// printf("Time taken to count to 10^5 is : %ld micro seconds\n",
    // ((end.tv_sec * 1000000 + end.tv_usec) -
    // (start.tv_sec * 1000000 + start.tv_usec)));

	// printf("Time taken to count to 10^5 is : %ld micro seconds\n",
    // ((end.tv_usec) -
    // (start.tv_usec)));

	// printf("end.tv_usec : %ld\n", end.tv_usec);
	// printf("start.tv_usec : %ld\n", start.tv_usec);
	// pthread_mutex_init(&data.mutex, NULL);
	// data.character = 'W';
	// data.count = 1;
	// i = -1;
	// while (++i < 3)
	// 	pthread_create(&thread_id[i], NULL, &thread_function, &data);
	// i = -1;
	// while (++i < 3)
	// 	pthread_join(thread_id[i], NULL);
	// printf("FINISH !\n");
}
