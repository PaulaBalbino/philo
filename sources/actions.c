/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:06:39 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/30 16:16:30 by pbalbino         ###   ########.fr       */
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
// eh possivel criar o if dentro do mutex, porem nao eh o recomendado. qto menos tempo ficar travado o mutex melhor.

}

void	*ft_one_philo(t_philo *philo)
{
	state_message(philo, "has taken a fork");
	usleep(philo->config->time_to_die);
	state_message(philo, "died");
	return (0);
}


void	*philosopher(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	pthread_mutex_lock(&philo->nb_and_time_meal);
	philo->last_eat = philo->config->time_start;
	pthread_mutex_unlock(&philo->nb_and_time_meal);
	//eh realmente necessario criar um delay para iniciar as threads?
	if (philo->config->time_to_die == 0) // nao ha tempo para executar as acoes
		return (0);
	if (philo->config->philo_count == 1)
		return(ft_one_philo(philo));
	else if (philo->philo_nb % 2 == 0) // philos pares
		//ft_think(philo, TRUE);
	while (check_simulation(philo->config) == FALSE)
	{
		usleep(100000);
		//ft_eat_sleep(philo);
		//ft_think(philo, FALSE);
	}
	return (0);
}

/*
prototipo do pthread create:
int
pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg);

por isso que eh void * e recebe (void *)

*/