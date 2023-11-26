/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:52:47 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/26 10:34:59 by pbalbino         ###   ########.fr       */
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
	init_delay(table);
	while (TRUE)
	{
		if (check_simulation_time(table) == TRUE
			|| check_simulation_meals(table) == TRUE)
			return (NULL);
		usleep(1500);
	}
	return (NULL);
}

int	ft_start_philo(t_config *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->wait_init);
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo[i]->thread, NULL,
				&philosopher, table->philo[i]) != 0)
		{
			printf("Error while initializing the simulation\n");
			ft_free_resources(table);
			return (FALSE);
		}
		i++;
		usleep(1000);
	}
	table->time_start = current_time_in_ms();
	pthread_mutex_unlock(&table->wait_init);
	return (TRUE);
}

int	init_simulation(t_config *table)
{
	int	currentcount;

	currentcount = 0;
	if (ft_start_philo(table) == FALSE)
		return (FALSE);
	pthread_mutex_lock(&table->philo_ready_count_mutex);
	currentcount = table->philo_count;
	pthread_mutex_unlock(&table->philo_ready_count_mutex);
	while (currentcount != table->philo_count)
	{
		pthread_mutex_lock(&table->philo_ready_count_mutex);
		currentcount = table->philo_ready_count;
		pthread_mutex_unlock(&table->philo_ready_count_mutex);
		usleep(1000);
	}
	usleep (table->philo_count * 100);
	if (table->philo_count > 1)
		if (pthread_create(&table->check_thread, NULL, &ft_check, table) != 0)
			return (FALSE);
	return (TRUE);
}

int	check_simulation_meals(t_config *table)
{
	int	i;
	int	meals_eaten;

	i = 0;
	meals_eaten = 0;
	if (table->eat_times == -1)
		return (FALSE);
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philo[i]->nb_and_time_meal);
		meals_eaten = meals_eaten + table->philo[i]->eat_count;
		pthread_mutex_unlock(&table->philo[i]->nb_and_time_meal);
		i++;
	}
	if (meals_eaten >= table->philo_count * table->eat_times)
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
	int		i;
	time_t	meal_time;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philo[i]->nb_and_time_meal);
		meal_time = table->philo[i]->last_eat;
		if (current_time_in_ms() - meal_time >= table->time_to_die)
		{
			state_message(table->philo[i], "died");
			pthread_mutex_lock(&table->stop_simulation_mutex);
			table->stop_simulation = TRUE;
			pthread_mutex_unlock(&table->stop_simulation_mutex);
			pthread_mutex_unlock(&table->philo[i]->nb_and_time_meal);
			return (TRUE);
		}
		pthread_mutex_unlock(&table->philo[i]->nb_and_time_meal);
		i++;
	}
	return (FALSE);
}

/*
line 34: tempo de espera para rodar o check, se for mto rapido impacta o philo

line 81: Criacao do checker.

line 86 ft_check_simulations meals: verificar se o nr de refeicoes foi atingido
ou se morreu

line 102: if (meals_eaten >= table->philo_count * table->eat_times)
	 >= eh apenas uma garantia extra caso algum coma a mais

line 127 / 128:
			pthread_mutex_unlock(&table->stop_simulation_mutex);
			pthread_mutex_unlock(&table->philo[i]->nb_and_time_meal);
			>> precisa dar unlock aqui tb para nao dar deadlock,
			caso contrario retonara true e ficara locked.



*/