/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:31:09 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/14 18:50:25 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	test_philos(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		printf("\nphilo nb: %d\n", philo[i]->nb);
		printf("time to die, eat, sleep: %d %d %d\n", philo[i]->time_to_die, \
				philo[i]->time_to_eat, philo[i]->time_to_sleep);
		printf("meals to eat: %d\n", philo[i]->meals_to_eat);
		printf("left fork: %p\n", philo[i]->left_fork);
		printf("right fork: %p\n", philo[i]->right_fork);
		i++;
	}
}
