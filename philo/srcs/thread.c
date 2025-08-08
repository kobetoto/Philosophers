/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:03:48 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/08 15:38:04 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t *thread_arr_init(t_data *data, void *f())
{
    int i;
    int check_thread;
    pthread_t *threads_arr;

    i = 0;
    check_thread = 0;
    threads_arr = malloc(sizeof(pthread_t) * data->number_of_philos);
    if (threads_arr == NULL)
        ft_error("φ philo_arr malloc failed φ");
    while (i < data->number_of_philos)
    {
        check_thread = pthread_create(&threads_arr[i], NULL, f, &data->philos_arr[i]);
        if (check_thread != 0)
            ft_error("φ failed to create thread φ");
        i++;
    }
    usleep(42);
    return (threads_arr);
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    pthread_t death_checker;

    philo = (t_philo *)arg;
    pthread_create(&death_checker, NULL, thread_death_check, philo);
    pthread_detach(death_checker);
    while (1)
    {
        pthread_mutex_lock(&philo->data->state_mutex);
        if(philo->data->death)
        {
            pthread_mutex_unlock(&philo->data->state_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->state_mutex);
        ft_take_forks(philo);
        ft_eating(philo);
        ft_put_down_fork(philo);
        ft_sleeping(philo);
        ft_thinking(philo);
    }
    return (NULL);
}

void *thread_death_check(void *arg)
{
    t_philo *philo;
    long    now;

    philo = (t_philo *)arg;
    while (1)
    {
        now = timestamp_now(philo->data->start);
        pthread_mutex_lock(&philo->data->state_mutex);
        if (philo->data->death)
        {
            pthread_mutex_unlock(&philo->data->state_mutex);
            break;
        }
        if (now - philo->last_meal >= philo->data->time_to_die)
        {
            philo->data->death = 1;
            pthread_mutex_unlock(&philo->data->state_mutex);
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("%ldms [%d] died\n", now, philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->state_mutex);
    }
    return (NULL);
}
