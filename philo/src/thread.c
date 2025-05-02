/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:03:48 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/02 13:14:18 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t *ft_philo_former(t_data	*data, void *f())
{
    int i;
    int check_t;
    pthread_t *philo_arr;
    long *time_to_eat;
    i = 0;
    time_to_eat = malloc(sizeof(long));
    *time_to_eat = data->time_to_eat;
    philo_arr = malloc(sizeof(pthread_t) * data->number_of_philos);
    if(philo_arr == NULL)
        ft_error("philo_arr malloc failed");
    while (i < data->number_of_philos)
    {
        check_t = 0;
        check_t = pthread_create(&philo_arr[i], NULL, f, time_to_eat);
        if (check_t != 0)
            ft_error("failed to create thread");
        i++;
    }
    return (philo_arr);
}
