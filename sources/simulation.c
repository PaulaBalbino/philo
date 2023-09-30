/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:52:47 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/30 16:19:20 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_time(t_config *table);
int	check_simulation_meals(t_config *table);

void	*ft_check(void *input)
{
	t_config	*table;

	table = (t_config *)input;
	if (table->eat_times == 0)
		return (NULL);
	pthread_mutex_lock(&table->stop_simulation_mutex);
	table->stop_simulation = FALSE;
	pthread_mutex_unlock(&table->stop_simulation_mutex);
	while (TRUE)
	{
		if (check_simulation_time(table) == TRUE
			|| check_simulation_meals(table) == TRUE)
			return (NULL);
		usleep(1500); // tempo de espera para rodar o check, se for mto rapido impacta o philo
	}
	return (NULL);
}

int	init_simulation(t_config *table)
{
	int	i;

	table->time_start = current_time_in_ms();
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo[i]->thread, NULL,
				&philosopher, table->philo[i]) != 0)
		{
			printf("Error while initializing the simulation\n");
			return (FALSE);
		}
		i++;
	}
	if (table->philo_count > 1)
	{
		if (pthread_create(&table->check_thread, NULL,
				&ft_check, table) != 0)
		{
			printf("Error while initializing the simulation\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

/* verificar se o nr de refeicoes foi atingido ou se morreu*/

int	check_simulation_meals(t_config *table)
{
	int	i;
	int	meals_eaten;

	i = 0;
	meals_eaten = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philo[i]->nb_and_time_meal);
		meals_eaten = meals_eaten + table->philo[i]->eat_count;
		pthread_mutex_unlock(&table->philo[i]->nb_and_time_meal);
		i++;
	}
	if (meals_eaten >= table->philo_count * table->eat_times) // >= eh apenas uma garantia extra caso algum coma a mais
	{
		pthread_mutex_lock(&table->stop_simulation_mutex);
		table->stop_simulation = TRUE;
		pthread_mutex_unlock(&table->stop_simulation_mutex);
		return (TRUE);
	}
	return (FALSE);
}

int	check_simulation_time(t_config *table)
{
	int	i;
	int	meal_time;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philo[i]->nb_and_time_meal);
		meal_time = table->philo[i]->last_eat;
		if (meal_time >= table->time_to_die + current_time_in_ms())
		{
			pthread_mutex_lock(&table->stop_simulation_mutex);
			table->stop_simulation = TRUE;
			pthread_mutex_unlock(&table->stop_simulation_mutex);
			state_message(table->philo[i], "died");
			pthread_mutex_unlock(&table->philo[i]->nb_and_time_meal); // precisa dar unlock aqui tb para nao dar deadlock, caso contrario retonara true e ficara locked.				return (TRUE);
		}
		pthread_mutex_unlock(&table->philo[i]->nb_and_time_meal);
		i++;
	}
	return (FALSE);
}
