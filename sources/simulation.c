/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:52:47 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/25 14:39:00 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(t_config *table)
{
	int	i;

	table->time_start = current_time_in_ms();
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				&philosopher, &table->philo[i]) != 0)
		{
			printf("Error while initializing the simulation\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/* verificar se o nr de refeicoes foi atingido ou se morreu*/

void	check_simulation(t_config *table)
{
	int	i;
	int	meals_eaten;

	i = 0;
	meals_eaten = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philo[i].nb_and_time_meal);
		meals_eaten = meals_eaten + table->philo[i].eat_count;
		pthread_mutex_unlock(&table->philo[i].nb_and_time_meal);
		i++;
	}
	if (meals_eaten == table->philo_count * table->eat_times)
	{

	}
}
