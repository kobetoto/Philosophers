/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/04 12:17:40 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
	t_data data;
	pthread_t *arr_p;
	data = ft_parsing(ac, av);
	arr_p = ft_philo_thread(&data, &philo_life);

	ft_free_thread_tab(arr_p, data.number_of_philos);
	return (0);
}

int ft_free_thread_tab(pthread_t *arr, int p)
{
	int i;

	i = 0;
	while (i < p)
	{
		pthread_join(arr[i], NULL);
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

