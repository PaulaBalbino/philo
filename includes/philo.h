/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:59:13 by pbalbino          #+#    #+#             */
/*   Updated: 2023/09/30 12:46:58 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0
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

typedef struct s_config	t_config;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_nb;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	time_t				last_eat;
	t_config		*config;
	pthread_mutex_t	nb_and_time_meal;
	//meal time lock ?
}	t_philo;

typedef struct s_config
{
	int				philo_count;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int				eat_times;
	time_t				time_start;
	int				stop_simulation;
	pthread_mutex_t	*fork_area;
	pthread_mutex_t	locked_printf;
	pthread_mutex_t	stop_simulation_mutex;
	t_philo			**philo;
	pthread_t		check_thread; // pthread_t eh o identificador de uma thread, vide linha 41
	//int				end_simulation;
	//pthread_mutex_t	*end_simulation_mutex;

}	t_config;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

int		set_table(t_config *table, int ac, char **av);
int		ft_atoi(char *str);
int		init_simulation(t_config *table);
void	*philosopher(void *info);
time_t		current_time_in_ms(void);
int		numeric_input(int ac, char **av);
void state_message(t_philo *philo, char *str);

#endif