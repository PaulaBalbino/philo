/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:58:55 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/20 17:27:17 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_numeric_string(char *str)
{
	int	i;
	int	nb_pos;

	nb_pos = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] == 32 || (str[i] > 9 && str[i] < 13))
		i++;
	nb_pos = i;
	while (str[i] != 0)
	{
		if ((str[i] == '+' || str[i] == '-') && i != nb_pos)
			return (-1);
		if (str[i] == '+')
			i++;
		if (str[i] == '-')
			return (-1);
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	numeric_input(int ac, char **av, t_config *table)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_valid_numeric_string(av[i]) == -1)
		{
			printf("At least one argument is invalid!\n");
			free(table);
			return (-1);
		}
		i++;
	}
	return (0);
}
