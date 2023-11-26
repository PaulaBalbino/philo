/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:57:16 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/26 17:26:18 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_philos(t_config *table)
{
	int	i;

	i = table->philo_count - 1;
	while (i >= 0)
	{
		free(table->philo[i]);
		i--;
	}
}

void	ft_free_resources(t_config *table)
{
	if (table->fork_area != NULL)
		free(table->fork_area);
	if (table->forks != NULL)
		free(table->forks);
	ft_free_philos(table);
	free(table->philo);
	free(table);
}

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
	pthread_mutex_destroy(&table->philo_ready_count_mutex);
}

void	wait_threads(t_config *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philo[i]->thread, NULL);
		i++;
	}
	if (table->philo_count > 1)
		pthread_join(table->check_thread, NULL);
	ft_mutex_destroy(table);
}

int	main(int ac, char **av)
{
	t_config	*table;

	table = malloc(sizeof(t_config));
	if (table == NULL)
		return (0);
	if (ac < 5 || ac > 6)
	{
		printf("Check number of arguments\n");
		free(table);
		return (0);
	}
	if (numeric_input(ac, av, table) == -1)
		return (0);
	if (set_table(table, ac, av) == FALSE || (table->eat_times == 0))
	{
		ft_free_resources(table);
		return (0);
	}
	if (init_simulation(table) == FALSE)
		return (0);
	wait_threads(table);
	ft_free_resources(table);
	return (0);
}

/*
 The pthread_join() function suspends execution of the calling thread
     until the target thread terminates unless the target thread has already
     terminated.
	 */