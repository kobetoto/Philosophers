/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:43:42 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/12 12:15:29 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_thread_tab(pthread_t *arr, int p)
{
	int	i;

	i = 0;
	while (i < p)
	{
		pthread_join(arr[i], NULL);
		i++;
	}
	free(arr);
	return (0);
}

int	free_mutex_tab(t_fork *arr, int p)
{
	int	i;

	i = 0;
	while (i < p)
	{
		pthread_mutex_destroy(&(arr[i].mutex));
		i++;
	}
	free(arr);
	return (0);
}
