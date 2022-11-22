/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:09:46 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/22 20:40:52 by viferrei         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mtx->print_mtx);
	if (is_simulating(philo))
		printf("%zu %d %s\n", current_time(), philo->nb, state_str);
	pthread_mutex_unlock(&philo->mtx->print_mtx);
	return (0);
}

int	update_state(int new_state, t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	philo->state_start = current_time();
	philo->state = new_state;
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	print_state(philo);
	if (new_state == DEAD)
	{
		pthread_mutex_lock(&philo->mtx->simulation_mtx);
		philo->mtx->simulation_status = FALSE;
		pthread_mutex_unlock(&philo->mtx->simulation_mtx);
	}
	if (new_state == SLEEPING)
	{
		pthread_mutex_lock(&philo->mtx->meals_mtx);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->mtx->meals_mtx);
		usleep(philo->time_to_sleep * 1000);
	}
	if (new_state == EATING)
	{
		philo->last_meal_time = current_time();
		usleep(philo->time_to_eat * 1000);
	}
	return (0);
}

int	done_eating(t_philo *philo)
{
	if (is_eating(philo))
	{
		return ((current_time() - philo->state_start)
					>= (size_t) philo->time_to_eat);
	}
	return (0);
}

int	done_sleeping(t_philo *philo)
{
	if (is_sleeping(philo))
	{
		return ((current_time() - philo->state_start)
					>= (size_t) philo->time_to_sleep);
	}
	return (0);
}

int	done_living(t_philo *philo)
{
	return((current_time() - philo->last_meal_time)
			>= (size_t) philo->time_to_die);
}

int	picked_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mtx);
	pthread_mutex_lock(&philo->left_fork->fork_mtx);
	if (philo->right_fork->locked == FALSE && philo->left_fork->locked == FALSE)
	{
		philo->right_fork->locked = TRUE;
		philo->left_fork->locked = TRUE;
		pthread_mutex_lock(&philo->mtx->print_mtx);
		printf("%zu %d has taken a fork\n", current_time(), philo->nb);
		printf("%zu %d has taken a fork\n", current_time(), philo->nb);
		pthread_mutex_unlock(&philo->mtx->print_mtx);
		pthread_mutex_unlock(&philo->right_fork->fork_mtx);
		pthread_mutex_unlock(&philo->left_fork->fork_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->right_fork->fork_mtx);
	pthread_mutex_unlock(&philo->left_fork->fork_mtx);
	return (FALSE);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mtx);
	pthread_mutex_lock(&philo->left_fork->fork_mtx);
	philo->right_fork->locked = FALSE;
	philo->left_fork->locked = FALSE;
	pthread_mutex_unlock(&philo->right_fork->fork_mtx);
	pthread_mutex_unlock(&philo->left_fork->fork_mtx);
	return (0);
}

int	check_and_update_state(t_philo *philo)
{
	if (done_living(philo))
		return(update_state(DEAD, philo));
	if (is_thinking(philo))
	{
		if (picked_forks(philo))
			return (update_state(EATING, philo));
	}
	if (done_eating(philo))
	{
		drop_forks(philo);
		return (update_state(SLEEPING, philo));
	}
	if (done_sleeping(philo))
		return (update_state(THINKING, philo));
	return (0);
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

// Checks, updates and prints philosopher state while it's alive and hungry
void	*state_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	usleep(philo->nb * 250);
	while (!is_dead(philo) && !not_hungry(philo))
	{
		check_and_update_state(philo);
		usleep(200);
	}
	return (0);
}
