/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:03:48 by thodavid          #+#    #+#             */
/*   Updated: 2025/06/18 15:00:07 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t *ft_thread(t_data *data, void *f())
{
    int i;
    int check_thread;
    pthread_t *threads_arr;

    i = 0;
    check_thread = 0;
    threads_arr = malloc(sizeof(pthread_t) * data->number_of_philos);
    if (threads_arr == NULL)
        ft_error("philo_arr malloc failed");
    while (i < data->number_of_philos)
    {
        check_thread = pthread_create(&threads_arr[i], NULL, f, &data->philos_arr[i]);
        if (check_thread != 0)
            ft_error("failed to create thread");
        i++;
    }
    return (threads_arr);
}

/*
todo:
leaaaaaaaaaaaaak
free(arg) n'est jamais atteint
🔧 Solution :
Soit tu passes
t_philo * au lieu d’un int * pour chaque thread.
Soit tu extrais
la logique vers un while (!stop_condition) et tu free à la fin.
*/
void *philo_life(void *arg)
{
    t_philo *philo;
    pthread_t death_checker;
    // pthread_mutex_t mutex;

    philo = (t_philo *)arg;
    pthread_create(&death_checker, NULL, ft_thread_death_check, philo);
    pthread_detach(death_checker);//autonomus thread
    while (!philo->data->death)
    {
        printf("\n-------------------------------------------------\nHELLO IAM THREAD?PHILO?   [%i]\nR-fork->[%i]~~~L-fork->[%i]\n",
               philo->id, philo->right_fork, philo->left_fork);
        ft_take_forks(philo);
        ft_eating(philo);
        //ft_putDown_fork(philo);
        ft_sleeping(philo);
        ft_thinking(philo);
    }
    // free(arg);
    return (NULL);
}

void ft_eating(t_philo *philo)
{
    long ts;
    
    ts = timestamp_now(philo->data);
    printf("%s%ld %i is eating" RESET "\n", log_format(philo->id), ts, philo->id);
}

void ft_thinking(t_philo *philo)
{
    long ts;
    
    ts = timestamp_now(philo->data);
    printf("%s%ld %i is thinking" RESET "\n", log_format(philo->id), ts, philo->id);
}

void ft_sleeping(t_philo *philo)
{
    long ts;
    
    ts = timestamp_now(philo->data);
    printf("%s%ld %i is sleeping" RESET "\n", log_format(philo->id), ts, philo->id);
}



void *ft_thread_death_check(void *arg)
{
    t_philo *philo;
    pthread_mutex_t mutex;
    long    now;

    philo = (t_philo *)arg;
    pthread_mutex_init(&mutex, NULL);
    while (philo->data->death == 0)
    {
        now = get_timestamp_ms();
        if((now - (philo->last_meal)) >= philo->data->time_to_die)
        {
            pthread_mutex_lock(&mutex);
			printf("%s%ld %d died\n",RED, now - philo->data->start, philo->id);
            pthread_mutex_unlock(&mutex);
            pthread_mutex_destroy(&mutex);
            philo->data->death = 1;
            break;
        }
        usleep(242);
    }  
    return (NULL);
}

void    ft_take_forks(t_philo *philo)
{
    int left_f;
    int right_f;

    left_f = philo->left_fork;
    right_f = philo->right_fork;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks_arr[left_f].mutex);
        ft_log(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks_arr[right_f].mutex);
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks_arr[right_f].mutex);
        ft_log(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks_arr[left_f].mutex);
    }
}
void    ft_log(t_philo *philo, char *msg)
{
    long ts;
    
	if(philo->data->death)
		return ;
    ts = timestamp_now(philo->data);
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%s%ld %i %s" RESET "\n", log_format(philo->id), ts, philo->id, msg);
}
