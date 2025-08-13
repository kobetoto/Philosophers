/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 15:14:31 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*parsing(int ac, char **av)
{
	t_data	*data;

	(void) ac;
	data = stock_data(av);
	if (data == NULL)
		return (NULL);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!check_args(ac, av))
		return (0);
	data = parsing(ac, av);
	if (data == NULL)
		return (1);
	data->threads_arr = thread_arr_init(data, &philo_routine);
	if (data->threads_arr == NULL)
	{
		free_mutex_tab(data->forks_arr, data->number_of_philos);
		pthread_mutex_destroy(&(data->print_mutex));
		pthread_mutex_destroy(&(data->state_mutex));
		free(data->philos_arr);
		free(data);
		return (1);
	}	
	free_thread_tab(data->threads_arr, data->number_of_philos);
	free_mutex_tab(data->forks_arr, data->number_of_philos);
	pthread_mutex_destroy(&(data->state_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
	free(data->philos_arr);
	free(data);
	return (0);
}
