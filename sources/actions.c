/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:06:39 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/26 19:08:35 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation(t_config *table);

int	philo_delay(t_config *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = current_time_in_ms() + sleep_time;
	while (current_time_in_ms() < wake_up)
	{
		if (check_simulation(table) == FALSE)
			return (SIMULATION_END);
		usleep(100);
	}
	return (SIMULATION_CONTINUE);
}

int	ft_sleep(t_philo *philo)
{
	state_message(philo, "is sleeping");
	return (philo_delay(philo->config, philo->config->time_to_sleep));
}

int	ft_think(t_philo *philo)
{
	time_t	think;

	pthread_mutex_lock(&philo->nb_and_time_meal);
	think = (philo->config->time_to_die - (current_time_in_ms()
				-philo->last_eat) - philo->config->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->nb_and_time_meal);
	state_message(philo, "is thinking");
	return (philo_delay(philo->config, think));
}

int	ft_start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->fork_area[philo->left_fork]);
	if (check_simulation(philo->config) == FALSE)
	{
		pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
		return (SIMULATION_END);
	}
	philo->config->forks[philo->left_fork] = UP;
	state_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->config->fork_area[philo->right_fork]);
	if (check_simulation(philo->config) == FALSE)
	{
		philo->config->forks[philo->left_fork] = DOWN;
		pthread_mutex_unlock(&philo->config->fork_area[philo->right_fork]);
		pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
		return (SIMULATION_END);
	}
	philo->config->forks[philo->right_fork] = UP;
	state_message(philo, "has taken a fork");
	state_message(philo, "is eating");
	return (SIMULATION_CONTINUE);
}

int	ft_eat(t_philo *philo)
{
	if (ft_start_eating(philo) == SIMULATION_END)
		return (SIMULATION_END);
	pthread_mutex_lock(&philo->nb_and_time_meal);
	philo->last_eat = current_time_in_ms();
	pthread_mutex_unlock(&philo->nb_and_time_meal);
	if (philo_delay(philo->config, philo->config->time_to_eat)
		!= SIMULATION_CONTINUE)
	{
		philo->config->forks[philo->left_fork] = DOWN;
		philo->config->forks[philo->right_fork] = DOWN;
		pthread_mutex_unlock(&philo->config->fork_area[philo->right_fork]);
		pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
		return (SIMULATION_END);
	}
	if (check_simulation(philo->config) == TRUE)
	{
		pthread_mutex_lock(&philo->nb_and_time_meal);
		philo->eat_count = philo->eat_count + 1;
		pthread_mutex_unlock(&philo->nb_and_time_meal);
	}
	philo->config->forks[philo->left_fork] = DOWN;
	philo->config->forks[philo->right_fork] = DOWN;
	pthread_mutex_unlock(&philo->config->fork_area[philo->right_fork]);
	pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
	return (SIMULATION_CONTINUE);
}
