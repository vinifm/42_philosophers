/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:09:46 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/20 20:01:45 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	current_time(void)
{
	static size_t	initial_time;
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	if (!initial_time)
		initial_time = time;
	return (time - initial_time);
}

int	print_state(t_philo *philo)
{
	char *state_str;

	if (philo->state == EATING)
		state_str = "is eating";
	else if (philo->state == SLEEPING)
		state_str = "is sleeping";
	else if (philo->state == THINKING)
		state_str = "is thinking";
	else
	 	state_str = "died";
	printf("%zu %d %s", current_time(), philo->nb, state_str);
	return (0);


int	update_state(int new_state, t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	philo->state_start = current_time();
	philo->state = new_state;
	// print state here inside mutex?
	print_state(philo);
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	if (new_state == SLEEPING)
	{
		pthread_mutex_lock(&philo->mtx->meals_mtx);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->mtx->meals_mtx);
	}
	if (new_state == EATING)
		philo->last_meal_time = current_time();
	return (0);
}

int	done_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	if (philo->state == EATING)
	{
		pthread_mutex_unlock(&philo->mtx->state_mtx);
		return ((current_time() - philo->state_start) >= philo->time_to_eat);
	}
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	return (0);
}

int	done_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	if (philo->state == SLEEPING)
	{
		pthread_mutex_unlock(&philo->mtx->state_mtx);
		return ((current_time() - philo->state_start) >= philo->time_to_sleep);
	}
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	return (0);
}

int	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	if (philo->state == THINKING)
	{
		pthread_mutex_unlock(&philo->mtx->state_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	return (FALSE);
}

int	is_dead(t_philo *philo)
{
	return((current_time - philo->last_meal_time) >= philo->time_to_die);
}

int	check_and_update_state(t_philo *philo)
{
	// check if should die
	if (is_dead(philo))
		return(update_state(DEAD, philo))
	if (is_thinking(philo))
	{
		if (has_both_forks(philo))
			return (update_state(EATING, philo));
		else
			return (pick_forks(philo));
	}
	if (done_eating(philo))
	{
		drop_forks(philo);
		return (update_state(SLEEPING, philo));
	}
	if (done_sleeping(philo))
		return (update_state(THINKING, philo));
}

int	not_hungry(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->meals_mtx);
	if (philo->meals_eaten >= philo->meals_to_eat)
	{
		pthread_mutex_unlock(&philo->mtx->meals_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mtx->meals_mtx);
	return (FALSE);
}

//	Checks if the philosopher has not died nor reached the meals goal
int	alive_and_hungry(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->mtx->state_mtx);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	if (not_hungry(philo))
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
