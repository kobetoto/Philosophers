/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:03:48 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/04 15:00:26 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t *ft_philo_thread(t_data *data, void *f())
{
    int i;
    int check_t;
    pthread_t *philo_arr;

    i = 0;
    philo_arr = malloc(sizeof(pthread_t) * data->number_of_philos);
    if (philo_arr == NULL)
        ft_error("philo_arr malloc failed");
    while (i < data->number_of_philos)
    {
        int *philo_id;
        philo_id = malloc(sizeof(int));
        *philo_id = i;
        check_t = 0;
        usleep(242);
        check_t = pthread_create(&philo_arr[i], NULL, f, philo_id);
        if (check_t != 0)
            ft_error("failed to create thread");
        i++;
    }
    return (philo_arr);
}

void *philo_life(void *arg)
{
    t_philo *philo;
    int *id;
    char *color;

    id = (int *)arg;
    color = "";
    *id += 1;
    philo = malloc(sizeof(t_philo));
    if (philo == NULL)
        ft_error("malloc failed (philo_life)");
    philo->pthread_id = *id;
    // ft_eating();
    // ft_sleeping();
    // ft_thinking();
    ft_log(id);

    return (NULL);
}

void ft_log(int *philo_id)
{
    char *color;

    color = "";
    if (((*philo_id) % 1) == 0)
        color = PURPLE;
    if (((*philo_id) % 2) == 0)
        color = CYAN;
    if (((*philo_id) % 3) == 0)
        color = GREEN;

    printf("%s%i EAT\n", color, *philo_id);
    printf("%s%i SLEEP\n", color, *philo_id);
    printf("%s%i THINK" RESET "\n\n", color, *philo_id);
}

// void    ft_eating()
// {}
