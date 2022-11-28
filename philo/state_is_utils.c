/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:49:09 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/21 20:13:21 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	if (philo->state == EATING)
	{
		pthread_mutex_unlock(&philo->mtx->state_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	return (FALSE);
}

int	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	if (philo->state == SLEEPING)
	{
		pthread_mutex_unlock(&philo->mtx->state_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	return (FALSE);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->state_mtx);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->mtx->state_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mtx->state_mtx);
	return (FALSE);
}

int	is_simulating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx->simulation_mtx);
	if (philo->mtx->simulation_status == TRUE)
	{
		pthread_mutex_unlock(&philo->mtx->simulation_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mtx->simulation_mtx);
	return (FALSE);
}
