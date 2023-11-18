/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:06:39 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/18 13:13:14 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	check_simulation(t_config *table);

int	philo_sleep(t_config *table, time_t sleep_time)
{
	time_t	wake_up;
	wake_up = current_time_in_ms() + sleep_time;
//	printf("while %ld < %ld\n", current_time_in_ms(), wake_up);
	while (current_time_in_ms() < wake_up)
	{
		if (check_simulation(table) == FALSE){
			//printf("\nthe end fim");
			return SIMULATION_END;
		}
		usleep(100);
	}
	return SIMULATION_CONTINUE;
}

int ft_sleep(t_philo *philo)
{
	state_message(philo, "is sleeping");
	//printf("\n philo sleep for %ld ms", philo->config->time_to_sleep);
	return philo_sleep(philo->config, philo->config->time_to_sleep);
}

int ft_think(t_philo *philo)
{
	time_t	think;

	pthread_mutex_lock(&philo->nb_and_time_meal);
	think = (philo->config->time_to_die - (current_time_in_ms()
		-philo->last_eat) - philo->config->time_to_eat) / 2;

	pthread_mutex_unlock(&philo->nb_and_time_meal);
	//printf("\n time to die: %ld, current: %ld, last eat: %ld \n", philo->config->time_to_die, current_time_in_ms(), philo->last_eat);
//	printf("\n think: %ld\n", think);
	state_message(philo, "is thinking");
	return philo_sleep(philo->config, think);
}

//TODO ta igual - mudar
int ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->fork_area[philo->left_fork]);
	if (check_simulation(philo->config) == FALSE)
	{
		pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
		return SIMULATION_END;
	}
	state_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->config->fork_area[philo->right_fork]);
	if (check_simulation(philo->config) == FALSE)
	{
		pthread_mutex_unlock(&philo->config->fork_area[philo->right_fork]);
		return SIMULATION_END;
	}
	state_message(philo, "has taken a fork");
	state_message(philo, "is eating");
	pthread_mutex_lock(&philo->nb_and_time_meal);
	philo->last_eat = current_time_in_ms();
	pthread_mutex_unlock(&philo->nb_and_time_meal);
	if(philo_sleep(philo->config, philo->config->time_to_eat) != SIMULATION_CONTINUE){
		pthread_mutex_unlock(&philo->config->fork_area[philo->right_fork]);
		pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
		return SIMULATION_END;
	}
	if (check_simulation(philo->config) == TRUE)
	{
		pthread_mutex_lock(&philo->nb_and_time_meal);
		philo->eat_count = philo->eat_count + 1;
		pthread_mutex_unlock(&philo->nb_and_time_meal);
	}
	pthread_mutex_unlock(&philo->config->fork_area[philo->right_fork]);
	pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
	return SIMULATION_CONTINUE;
}

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
	pthread_mutex_lock(&philo->config->fork_area[philo->left_fork]);
	state_message(philo, "has taken a fork");
	philo_sleep(philo->config, philo->config->time_to_die);
	pthread_mutex_unlock(&philo->config->fork_area[philo->left_fork]);
	state_message(philo, "died");
	return (0);
}

void	init_delay(t_config *table) // rever depois
{
	pthread_mutex_lock(&table->wait_init);
	pthread_mutex_unlock(&table->wait_init);
}

void	*philosopher(void *info)
{
	t_philo	*philo;
	philo = (t_philo *)info;
	//printf("\nphilosopher born %d", philo->philo_nb); //TODO tem que ver a questao do tempo, se tirar o printf nao funciona
	//printf("\n philo %d created - waiting", philo->philo_nb);
	init_delay(philo->config); //Block until all philospher are ready

	pthread_mutex_lock(&philo->nb_and_time_meal);
	philo->last_eat = philo->config->time_start;
	pthread_mutex_unlock(&philo->nb_and_time_meal);

//	pthread_mutex_lock(&philo->config->philo_ready_count_mutex);
	philo->config->philo_ready_count++;
//	pthread_mutex_unlock(&philo->config->philo_ready_count_mutex);


	//printf("\n philo %d created - released last_eat %ld\n", philo->philo_nb, philo->last_eat);
	if (philo->config->time_to_die == 0){
		//printf("\n philo %d - time to die 0 - Dying!", philo->philo_nb);
		return (0);
	}
	if (philo->config->philo_count == 1)
		return(ft_one_philo(philo));
	else if (philo->philo_nb % 2 == 0) // philos pares
		ft_think(philo);
	while (check_simulation(philo->config) == TRUE)
	{
		//printf("\n philo %d - Idle", philo->philo_nb);
		if(ft_eat(philo) == SIMULATION_END)
			break;
		if(ft_sleep(philo) == SIMULATION_END)
			break;
		if(ft_think(philo) == SIMULATION_END)
			break;
		//ft_eat_sleep(philo);
		//ft_think(philo, FALSE);
	}
	//printf("\n philo %d - End!", philo->philo_nb);
	return (0);
}

/*
prototipo do pthread create:
int
pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg);

por isso que eh void * e recebe (void *)

*/