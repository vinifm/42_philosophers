/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:09:46 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/28 19:32:38 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	check_and_update_state(t_philo *philo)
{
	if (done_living(philo))
		return (update_state(DEAD, philo));
	if (is_thinking(philo))
	{
		while (!(picked_forks(philo)) && is_simulating(philo))
			continue ;
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
	char	*state_str;

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
		eat_or_die(philo);
	return (0);
}
