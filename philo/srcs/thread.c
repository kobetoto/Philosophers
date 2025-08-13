/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:03:48 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 12:50:33 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t	*thread_arr_init(t_data *data, void *f())
{
	int			i;
	int			j;
	int			check_thread;
	pthread_t	*threads_arr;

	i = 0;
	j = 0;
	check_thread = 0;
	threads_arr = malloc(sizeof(pthread_t) * data->number_of_philos);
	if (threads_arr == NULL)
	{
		ft_error("φ philo_arr malloc failed φ");
		return (NULL);
	}
	while (i < data->number_of_philos)
	{
		check_thread = pthread_create(&threads_arr[i], NULL,
				f, &data->philos_arr[i]);
		if (check_thread != 0)
		{
			ft_error("φ failed to create thread φ");
			pthread_mutex_lock(&data->state_mutex);
			data->death = 1;
			pthread_mutex_lock(&data->state_mutex);
			if (i > 0)
			{
				while (j < i)
				{
					pthread_join(threads_arr[j], NULL);
					j++;
				}
			}
			free(threads_arr);
			return (NULL);
		}
		i++;
	}
	return (threads_arr);
}

void	*thread_death_check(void *arg)
{
	t_philo	*philo;
	long	now;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(200);
		now = timestamp_now(philo->data->start);
		pthread_mutex_lock(&philo->data->state_mutex);
		if (philo->data->death || philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		if (now - philo->last_meal >= philo->data->time_to_die)
		{
			philo->data->death = 1;
			pthread_mutex_unlock(&philo->data->state_mutex);
			print_death(philo, now);
			break ;
		}
		pthread_mutex_unlock(&philo->data->state_mutex);
	}
	return (NULL);
}
