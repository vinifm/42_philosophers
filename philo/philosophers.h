/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:24 by viferrei          #+#    #+#             */
/*   Updated: 2022/11/13 18:52:27 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define EINVAL		22	// Invalid argument
# define INT_MAX 	2147483647

// Input handling
int		invalid_args(int argc, char *argv[]);

int		ft_atoi(const char *str);
double	ft_atod(const char *str);
int		ft_isdigit(int c);

#endif
