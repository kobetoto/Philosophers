/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:01:30 by thodavid          #+#    #+#             */
/*   Updated: 2025/04/29 15:23:40 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_parsing(int ac, char **av)
{
	t_data	*data;
	
	data = NULL;
	if (!(ac == 4) || !(ac == 5))
		ft_error("ARG ERR\n==HINT: 4 or 5 arguments==");
	ft_check_data(av);
}

void	ft_check_data(char **av)
{
	int		i;
	int		philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meal;

	i = 0;
	while (av[i] != NULL)
		i++;
	philo = ft_atoi(av[1]);
	if (philo <= 0)
		ft_error("ARG ERR\n==HINT: at least one philosopher (be or not to be)==");
	time_to_die = ft_atol(av[2]);
	time_to_eat = ft_atol(av[3]);
	time_to_sleep = ft_atol(av[4]);
	if (i == 5)
		max_meal = ft_atoi(av[5]);

	ft_check_timestamp(time_to_die, time_to_eat, time_to_sleep, max_meal);
}

void	ft_check_timestamp(long t_to_die, long t_to_eat, long t_to_sleep, int max_meal)
{
    if (t_to_die > LONG_MAX)
        ft_error("ARG ERR\n==HINT: time to die too long (long max err)==");
    if (t_to_eat > LONG_MAX)
        ft_error("ARG ERR\n==HINT: time to eat too long (long max err)==");
    if (t_to_sleep > LONG_MAX)
        ft_error("ARG ERR\n==HINT: time to die too long (long max err)==");
    if (t_to_eat > t_to_die)
        ft_error("ARG ERR\n==HINT: time to eat too long==");
    if (t_to_sleep > t_to_die)
        ft_error("ARG ERR\n==HINT: time to sleep too long==");
    if (max_meal <= 0 || max_meal > INT_MAX)
        ft_error("ARG ERR\n==HINT: max meal==");
}
