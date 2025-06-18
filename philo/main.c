/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/06/17 14:00:35 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*int gettimeofday(struct timeval *tv, struct timezone *tz);

struct timeval {
    time_t      tv_sec;     // secondes depuis le 1er janvier 1970 (Epoch)
    suseconds_t tv_usec;    // microsecondes (0 à 999999)
};

    tv : pointeur vers une struct timeval remplie par la fonction.

    tz : toujours NULL (obsolète, pas utilisé).

Elle remplit la struct avec le temps actuel
(en UTC, depuis Epoch : 1970-01-01).


    Appel initial : gettimeofday(&start, NULL);

    Plus tard : gettimeofday(&end, NULL);

(end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000 
pour avoir en millisecondes.
*/


int main(int ac, char **av)
{
	t_data	*data;
	pthread_t *threads_arr;


	data = ft_parsing(ac, av);
	data->start = get_timestamp_ms();
	threads_arr = ft_thread(data, &philo_life);
	ft_free_thread_tab(threads_arr, data->number_of_philos);
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

long	timestamp_now(t_data *data)
{
	return (get_timestamp_ms() - data->start);
}

/*
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/


	// int	i;
	// i = 0;
	// while(i < data->number_of_philos)
	// {
	// 	printf("philo[%i]: \n id ==> %i\nleft fork %i\nright fork %i\n\n",i+1, data->philos_arr[i].id, data->philos_arr[i].left_fork,data->philos_arr[i].right_fork);
	// 	i++;
	// }	
	// printf("\n----------------------------------------\n");
	// printf("data: \n nbr de philo ==> %i\n", data->number_of_philos);

