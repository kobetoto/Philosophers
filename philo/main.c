/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/01 14:34:28 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	data = ft_parsing(ac, av);
	printf("==number of philo:%d==\n", data.number_of_philos);
	printf("==time to die:%ld==\n", data.time_to_die);
	printf("==time to eat:%ld==\n", data.time_to_eat);
	printf("==time to sleep:%ld==\n", data.time_to_sleep);
	printf("==max meal:%d==\n", data.max_meal);
	return (0);
}
/*
number_of_philosophers 
time_to_die 
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/
