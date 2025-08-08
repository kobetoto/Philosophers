/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/08 11:00:32 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data	*data;
	pthread_t *threads_arr;

	/* PARSING 		*/
	data = parsing(ac, av);

	/* THREAD 		*/
	threads_arr = thread_arr_init(data, &philo_routine);
	free_thread_tab(threads_arr, data->number_of_philos);
	free(data);
	return (0);
}
