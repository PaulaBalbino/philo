/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:26:38 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/24 15:44:58 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	current_time_in_ms()
{
	struct timeval	currenttime;
	int				milisec;

	gettimeofday(&currenttime, NULL);
	milisec = currenttime.tv_sec * 1000;
	milisec = (currenttime.tv_usec / 1000) + milisec;
	return (milisec);
}

/*
man gettimeofday

timeval definition:
_STRUCT_TIMEVAL
{
	__darwin_time_t         tv_sec;          seconds since Jan. 1, 1970
	__darwin_suseconds_t    tv_usec;         and microseconds
};

*/

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}