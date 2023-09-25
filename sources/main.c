/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:57:16 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/25 16:24:24 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_config	table;

	if (ac < 5 || ac > 6)
	{
		printf("Check number of arguments\n");
		return (0);
	}
	if (numeric_input(ac, av) == -1)
		return (0);
	if (set_table(&table, ac, av) == FALSE)
		return (0);
	if (init_simulation(&table) == FALSE)
	{
		printf("Error while initializing the simulation\n");
		return (0);
	}
	//check_simulation(&table);

}
