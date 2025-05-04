/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:15:41 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/04 14:18:48 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define RESET	"\e[0m"

typedef struct s_data	t_data;

struct timevl 
{
    time_t      tv_sec;
    suseconds_t tv_usec;
};


typedef struct s_philo
{
	int		id;
	int		pthread_id;
	int		left_fork;
	int		right_fork;
	long	last_meal;
	t_data	*data;

}	t_philo;

typedef struct s_fork
{
	int			id;
	pthread_t	mutex;

}	t_fork;

struct	s_data
{
	int		number_of_philos;
	int		max_meal;
	long	start;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	t_fork	*forks_arr;
	t_philo	*philos_arr;
};

t_data	ft_parsing(int ac, char **av);
t_data	ft_stock_data(char **av);
pthread_t *ft_philo_thread(t_data *data, void *f());
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_error(char *str);
void	ft_check_args(char **av);
void	ft_check_data(t_data *data);
void	*philo_life(void *arg);
void	ft_log(int *philo_id);
long	ft_atol(const char *nptr);
long	get_timestamp_ms(void);
int		ft_free_thread_tab(pthread_t *arr, int p);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);

#endif
