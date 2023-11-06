/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:38:39 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/05 10:42:54 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	t_philo	**init_philosophers(t_config *table);

static	pthread_mutex_t	*set_mutex_forks(t_config *table)
{
	pthread_mutex_t	*mutex_array;
	int				i;

	mutex_array = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (mutex_array == 0)
		return (NULL);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&mutex_array[i], NULL) != 0)
		{
			free (mutex_array);
			return (0);
		}
	i++;
	}
	return (mutex_array);
}

/*
pthread_mutex_init:
If successful, pthread_mutex_init() will return zero and put the new mutex id into mutex,
otherwise an error number will be returned to indicate the error.

ZERO SIGNIFICA QUE DEU CERTO */

int	set_table(t_config *table, int ac, char **av)
{
	table->philo_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->eat_times = ft_atoi(av[5]);
	else
		table->eat_times = NOT_SET;
	table->philo = init_philosophers(table);
	if (table->philo == 0)
	{
		printf("Error while setting the table\n");
		return (FALSE);
	}
	table->fork_area = set_mutex_forks(table);
	if (table->fork_area == 0)
	{
		printf("Error while setting the table\n");
		return (FALSE);
	}
	if (pthread_mutex_init(&table->wait_init, NULL) != 0)
			return (FALSE);
	//if (pthread_mutex_init(&table->philo_ready_count_mutex, NULL) != 0)
	//		return (FALSE);
	return (TRUE);
}

static void	set_forks(t_philo *philo)
{
	if (philo->philo_nb % 2 == 0)
	{
		philo->left_fork = philo->philo_nb;
		if (philo->philo_nb == philo->config->philo_count - 1)
			philo->right_fork = 0; // fork do primeiro philo (philo zero);
		else
			philo->right_fork = philo->philo_nb + 1;
	}
	else
	{
		philo->right_fork = philo->philo_nb;
		if (philo->philo_nb == philo->config->philo_count - 1)
			philo->left_fork = 0; // fork do primeiro philo (philo zero);
		else
			philo->left_fork = philo->philo_nb + 1;
	}
}

static	t_philo	**init_philosophers(t_config *table)
{
	t_philo	**philo;
	int		i;

	philo = malloc(sizeof( t_philo *) * table->philo_count);
	if (philo == 0)
		return (0);
	i = 0;
	while (i < table->philo_count)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		philo[i]->config = table;
		philo[i]->philo_nb = i;
		philo[i]->eat_count = 0;
		set_forks(philo[i]);
		if (pthread_mutex_init(&philo[i]->nb_and_time_meal, NULL) != 0)
			return (FALSE);
		i++;
	}
	return (philo);
}
