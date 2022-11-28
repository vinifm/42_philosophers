/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:19:35 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/28 18:49:09 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	**create_philosophers(char *argv[], t_mtx *mtx)
{
	t_philo	**philo;
	int		philo_count;
	int		index;

	philo_count = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo *) * (philo_count + 1));
	if (!philo)
		return (NULL);
	index = 0;
	while (index < philo_count)
	{
		philo[index] = init_philosopher(index, argv, mtx);
		if (!philo[index])
			return (NULL);
		create_fork(philo[index]);
		if (index > 0)
			philo[index]->left_fork = philo[index - 1]->right_fork;
		index++;
	}
	philo[0]->left_fork = philo[index - 1]->right_fork;
	philo[index] = NULL;
	return (philo);
}

t_philo	*init_philosopher(int index, char *argv[], t_mtx *mtx)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->nb = index + 1;
	philo->philo_count = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
	else
		philo->meals_to_eat = INT_MAX;
	philo->meals_eaten = 0;
	philo->last_meal_time = 0;
	philo->start_time = 0;
	philo->state_start = 0;
	philo->state = THINKING;
	philo->mtx = mtx;
	return (philo);
}

void	create_fork(t_philo *philo)
{
	t_fork			*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return ;
	fork->locked = FALSE;
	philo->right_fork = fork;
}

t_mtx	*init_mutexes(void)
{
	t_mtx	*mtx;

	mtx = malloc(sizeof(t_mtx));
	if (!mtx)
		return (NULL);
	mtx->simulation_status = TRUE;
	pthread_mutex_init(&mtx->simulation_mtx, NULL);
	pthread_mutex_init(&mtx->state_mtx, NULL);
	pthread_mutex_init(&mtx->print_mtx, NULL);
	pthread_mutex_init(&mtx->meals_mtx, NULL);
	pthread_mutex_init(&mtx->forks_mtx, NULL);
	return (mtx);
}
