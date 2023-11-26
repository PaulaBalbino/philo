/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:38:39 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/26 17:24:01 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_philosophers(t_config *table);

static	void	set_mutex_forks(t_config *table)
{
	int	i;

	table->fork_area = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (table->fork_area == 0)
		return ;
	table->forks = malloc(sizeof(int) * table->philo_count);
	if (table->forks == 0)
		return ;
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->fork_area[i], NULL) != 0)
		{
			free (table->fork_area);
			return ;
		}
		table->forks[i] = DOWN;
		i++;
	}
}

int	init_table_mutexes(t_config *table)
{
	if (pthread_mutex_init(&table->wait_init, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&table->locked_printf, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&table->stop_simulation_mutex, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&table->philo_ready_count_mutex, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

int	set_table(t_config *table, int ac, char **av)
{
	table->philo_ready_count = 0;
	table->philo_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->eat_times = ft_atoi(av[5]);
	else
		table->eat_times = NOT_SET;
	init_philosophers(table);
	if (table->philo == 0)
	{
		printf("Error while setting the table\n");
		return (FALSE);
	}
	set_mutex_forks(table);
	if (table->fork_area == 0)
	{
		printf("Error while setting the table\n");
		return (FALSE);
	}
	table->stop_simulation = FALSE;
	if (init_table_mutexes(table) == FALSE)
		return (FALSE);
	return (TRUE);
}

static void	set_forks(t_philo *philo)
{
	if (philo->philo_nb % 2 == 0)
	{
		philo->left_fork = philo->philo_nb;
		if (philo->philo_nb == philo->config->philo_count - 1)
			philo->right_fork = 0;
		else
			philo->right_fork = philo->philo_nb + 1;
	}
	else
	{
		philo->right_fork = philo->philo_nb;
		if (philo->philo_nb == philo->config->philo_count - 1)
			philo->left_fork = 0;
		else
			philo->left_fork = philo->philo_nb + 1;
	}
}

static	void	init_philosophers(t_config *table)
{
	int		i;

	table->philo = malloc(sizeof(t_philo *) * table->philo_count);
	if (table->philo == 0)
		return ;
	i = 0;
	while (i < table->philo_count)
	{
		table->philo[i] = malloc(sizeof(t_philo) * 1);
		table->philo[i]->config = table;
		table->philo[i]->philo_nb = i;
		table->philo[i]->eat_count = 0;
		set_forks(table->philo[i]);
		if (pthread_mutex_init(&table->philo[i]->nb_and_time_meal, NULL) != 0)
			return ;
		i++;
	}
}

/*
pthread_mutex_init:
If successful, pthread_mutex_init() will return zero and put the
new mutex id into mutex, otherwise an error number will be returned
to indicate the error.

ZERO SIGNIFICA QUE DEU CERTO

line 84: fork do primeiro philo (philo zero);

line 78: static void set_forks(t_philo *philo)
Dar os garfos para os filosofos pares e impares de forma alternada
previne deadlock;

103: if (pthread_mutex_init(&table->philo[i]->nb_and_time_meal, NULL) != 0)
inicializacao do mutex que vai ser usado para contar o numero de refeicoes e
o horario da ultima refeicao do philo;
*/
