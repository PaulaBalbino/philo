/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:06:39 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/24 15:30:01 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"





void	*philosopher(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	while(1==1){
	printf("oi %d", philo->philo_nb);
	}
	return (NULL);
	philo->last_eat = philo->config->time_start;
}

/*
prototipo do pthread create:
int
pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg);

por isso que eh void * e recebe (void *)

*/