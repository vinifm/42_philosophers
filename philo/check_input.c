/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:56:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/28 18:38:16 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	input_error(int err_id, char *argv)
{
	printf("Invalid input: ");
	if (err_id == 0)
		printf("philosophers needs between 4 and 5 integer values.\n");
	if (err_id == 1)
		printf("%s: not a positive integer.\n", argv);
	if (err_id == 2)
		printf("%s: number is too big.\n", argv);
	return (1);
}

// Minimum of 4, maximum of 5 integer values.
int	invalid_args(int argc, char *argv[])
{
	int		i;
	char	*str;

	if (argc < 5 || argc > 6)
		return (input_error(0, argv[0]));
	i = 1;
	while (argv[i])
	{
		str = argv[i];
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (input_error(1, argv[i]));
			str++;
		}
		if (ft_atod(argv[i]) > INT_MAX)
			return (input_error(2, argv[i]));
		i++;
	}
	return (0);
}
