/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:01:30 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/01 14:43:29 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	ft_parsing(int ac, char **av)
{
	t_data	data;

	if ((ac != 5) && (ac != 6))
		ft_error("ARG ERR\n==HINT: 4 or 5 arguments==");
	ft_check_args(av);
	data = ft_stock_data(av);
	return (data);
}

void	ft_check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				ft_error("ARG ERR\n==HINT: only positive intenger==");
			j++;
		}
		i++;
	}
}

t_data	ft_stock_data(char **av)
{
	t_data	table;

	table.number_of_philos = ft_atoi(av[1]);
	table.time_to_die = ft_atol(av[2]);
	table.time_to_eat = ft_atol(av[3]);
	table.time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
		table.max_meal = ft_atoi(av[5]);
	else
		table.max_meal = 0;
	ft_check_data(&table);
	return (table);
}

void	ft_check_data(t_data *data)
{
	if (data->number_of_philos <= 0 || data->number_of_philos > INT_MAX)
		ft_error("φ ERR\n==HINT: wrong number of philosopher==");
	if (data->time_to_die > LONG_MAX || data->time_to_die < 1)
		ft_error("TIME TO DIE ERR\n==HINT: wrong time to die==");
	if (data->time_to_eat > LONG_MAX || data->time_to_eat < 1)
		ft_error("TIME TO EAT ERR\n==HINT: wrong time to eat==");
	if (data->time_to_sleep > LONG_MAX || data->time_to_sleep < 1)
		ft_error("TIME TO SLEEP ERR\n==HINT: wrong time to sleep==");
	if (data->max_meal <= 0)
		ft_error("MAX MEAL ERR\n==HINT: wrong max meal==");
}

