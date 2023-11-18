/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:58:55 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/18 11:42:22 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_numeric_string(char *str)
{
	int	i;
	int	signal;

	signal = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	if (str[0] == '-' || str[0] == '+')
	{
		i++;
		signal = 1;
	}
	while (str[i] != 0)
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	if (signal == 1)
		return (-1);
	return (0);
}

int	numeric_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_valid_numeric_string(av[i]) == -1)
		{
			printf("At least one argument is invalid!\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
