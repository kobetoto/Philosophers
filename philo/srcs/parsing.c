/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:01:30 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 12:54:08 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if ((ac < 5) || (ac > 6))
	{
		ft_error("φ ARG ERR φ\n==HINT: 4 or 5 arguments only==");
		return (0);
	}
	while (av[i])
	{
		j = 0;
		if(av[i][0] == '\0')
			return (ft_error("φ ARG ERR φ\n==HINT: empty arg=="), (0));
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (ft_error("φ ARG ERR φ\n==HINT: only positive intenger=="), (0));
			j++;
		}
		i++;
	}
	return (1);
}

t_data	*stock_data(char **av)
{
	t_data	*data_info;

	data_info = malloc(sizeof(t_data));
	if (data_info == NULL)
	{
		ft_error("φ data_info malloc failed φ");
		return (NULL);
	}
	data_info->number_of_philos = ft_atoi(av[1]);
	data_info->time_to_die = ft_atol(av[2]);
	data_info->time_to_eat = ft_atol(av[3]);
	data_info->time_to_sleep = ft_atol(av[4]);
	data_info->full_philo_count = 0;
	if (av[5] && *av[5] != '\0')
	{
		data_info->max_meal_activ = 1;
		data_info->max_meal = ft_atoi(av[5]);
	}
	else
	{
		data_info->max_meal_activ = 0;
		data_info->max_meal = -1;
	}
	data_info->stop = 0;
	data_info->start = get_timestamp_ms();
	data_info->death = 0;
	if (check_data(data_info) == 0)
	{
		free(data_info);
		return (NULL);
	}
	if (pthread_mutex_init(&(data_info->print_mutex), NULL) != 0)
	{
		ft_error("φ mutex_init err φ (1)");
		free(data_info);
		return (NULL);
	}
	if (pthread_mutex_init(&(data_info->state_mutex), NULL) != 0)
	{
		ft_error("φ mutex_init err φ (2)");
		pthread_mutex_destroy(&(data_info->print_mutex));
		free(data_info);
		return (NULL);
	}
	data_info->philos_arr = philo_arr_init(data_info->number_of_philos,
			data_info);
	if (data_info->philos_arr == NULL)
	{
		pthread_mutex_destroy(&(data_info->print_mutex));
		pthread_mutex_destroy(&(data_info->state_mutex));
		free(data_info);
		return (NULL);
	}
	if ((fork_mutex_arr_init(data_info)) == 0)
	{	
		free(data_info->philos_arr);
		pthread_mutex_destroy(&(data_info->print_mutex));
		pthread_mutex_destroy(&(data_info->state_mutex));
		free(data_info);
		return (NULL);
	}
	return (data_info);
}

int	check_data(t_data *data)
{
	if (data->number_of_philos <= 0 || data->number_of_philos > 200)
		return (ft_error("φ PHILO ERR φ\n==HINT: wrong number of philosopher=="), (0));
	if (data->time_to_die < 1 ||
		data->time_to_eat < 1 ||
		data->time_to_sleep < 1)
		return (ft_error("φ TIME TO DIE ERR φ\n==HINT: wrong time to die=="), (0));
	if (data->max_meal_activ && data->max_meal < 1)
		return (ft_error("φ MEAL ERR φ\n==HINT: wrong number of meal=="), (0));
	return (1);
}
