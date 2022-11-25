/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:51 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/25 17:14:34 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(int index, t_philo *philo, char *argv[], t_mtx *mtx)
{
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
	philo->state = THINKING;
	philo->mtx = mtx;
}

void	create_fork(t_philo *philo)
{
	t_fork			*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return ;
	fork->locked = FALSE;
	// pthread_mutex_init(&fork->fork_mtx, NULL);
	philo->right_fork = fork;
}

t_mtx	*init_mutexes()
{
	t_mtx	*mtx;

	mtx = malloc(sizeof(t_mtx));
	if (!mtx)
		return NULL;
	mtx->simulation_status = TRUE;
	pthread_mutex_init(&mtx->simulation_mtx, NULL);
	pthread_mutex_init(&mtx->state_mtx, NULL);
	pthread_mutex_init(&mtx->print_mtx, NULL);
	pthread_mutex_init(&mtx->meals_mtx, NULL);
	pthread_mutex_init(&mtx->forks_mtx, NULL);
	return(mtx);
}

t_philo	**create_philosophers(char *argv[], t_mtx *mtx)
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
		init_philosopher(index, philo[index], argv, mtx);
		create_fork(philo[index]);
		if (index > 0)
			philo[index]->left_fork = philo[index - 1]->right_fork;
		index++;
	}
	philo[0]->left_fork = philo[index - 1]->right_fork;
	philo[index] = NULL;
	return (philo);
}

// Saves the starting time
void	set_start_time(t_philo **philo)
{
	size_t	start_time;
	int		i;

	start_time = current_time();
	i = 0;
	while (philo[i])
	{
		philo[i]->start_time = start_time;
		i++;
	}
}

//	Creates each thread
void	start_simulation(t_philo **philo)
{
	int	i;

	set_start_time(philo);
	i = 0;
	while (philo[i])
	{
		pthread_create(&philo[i]->thread, NULL, &state_loop, philo[i]);
		i++;
	}
}

int	simulation_loop(t_philo **philo, char *argv[])
{
	int	index;
	int	satisfieds;
	int	philo_count;

	index = 0;
	satisfieds = 0;
	philo_count = ft_atoi(argv[1]);
	while (is_simulating(philo[index]) && (satisfieds < philo_count))
	{
		usleep(1000);
		if (not_hungry(philo[index]))
			satisfieds++;
		index++;
		if ((index + 1) == philo_count)
			index = 0;
	}
	return (0);
}

//	Join threads, destroy mutexes and free philosophers.
int	end_simulation(t_philo **philo, t_mtx *mtx)
{
	int	i;

	i = 0;
	while(philo[i])
	{
		pthread_join(philo[i]->thread, NULL);
		// pthread_mutex_destroy(&philo[i]->right_fork->fork_mtx);
		free(philo[i]);
		i++;
	}
	free(philo);
	pthread_mutex_destroy(&mtx->simulation_mtx);
	pthread_mutex_destroy(&mtx->state_mtx);
	pthread_mutex_destroy(&mtx->print_mtx);
	pthread_mutex_destroy(&mtx->meals_mtx);
	pthread_mutex_destroy(&mtx->forks_mtx);
	free(mtx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mtx	*mtx;
	t_philo	**philo;

	if (invalid_args(argc, argv))
		return (EINVAL);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 died\n");
		return (0);
	}
	mtx = init_mutexes();
	if (!mtx)
		return (-1);
	philo = create_philosophers(argv, mtx);
	if (!philo)
		return (-1);
	start_simulation(philo);
	simulation_loop(philo, argv);
	end_simulation(philo, mtx);
	// test_philos(philo);
	return (0);
}
