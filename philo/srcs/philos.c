/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:42:46 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 12:45:02 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*philo_arr_init(int nbr_philo, t_data *data_info)
{
	int		i;
	t_philo	*philo_arr;

	i = 0;
	philo_arr = malloc(sizeof(t_philo) * nbr_philo);
	if (philo_arr == NULL)
		ft_error("φ philo_arr malloc failed φ");
	while (i < nbr_philo)
	{
		philo_arr[i].id = i + 1;
		philo_arr[i].right_fork = i;
		philo_arr[i].left_fork = (i + 1) % nbr_philo;
		philo_arr[i].last_meal = 0;
		philo_arr[i].meals_eat = 0;
		philo_arr[i].is_full = 0;
		philo_arr[i].data = data_info;
		i++;
	}
	return (philo_arr);
}


void	handle_single_philo(t_philo *philo, pthread_t death_checker)
{
	int	check;

	pthread_mutex_lock(&philo->data->forks_arr[philo->left_fork].mutex);
	ft_log(philo, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		check = philo->data->death;
		pthread_mutex_unlock(&philo->data->state_mutex);
		if (check)
			break ;
		usleep(200);
	}
	pthread_mutex_unlock(&philo->data->forks_arr[philo->left_fork].mutex);
	pthread_join(death_checker, NULL);
}

void	philo_loop(t_philo *philo)
{
	if ((philo->id % 2) == 1
		&& philo->data->time_to_eat < philo->data->time_to_die)
		usleep((philo->data->time_to_eat / 2) * 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		if (philo->data->death || philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->state_mutex);
		if ((philo->id % 2) == 1)
			usleep(1000);
		if (ft_take_forks(philo))
		{
			ft_eating(philo);
			ft_put_down_fork(philo);
		}
		ft_sleeping(philo);
		ft_thinking(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death_checker;

	philo = (t_philo *)arg;
	usleep(philo->data->time_to_eat / 2 * 1000);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->last_meal = timestamp_now(philo->data->start);
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_create(&death_checker, NULL, thread_death_check, philo);
	if (philo->data->number_of_philos == 1)
	{
		handle_single_philo(philo, death_checker);
		return (NULL);
	}
	philo_loop(philo);
	pthread_join(death_checker, NULL);
	return (NULL);
}
