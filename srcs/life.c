/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:28:44 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/08 12:41:32 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_put_down_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks_arr[philo->right_fork].mutex);
	pthread_mutex_unlock(&philo->data->forks_arr[philo->left_fork].mutex);
}

void	ft_take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->left_fork;
	right= philo->right_fork;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks_arr[philo->left_fork].mutex);
        ft_log(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks_arr[philo->right_fork].mutex);
        ft_log(philo, "has taken a fork");
    }
    else
    {
		pthread_mutex_lock(&philo->data->forks_arr[philo->right_fork].mutex);
        ft_log(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks_arr[philo->left_fork].mutex);
        ft_log(philo, "has taken a fork");

    }
}


void	ft_eating(t_philo *philo)
{
	long	ts;

	ts = timestamp_now(philo->data->start);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i is eating\n", ts, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep((philo->data->time_to_eat) * 1000);
	philo->last_meal = timestamp_now(philo->data->start);
}

void	ft_thinking(t_philo *philo)
{
	long	ts;

	ts = timestamp_now(philo->data->start);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i is thinking\n", ts, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_sleeping(t_philo *philo)
{
	long	ts;

	ts = timestamp_now(philo->data->start);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i is sleeping\n", ts, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep((philo->data->time_to_sleep) * 1000);
}
