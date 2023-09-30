/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:57:16 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/30 11:58:44 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_destroy(t_config *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->fork_area[i]);
		pthread_mutex_destroy(&table->philo[i]->nb_and_time_meal);
		i++;
	}
	pthread_mutex_destroy(&table->locked_printf);
	pthread_mutex_destroy(&table->stop_simulation_mutex);
}

void wait_threads(t_config *table)
{
	int	i;

	i = 0;
	while(i < table->philo_count)
	{
		pthread_join(table->philo[i]->thread, NULL);
		i++;
	}
	if (table->philo_count > 1)
		pthread_join(table->check_thread, NULL);
	ft_mutex_destroy(table);
}

/*
 The pthread_join() function suspends execution of the calling thread
     until the target thread terminates unless the target thread has already
     terminated.
	 */

int	main(int ac, char **av)
{
	t_config	table;

	if (ac < 5 || ac > 6)
	{
		printf("Check number of arguments\n");
		return (0);
	}
	if (numeric_input(ac, av) == -1)
		return (0);
	if (set_table(&table, ac, av) == FALSE)
		return (0);
	if (init_simulation(&table) == FALSE)
	{
		printf("Error while initializing the simulation\n");
		return (0);
	}
	wait_threads(&table);
	if (table.fork_area != NULL)
		free(table.fork_area);
	free(table.philo);
}
