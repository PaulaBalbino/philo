/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:57:16 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/24 16:50:13 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	//verificar ac e av
	//return (0);
	t_config	table;

	if (set_table(&table, ac, av) == false)
	{
		//TODO mensagem
		return (0);
	}
	if (init_simulation(&table) == false)
	{
		//TODO mensagem
		return (0);
	}
	//check_simulation(&table);




}
