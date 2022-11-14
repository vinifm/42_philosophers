/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:24 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/14 18:01:26 by viferrei         ###   ########.fr       */
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

/*
// STRUCTS
*/
typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				locked;
}				t_fork;

typedef struct s_philo
{
	int	nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_to_eat;
	int	state;
	t_fork	*right_fork;
	t_fork	*left_fork;
}				t_philo;

/*
// FUNCTIONS
*/
// Input handling
int		invalid_args(int argc, char *argv[]);
int		ft_atoi(const char *str);
double	ft_atod(const char *str);
int		ft_isdigit(int c);

#endif
