/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:24 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/18 20:00:51 by viferrei         ###   ########.fr       */
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
	DEAD
}			t_state;

/*
// STRUCTS
*/
typedef struct s_fork
{
	pthread_mutex_t	fork_mtx;
	int				locked;
}				t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				nb;

	// create shared data struct
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	size_t			start_time;
	pthread_mutex_t	state_mtx;
	
	int				meals_eaten;
	pthread_mutex_t	meals_mtx;
	size_t			state_start;
	t_state			state;
	t_fork			*right_fork;
	t_fork			*left_fork;
}				t_philo;

/*
// FUNCTIONS
*/
// Input handling
int		invalid_args(int argc, char *argv[]);
int		ft_atoi(const char *str);
double	ft_atod(const char *str);
int		ft_isdigit(int c);

// state.c
void	*state_loop(void *arg);

/*
// DELETE BEFORE SUBMISSION
*/
void	test_philos(t_philo **philo);

#endif
