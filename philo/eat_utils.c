/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:43:59 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/28 19:33:59 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	picked_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->forks_mtx);
	if (is_simulating(philo)
		&& philo->right_fork->locked == FALSE
		&& philo->left_fork->locked == FALSE)
	{
		philo->right_fork->locked = TRUE;
		philo->left_fork->locked = TRUE;
		pthread_mutex_lock(&philo->mtx->print_mtx);
		printf("%zu %d has taken a fork\n", current_time(), philo->nb);
		printf("%zu %d has taken a fork\n", current_time(), philo->nb);
		pthread_mutex_unlock(&philo->mtx->print_mtx);
		pthread_mutex_unlock(&philo->mtx->forks_mtx);
		update_state(EATING, philo);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mtx->forks_mtx);
	return (FALSE);
}

int	drop_forks(t_philo *philo)
{
	if (is_simulating(philo))
	{
		pthread_mutex_lock(&philo->mtx->forks_mtx);
		philo->right_fork->locked = FALSE;
		philo->left_fork->locked = FALSE;
		pthread_mutex_unlock(&philo->mtx->forks_mtx);
	}
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

//	Updates last meal time and checks if philosopher won't die while eating
int	eat_or_die(t_philo *philo)
{
	philo->last_meal_time = current_time();
	if (current_time() - philo->last_meal_time + philo->time_to_eat
		>= (size_t) philo->time_to_die)
	{
		usleep(philo->time_to_die * 1000);
		update_state(DEAD, philo);
	}
	else
		usleep(philo->time_to_eat * 1000);
	return (0);
}
