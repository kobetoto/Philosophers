/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:45:06 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 12:51:35 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
}

void	print_death(t_philo *philo, long now)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d died\n", now, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_log(t_philo *philo, char *msg)
{
	long	ts;

	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->death || philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	ts = timestamp_now(philo->data->start);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i %s\n", ts, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->state_mutex);
}
