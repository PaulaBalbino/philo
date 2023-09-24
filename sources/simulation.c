/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:52:47 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/24 11:22:22 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_simulation(t_config *table)
{
	unsigned int i;


	i = 0;
	while (i < table->philo_count)
	{
		if(pthread_create(&table->philo[i].thread, NULL, &philosopher,
			&table->philo[i]) != 0)
			return (false);
		i++;
	}



}