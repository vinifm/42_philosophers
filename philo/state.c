/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:09:46 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/18 20:00:32 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	update_state(int new_state, t_philo *philo, size_t current_time)
{
	pthread_mutex_lock(&philo->state_mtx);
	philo->state_start = current_time;
	philo->state = new_state;
	// print state here inside mutex?
	pthread_mutex_unlock(&philo->state_mtx);
	if (new_state == SLEEPING)
	{
		// pthread_mutex_lock(&philo->meals_mtx);
		philo->meals_eaten++;
		// pthread_mutex_unlock(&philo->meals_mtx);
	}
	return (0);
}

int	done_eating(t_philo *philo, size_t current_time)
{
	if (philo->state == EATING) 
		// mutex? 
		return ((current_time - philo->state_start) >= philo->time_to_eat);
	return (0);	
}

int	done_sleeping(t_philo *philo, size_t current_time)
{
	if (philo->state == SLEEPING)
		return ((current_time - philo->state_start) >= philo->time_to_sleep);
	return (0); 
}

size_t	get_current_time(size_t start_time)
{
	struct	timeval tv;

	gettimeofday(&tv, NULL);
	 = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int	check_and_update_state(t_philo *philo)
{
	size_t	current_time;

	current_time = get_current_time(philo->start_time);
	// check if should die
	if (philo->state == THINKING)
	{
		if (has_both_forks(philo))
			return(update_state(EATING, philo, current_time));
		else
			return(pick_forks(philo));
	}
	if (done_eating(philo, current_time))
	{
		drop_forks(philo);
		return(update_state(SLEEPING, philo, current_time));
	}
	if (done_sleeping(philo, current_time))
		return(update_state(THINKING, philo, current_time));
}

//	Checks if the philosopher has not died nor reached the meals goal
int	alive_and_hungry(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mtx);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->state_mtx);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->state_mtx);
	if (is_satisfied(philo))
		return (FALSE);
	return (TRUE);
}

// Checks, updates and prints philosopher state while it's alive and hungry
void	*state_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (alive_and_hungry(philo))
	{
		check_and_update_state(philo);
		// usleep?
	}
	// print state
	return (0);
}
