/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:57:16 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/18 16:47:00 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_philos(t_config *table)
{
	int	i;

	i = table->philo_count - 1;
	while ( i >= 0)
	{
		free(table->philo[i]);
		i--;
	}
}

void	ft_free_resources(t_config *table)
{
	if (table->fork_area != NULL)
		free(table->fork_area);
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
}

void wait_threads(t_config *table)
{
	int	i;

	i = 0;
	while(i < table->philo_count)
	{
		//printf("\nphilo %d waiting it to finish or die", i + 1);
		pthread_join(table->philo[i]->thread, NULL);
		//printf("\nphilo %d just finished", i + 1);
		i++;
	}
	//printf("\nphilo waiting check thread to finish");
	if (table->philo_count > 1)
		pthread_join(table->check_thread, NULL);
	//printf("\nphilo check thread finished");
	ft_mutex_destroy(table);
}

/*
 The pthread_join() function suspends execution of the calling thread
     until the target thread terminates unless the target thread has already
     terminated.
	 */

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

	if (set_table(table, ac, av) == FALSE)
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
