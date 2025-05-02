/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/02 13:19:25 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void* routine(void *arg)
{
	long time_to_eat = *((long *)arg);
	// while(time_to_eat)
	// {
		printf("EAT\n");
		time_to_eat--;
	// }
	free(arg);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	pthread_t *arr_p;
	data = ft_parsing(ac, av);
	arr_p = ft_philo_former(&data, &routine);

	ft_free_data(arr_p, data.number_of_philos);
	return (0);
}

int	ft_free_data(pthread_t *arr, int p)
{
	int	i;
	
	i = 0;
	while (i < p)
		{
			if (pthread_join(arr[i], NULL) != 0) {
				return (1);
			}
			i++;
		}
	free(arr);
	return (0);
}


long get_timestamp_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}


/*
number_of_philosophers 
time_to_die 
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/
