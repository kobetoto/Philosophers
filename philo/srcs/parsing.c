/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:01:30 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/07 15:04:28 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"



t_data	*parsing(int ac, char **av)
{
	t_data	*data;

	check_args(ac, av);
	data = stock_data(av);
	return (data);
}

t_data	*stock_data(char **av)
{
	t_data	*data_info;

	data_info = malloc(sizeof(t_data));
	if (data_info == NULL)
		ft_error("φ data_info malloc failed φ");
	data_info->number_of_philos = ft_atoi(av[1]);
	data_info->time_to_die = ft_atol(av[2]);
	data_info->time_to_eat = ft_atol(av[3]);
	data_info->time_to_sleep = ft_atol(av[4]);
	data_info->start = get_timestamp_ms();
	if (pthread_mutex_init(&(data_info->print_mutex), NULL) != 0)
		perror("φ mutex_init err φ");
	check_data(data_info);
	data_info->philos_arr = philo_arr_init(data_info->number_of_philos, data_info);
	fork_mutex_arr_init(data_info);
	return (data_info);
}

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
		philo_arr[i].last_meal =  data_info->start;
		philo_arr[i].data = data_info;
		i++;
	}
	return (philo_arr);
}

void    fork_mutex_arr_init(t_data *data)
{
    int i;
    int nb_ofork;

    i = 0;
    nb_ofork = data->number_of_philos;
    data->forks_arr = malloc(sizeof(t_fork) * nb_ofork);
    if (data->forks_arr == NULL)
        ft_error("φ forks_arr malloc failed φ");
    while (i < nb_ofork)
    {
        data->forks_arr[i].id = i;
        if (pthread_mutex_init(&data->forks_arr[i].mutex, NULL) != 0)
            perror("φ mutex_init err φ");
        i++;
    }
}