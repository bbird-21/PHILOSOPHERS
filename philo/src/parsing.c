/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:34:40 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/07 18:12:40 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_allowed_string(char *str)
{
	int	i;

	i = 0;
	if (*str == 0)
		return (false);
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (false);
		i++;
	}
	return (true);
}

int	parse_args(char *str)
{
	long	res;

	res = -1;
	if (!(ft_allowed_string(str)))
		return (-1);
	res = ft_atoi(str);
	if (res == INT_OVERFLOW)
		return (-1);
	return (res);
}