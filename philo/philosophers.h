/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:24 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/13 19:38:48 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define EINVAL		22	// Invalid argument
# define INT_MAX 	2147483647

/*
// STRUCTS
*/
typedef struct s_philo
{
	int	nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_to_eat;
	int	state;
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
