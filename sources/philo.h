/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:59:13 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/24 11:21:34 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# define true 1
# define false 0
# define NOT_SET -1
# define MAXINT 2147483647
# define MININT -2147483648

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_state
{
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED = 4,
}	t_state;

typedef struct	s_config	t_config;

typedef struct s_philo
{
	pthread_t	thread;
	int			philo_nb;
	int			eat_count;
	int			left_fork;
	int			right_fork;
	int			last_eat;
	t_config	*config;
	//meal time lock ?
}	t_philo;

typedef struct s_config
{
	//time_t			time_start;
	//const eh para travar os numeros que nao devem mudar, sao constantes;
	int philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_times;
	pthread_mutex_t	*fork_area;
	t_philo		*philo; //analisar se basta um *
}	t_config;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

int set_table(t_config *table, int ac, char **av);
int	ft_atoi(char *str);
int init_simulation(t_config *table);
void	*philosopher(void *info);

#endif