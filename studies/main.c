/* ************************************************************************ */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codevault.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:09:57 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/04 16:12:10 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Unix threads in c (https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=1)

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

void *routine()
{
	printf("Test test test\n");
	sleep(3);
	printf("Process id %d\n", getpid());
	return (0);
}

int main(void)
{
	// Variable that stores info about the thread
	pthread_t	t1, t2;

	// Initializes thread. NULL sets the other parameters as default attributes.
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 1;
	
	// Waits for the thread to finish execution.
	if (pthread_join(t1, NULL) != 0)
		return 2;
	if (pthread_join(t2, NULL) != 0)
		return 2;

	return (0);
}