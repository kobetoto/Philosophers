/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:49:39 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 10:18:11 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	fork_mutex_arr_init(t_data *data)
{
	int	i;
	int	j;
	int	nb_ofork;

	i = 0;
	j = 0;
	nb_ofork = data->number_of_philos;
	data->forks_arr = malloc(sizeof(t_fork) * nb_ofork);
	if (data->forks_arr == NULL)
	{
		ft_error("φ forks_arr malloc failed φ");
		return (0);
	}
	while (i < nb_ofork)
	{
		data->forks_arr[i].id = i;
		if (pthread_mutex_init(&data->forks_arr[i].mutex, NULL) != 0)
		{
			perror("φ mutex_init err φ(3)");
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks_arr[j].mutex);
				j++;
			}
			free(data->forks_arr);
			data->forks_arr = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_put_down_fork(t_philo *philo)
{
	int	l;
	int	r;

	l = philo->left_fork;
	r = philo->right_fork;
	if (l == r)
	{
		pthread_mutex_unlock(&philo->data->forks_arr[l].mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->forks_arr[r].mutex);
	pthread_mutex_unlock(&philo->data->forks_arr[l].mutex);
}

int	handle_even_philo(t_philo *philo, int l, int r)
{
	pthread_mutex_lock(&philo->data->forks_arr[l].mutex);
	ft_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->death)
	{
		pthread_mutex_unlock(&philo->data->forks_arr[l].mutex);
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_lock(&philo->data->forks_arr[r].mutex);
	ft_log(philo, "has taken a fork");
	return (1);
}

int	handle_odd_philo(t_philo *philo, int l, int r)
{
	pthread_mutex_lock(&philo->data->forks_arr[r].mutex);
	ft_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->death)
	{
		pthread_mutex_unlock(&philo->data->forks_arr[r].mutex);
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_lock(&philo->data->forks_arr[l].mutex);
	ft_log(philo, "has taken a fork");
	return (1);
}

int	ft_take_forks(t_philo *philo)
{
	int	l;
	int	r;

	l = philo->left_fork;
	r = philo->right_fork;
	if (l == r)
	{
		pthread_mutex_lock(&philo->data->forks_arr[l].mutex);
		ft_log(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->forks_arr[l].mutex);
		return (0);
	}
	if (philo->id % 2 == 0)
	{
		if (handle_even_philo(philo, l, r) == 0)
			return (0);
	}
	else
	{
		if (handle_odd_philo(philo, l, r) == 0)
			return (0);
	}
	return (1);
}
