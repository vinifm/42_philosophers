/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_done_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:34:58 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/28 18:52:22 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	return ((current_time() - philo->last_meal_time)
		>= (size_t) philo->time_to_die);
}
