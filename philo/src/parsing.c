/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:01:30 by thodavid          #+#    #+#             */
/*   Updated: 2025/06/18 09:54:38 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	*ft_parsing(int ac, char **av)
{
	t_data	*data;

	if ((ac !=5))
		ft_error("ARG ERR\n==HINT: 4 arguments==");
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

t_data	*ft_stock_data(char **av)
{
	t_data	*data_info;

	data_info = malloc(sizeof(t_data));
	if (data_info == NULL)
		ft_error("data_info malloc failed");
	data_info->number_of_philos = ft_atoi(av[1]);
	data_info->time_to_die = ft_atol(av[2]);
	data_info->time_to_eat = ft_atol(av[3]);
	data_info->time_to_sleep = ft_atol(av[4]);
	data_info->philos_arr = ft_philo_arr_init(data_info->number_of_philos, data_info);
	fork_mutex_init(data_info);
	ft_check_data(data_info);
	return (data_info);
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
}

t_philo	*ft_philo_arr_init(int nbr_philo, t_data *data_info)
{
	int		i;
	t_philo	*philo_arr;
	
	i = 0;
	philo_arr = malloc(sizeof(t_philo) * nbr_philo);
	if (philo_arr == NULL)
		ft_error("err:: philo_arr malloc failed (1)");
	while (i < nbr_philo)
	{
		philo_arr[i].id = i + 1; 
		//todo:: right fork but no left fork
		philo_arr[i].right_fork = i;
		philo_arr[i].left_fork = (i + 1) % nbr_philo;
		philo_arr[i].last_meal =  data_info->start;
		philo_arr[i].data = data_info;
		i++;
	}
	return (philo_arr);
}

void    fork_mutex_init(t_data *data)
{
    int i;
    int nb_ofork;

    i = 0;
    nb_ofork = data->number_of_philos;
    data->forks_arr = malloc(sizeof(t_fork) * nb_ofork);
    if (data->forks_arr == NULL)
        ft_error("malloc forks_arr");
    while (i < nb_ofork)
    {
        data->forks_arr[i].id = i;
        if (pthread_mutex_init(&data->forks_arr[i].mutex, NULL) != 0)
            perror("mutex_init err");
        i++;
    }
}
