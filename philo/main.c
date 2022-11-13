/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:51 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/13 19:45:35 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(int index, t_philo *philo, char *argv[])
{
	index++;
	philo->nb = index;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
}

t_philo	**create_philosophers(char *argv[])
{
	t_philo **philo;
	int		philo_count;
	int		index;

	philo_count = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo *) * (philo_count + 1));
	if (!philo)
		return NULL;
	index = 0;
	while (index < philo_count)
	{
		philo[index] = malloc(sizeof(t_philo));
		if (!philo[index])
			return NULL;
		init_philosopher(index, philo[index], argv);
		index++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	**philo;

	if (invalid_args(argc, argv))
		return (EINVAL);
	philo = create_philosophers(argv);
	return (0);
}
