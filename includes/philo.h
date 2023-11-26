/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:59:13 by pbalbino          #+#    #+#             */
/*   Updated: 2023/11/26 10:37:11 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0
# define NOT_SET -1
# define MAXINT 2147483647
# define MININT -2147483648
# define SIMULATION_CONTINUE 0
# define SIMULATION_END 1

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
	time_t			last_eat;
	t_config		*config;
	pthread_mutex_t	nb_and_time_meal;
}	t_philo;

typedef struct s_config
{
	int				philo_count;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				eat_times;
	time_t			time_start;
	int				stop_simulation;
	int				philo_ready_count;
	pthread_mutex_t	*fork_area;
	pthread_mutex_t	locked_printf;
	pthread_mutex_t	stop_simulation_mutex;
	pthread_mutex_t	wait_init;
	pthread_mutex_t	philo_ready_count_mutex;
	t_philo			**philo;
	pthread_t		check_thread;
}	t_config;

/* Function Prototypes */

void	init_delay(t_config *table);
int		set_table(t_config *table, int ac, char **av);
int		ft_atoi(char *str);
int		init_simulation(t_config *table);
void	*philosopher(void *info);
time_t	current_time_in_ms(void);
int		numeric_input(int ac, char **av, t_config *table);
void	state_message(t_philo *philo, char *str);
void	ft_free_resources(t_config *table);
int		philo_sleep(t_config *table, time_t sleep_time);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_eat(t_philo *philo);
int		check_simulation(t_config *table);

#endif