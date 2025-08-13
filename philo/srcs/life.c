/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:28:44 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 13:31:44 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->death)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	philo->last_meal = timestamp_now(philo->data->start);
	pthread_mutex_unlock(&philo->data->state_mutex);
	ft_log(philo, "is eating");
	usleep((philo->data->time_to_eat) * 1000);
	pthread_mutex_lock(&philo->data->state_mutex);
	if (!philo->data->death && !philo->data->stop)
	{
		philo->meals_eat++;
		if(philo->data->max_meal_activ
			&& !philo->is_full
			&& philo->meals_eat >= philo->data->max_meal)
		{
			philo->is_full = 1;
			philo->data->full_philo_count++;
			if(philo->data->full_philo_count == philo->data->number_of_philos)
				philo->data->stop = 1;
		}
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->death || philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	ft_log(philo, "is thinking");
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->death || philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	ft_log(philo, "is sleeping");
	usleep((philo->data->time_to_sleep) * 1000);
}
