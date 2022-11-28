/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:51 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/28 19:28:21 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	return (0);
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
	while (philo[i])
	{
		pthread_join(philo[i]->thread, NULL);
		free(philo[i]->right_fork);
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
