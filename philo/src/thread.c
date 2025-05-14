/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:03:48 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/14 10:43:19 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t *ft_philo_thread(t_data *data, void *f())
{
    int i;
    int check_thread;
    //creation dun tableau de thread(philo)
    pthread_t *philo_id_arr;

    i = 0;
    //allocation de memoire pour le tableau de philos
    philo_id_arr = malloc(sizeof(pthread_t) * data->number_of_philos);
    if (philo_id_arr == NULL)
        ft_error("philo_arr malloc failed");
    //remplissage du tableau 
    while (i < data->number_of_philos)
    {
        int *philo_id = malloc(sizeof(int));
        *philo_id = i;
        check_thread = 0;
        //passer t_philo pour que chaque thread ai sa  strucutre
        check_thread = pthread_create(&philo_id_arr[i], NULL, f, philo_id);
        if (check_thread != 0)
            ft_error("failed to create thread");
        i++;
    }
    return (philo_id_arr);
}

void *philo_life(void *arg)
{
    int *id;
    char *color;

    id = (int *) arg;
    color = log_format(id);
    // while(1)
    // {
    //     ft_eating(id, color);
    //     ft_thinking(id, color);
    //     ft_sleeping(id, color);
    //     sleep(2);
    // }
    free(arg);
    return (NULL);
}

void    ft_eating(int *philo_id, char *color)
{
    printf("%s%i EAT"RESET"\n", color, *philo_id);
}

void    ft_thinking(int *philo_id, char *color)
{
    printf("%s%i THINK" RESET "\n", color, *philo_id);
}

void    ft_sleeping(int *philo_id, char *color)
{
    printf("%s%i SLEEP"RESET"\n", color, *philo_id);
}

char    *log_format(int *philo_id)
{
        char *color;
        color = "";
    if (((*philo_id) % 1) == 0)
        color = PURPLE;
    if (((*philo_id) % 2) == 0)
        color = CYAN;
    if (((*philo_id) % 3) == 0)
        color = GREEN;
    return (color);
}

/* 

int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);

| Argument                         | Rôle                                       |
| -------------------------------- | ------------------------------------------ |
| `pthread_t *thread`              | Pointeur pour stocker l’ID du thread créé. |
| `const pthread_attr_t *attr`     | Attributs du thread (NULL = défaut).       |
| `void *(*start_routine)(void *)` | Fonction que le thread exécutera.          |
| `void *arg`                      | Argument transmis à la fonction du thread. |
*/

