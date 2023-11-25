/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:50:03 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/25 15:15:35 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation(t_config *table)
{
	int	aux;

	pthread_mutex_lock(&table->stop_simulation_mutex);
	aux = table->stop_simulation;
	pthread_mutex_unlock(&table->stop_simulation_mutex);
	if (aux == TRUE)
		return (FALSE);
	else
		return (TRUE);
}

void	*ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->fork_area[philo->left_fork]);
	state_message(philo, "has taken a fork");
	philo_sleep(philo->config, philo->config->time_to_die);
	pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
	state_message(philo, "died");
	return (0);
}

void	init_delay(t_config *table) // TODO rever depois
{
	pthread_mutex_lock(&table->wait_init);
	pthread_mutex_unlock(&table->wait_init);
}

void	*philosopher(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	init_delay(philo->config); //Block until all philospher are ready
	pthread_mutex_lock(&philo->nb_and_time_meal);
	philo->last_eat = philo->config->time_start;
	pthread_mutex_unlock(&philo->nb_and_time_meal);
	pthread_mutex_lock(&philo->config->philo_ready_count_mutex);
	philo->config->philo_ready_count++;
	pthread_mutex_unlock(&philo->config->philo_ready_count_mutex);
	if (philo->config->time_to_die == 0)
		return (0);
	if (philo->config->philo_count == 1)
		return (ft_one_philo(philo));
	else if (philo->philo_nb % 2 == 0) // philos pares
		ft_think(philo);
	while (check_simulation(philo->config) == TRUE)
	{
		if (ft_eat(philo) == SIMULATION_END
			|| ft_sleep(philo) == SIMULATION_END)
			break ;
		if (ft_think(philo) == SIMULATION_END)
			break ;
	}
	return (0);
}
