/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:51 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/12 20:01:49 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	invalid_args(int argc, char argv[])
{

}

int	main(int argc, char argv[])
{
	if (invalid_args(argc, argv))
	{
		write(2, "Invalid input\n", 14);
		return(EINVAL);
	}
	return (0);
}
