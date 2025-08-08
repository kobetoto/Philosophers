/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:03:23 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/08 11:03:31 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

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

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (nptr[0] == '\0')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (r > (INT_MAX - (nptr[i] - '0')) / 10)
			return (-1);
		r = (r * 10) + (nptr[i] - '0');
		i++;
	}
	return (r);
}

long	ft_atol(const char *nptr)
{
	int		i;
	long		r;

	i = 0;
	r = 0;
	if (nptr[0] == '\0')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (r > (LONG_MAX - (nptr[i] - '0')) / 10)
			return (-1);
		r = (r * 10) + (nptr[i] - '0');
		i++;
	}
	return (r);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	check_data(t_data *data)
{
	if (data->number_of_philos <= 0 || data->number_of_philos > 1024)
		ft_error("φ ERR φ\n==HINT: wrong number of philosopher==");
	if (data->time_to_die > LONG_MAX || data->time_to_die < 1)
		ft_error("φ TIME TO DIE ERR φ\n==HINT: wrong time to die==");
	if (data->time_to_eat > LONG_MAX || data->time_to_eat < 1)
		ft_error("φ TIME TO EAT ERR φ\n==HINT: wrong time to eat==");
	if (data->time_to_sleep > LONG_MAX || data->time_to_sleep < 1)
		ft_error("φ TIME TO SLEEP ERR φ\n==HINT: wrong time to sleep==");
}

void	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if ((ac !=5))
		ft_error("φ ARG ERR φ\n==HINT: 4 arguments==");
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				ft_error("φ ARG ERR φ\n==HINT: only positive intenger==");
			j++;
		}
		i++;
	}
}

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

void	ft_log(t_philo *philo, char *msg)
{
	long	ts;
	if(philo->data->death)
		return;
	ts = timestamp_now(philo->data->start);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i %s\n", ts, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

