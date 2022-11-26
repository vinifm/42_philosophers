/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:24 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/26 19:42:19 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE		1
# define FALSE		0
# define EINVAL		22	// Invalid argument
# define INT_MAX 	2147483647

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	SIMULATION_ENDED
}			t_state;

/*
// STRUCTS
*/
typedef struct s_fork
{
	int				locked;
}				t_fork;

// Shared mutexes
typedef struct s_mtx
{
	int				simulation_status;
	pthread_mutex_t	simulation_mtx;
	pthread_mutex_t	state_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	meals_mtx;
	pthread_mutex_t	forks_mtx;
}				t_mtx;

// Individual philosopher struct
typedef struct s_philo
{
	pthread_t		thread;
	int				nb;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				meals_eaten;
	size_t			last_meal_time;
	size_t			start_time;
	size_t			state_start;
	t_state			state;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_mtx			*mtx;
}				t_philo;

/*
// FUNCTIONS
*/
// Input handling
int		invalid_args(int argc, char *argv[]);
int		ft_atoi(const char *str);
double	ft_atod(const char *str);
int		ft_isdigit(int c);

//	state.c
size_t	current_time(void);
void	*state_loop(void *arg);
int		not_hungry(t_philo *philo);

//	state_utils.c
int	is_thinking(t_philo *philo);
int	is_eating(t_philo *philo);
int	is_sleeping(t_philo *philo);
int	is_dead(t_philo *philo);
int	is_simulating(t_philo *philo);

/*
// DELETE BEFORE SUBMISSION
*/
void	test_philos(t_philo **philo);

#endif
