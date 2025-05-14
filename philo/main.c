/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/14 12:12:16 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
	t_data	*data;
	pthread_t *arr_philo;
	// struct timeval tv;
	// long start;
	// long time;

	// gettimeofday(&tv, NULL);
    // start = tv.tv_sec;
	// // printf("Seconds since Jan. 1, 1970: %ld\n", tv.tv_sec);
	// printf("START: %ld\n", start);
	// sleep(4);
	// gettimeofday(&tv, NULL);
	// time = tv.tv_sec;
	// printf("TIME: %ld\n", time - start);


	data = ft_parsing(ac, av);
	arr_philo = ft_philo_thread(data, &philo_life);

	// int	i;
	// i = 0;
	// while(i < data->number_of_philos)
	// {
	// 	printf("philo[%i]: \n id ==> %i\nright fork %i\n\n",i+1, data->philos_arr[i].id, data->philos_arr[i].right_fork);
	// 	i++;
	// }	

	

	ft_free_thread_tab(arr_philo, data->number_of_philos);
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

