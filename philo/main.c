/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:51 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/16 20:33:22 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(int index, t_philo *philo, char *argv[])
{
	philo->nb = index + 1;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
	else
		philo->meals_to_eat = INT_MAX;
	philo->state = THINKING;
	pthread_mutex_init(&philo->state_mtx, NULL);
}

void	create_fork(t_philo *philo)
{
	t_fork			*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return ;
	fork->locked = FALSE;
	pthread_mutex_init(&fork->fork_mtx, NULL);
	philo->right_fork = fork;
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
		create_fork(philo[index]);
		if (index > 0)
			philo[index]->left_fork = philo[index - 1]->right_fork;
		index++;
	}
	philo[0]->left_fork = philo[index - 1]->right_fork;
	philo[index] = NULL;
	return (philo);
}

//	Checks if the philosopher has not died nor reached the meals goal
int	alive_and_unsatisfied(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mtx);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->state_mtx);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->state_mtx);
	if (is_satisfied(philo))
		return (FALSE);
	return (TRUE);
}

void	check_and_update_state(t_philo *philo)
{
	long	timestamp;

	timestamp = gettimestamp(philo->start_time);
	if (is_thinking(philo))
	{
		if (has_both_forks(philo))
			return(update_state(EATING, philo));
		else
			return(pick_forks(philo));
	}
	if (done_eating(philo)) // check if they're eating inside
	{
		drop_forks(philo);
		return(update_state(SLEEPING, philo));
	}
	if (done_sleeping(philo))
		return(update_state(THINKING, philo));
}

void	*state_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (alive_and_unsatisfied(philo))
	{
		check_and_update_state(philo);
		// usleep?
	}
	// print state
	return (0);
}

// Saves the starting time
void	set_start_time(t_philo **philo)
{
	struct	timeval tv;\
	long	start_time;
	int		i;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
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

int	main(int argc, char **argv)
{
	t_philo	**philo;

	if (invalid_args(argc, argv))
		return (EINVAL);
	philo = create_philosophers(argv);
	start_simulation(philo);
	// test_philos(philo);
	return (0);
}
